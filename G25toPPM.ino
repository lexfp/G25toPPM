/* Simplified Thrustmaster T.16000M FCS Joystick Report Parser */

#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include "BtnPPMMap.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

/**
    This code will map the Logitech G25 steering wheel and pedals to PPM output. It will basically allow you to drive a RC car with the wheel.
    @Author github.com/lexfp
*/

//PPM config values
#define FRAME_LENGTH 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PULSE_LENGTH 300  //set the pulse length
#define onState 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 3  //set PPM signal output pin on the arduino

BtnPPMMap btnPPMMap;

// Logitech G25 steering wheel - only the wheel, pedals & shifter are mapped
struct GamePadEventData
{
  uint16_t	wheel;
  uint8_t		shift;
  uint32_t	gas;
} __attribute__((packed));

class JoystickEvents
{
  private:
    BtnPPMMap *btnPPMMap;
  public:
    JoystickEvents(BtnPPMMap *btnPPMMap);
    virtual void OnGamePadChanged(const GamePadEventData *evt);
    virtual void disconnectJoystick();
};

#define RPT_GAMEPAD_LEN	sizeof(GamePadEventData)

class JoystickReportParser : public HIDReportParser
{
    JoystickEvents		*joyEvents;

    uint8_t oldPad[RPT_GAMEPAD_LEN];

  public:
    JoystickReportParser(JoystickEvents *evt);
    virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};


JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
  joyEvents(evt)
{}

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
  // Checking if there are changes in report since the method was last called
  bool match = (sizeof(oldPad) == len) && (memcmp(oldPad, buf, len) == 0);

  // Calling Game Pad event handler
  if (!match && joyEvents) {
    joyEvents->OnGamePadChanged((const GamePadEventData*)buf);
    memcpy(oldPad, buf, len);
  }
}

JoystickEvents::JoystickEvents(BtnPPMMap * bpm) {
  btnPPMMap = bpm;
}

void JoystickEvents::disconnectJoystick()
{
  btnPPMMap->disArm();
}


void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{
  
    Serial.print("W: ");
    Serial.print(evt->wheel, DEC);
    Serial.print("S: ");
    Serial.print(evt->shift, DEC);
    Serial.print("T: ");
    Serial.print(evt->gas, DEC);
    Serial.println();
  
  btnPPMMap->mapShift(evt->shift);
  btnPPMMap->mapGas(evt->gas);
  btnPPMMap->mapSteer(evt->wheel);
  btnPPMMap->debug();

}

USB                                             Usb;
USBHub                                          Hub(&Usb);
HIDUniversal                                    Hid(&Usb);
JoystickEvents                                  JoyEvents(&btnPPMMap);
JoystickReportParser                            Joy(&JoyEvents);

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  if (!Hid.SetReportParser(0, &Joy))
    ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  );

  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, !onState);  //set the PPM signal pin to the default state (off)

  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;

  OCR1A = 100;  // compare match register, change this
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();
}

void loop()
{
  Usb.Task();
  if (Usb.getUsbTaskState() != USB_STATE_RUNNING)
  {
    //disconnected joystick
    JoyEvents.disconnectJoystick();
    //Serial.println("Joystick disconnected");
  }
}

ISR(TIMER1_COMPA_vect) { //leave this alone
  static boolean state = true;

  TCNT1 = 0;

  if (state) {  //start pulse
    digitalWrite(sigPin, onState);
    OCR1A = PULSE_LENGTH * 2;
    state = false;
  } else { //end pulse and calculate when to start the next pulse
    static byte cur_chan_numb;
    int channelValue;
    static unsigned int calc_rest;

    digitalWrite(sigPin, !onState);
    state = true;

    if (cur_chan_numb >= BtnPPMMap::NUM_CHANNELS) {
      cur_chan_numb = 0;
      calc_rest = calc_rest + PULSE_LENGTH;//
      OCR1A = (FRAME_LENGTH - calc_rest) * 2;
      calc_rest = 0;
    }
    else {
      channelValue = btnPPMMap.getChannelValue(cur_chan_numb);
      OCR1A = (channelValue - PULSE_LENGTH) * 2;
      calc_rest = calc_rest + channelValue;
      cur_chan_numb++;
    }
  }
}
