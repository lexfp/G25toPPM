#include <usbhid.h>

/**
  Button to PPM Mapping - Maps the joystick buttons and actions to different PPM values
  @Author github.com/lexfp
*/
class BtnPPMMap
{
  public:
    BtnPPMMap();
    
    static const int NUM_CHANNELS = 6; //set this to however many channels your rx supports

    void mapGas(uint32_t value);
    void mapShift(long value);
    void mapSteer(long value);
    int getChannelValue(int channel);
    void debug();
    void failsafe();
    void disArm();

  private:
    //please note that these values below can be different if the wheel is not plugged into AC, so please plug in your wheel if fine tuning values below
    static const uint32_t MAX_BREAK_INPUT = 16754943; //value in decimal (evt->gas) when I step on the break
    static const uint32_t NEUTRAL_GAS_INPUT = 4294944895; //value in decimal (evt->gas) when I don't step on any pedal
    static const uint32_t MAX_GAS_INPUT = 4278233088; //value in decimal (evt->gas) when I step on the gas
    static const int SHIFT_UP_INPUT = 160; //value in decimal when shifter is up
    static const int SHIFT_DOWN_INPUT = 144; //value in decimal when shifter is down 
    static const long DELAY_BETWEEN_SHIFT_MILLIS = 300; //amount of time between shift so you don't accidentally go from gear 1 to 5 in one motion
    
    static const int CH_THROTTLE = 0;
    static const int CH_STEERING = 1;
    static const int CH_SHIFTER = 2;
    static const int CH_4 = 3;
    static const int CH_5 = 4;
    static const int CH_6 = 5;
    static const int CH_7 = 6;
    static const int CH_8 = 7;
    
    static const int PPM_MAX_VALUE = 2000;
    static const int PPM_MIN_VALUE = 1000;
    static const int PPM_CENTER_VALUE = ((PPM_MAX_VALUE - PPM_MIN_VALUE) / 2) + PPM_MIN_VALUE;
    static const int PPM_FAIL_SAFE_VALUE = 950;
    //this following is the throttle arm value for your esc
    static const int PPM_THROTTLE_NEUTRAL = 1470; //50/50 (1500) or 70/30 (1300)
    int PPM_THROTTLE_MAX; 

    //Feel free to change the settings below for the type of feel that you want in your car
    static const int NUM_GEARS = 4; //set this to however many gears you want
    static const int FIRST_GEAR_LIMIT = 1550; //this is the throttle limit for first gear
    static const int SECOND_GEAR_LIMIT = 1650; //this is the throttle limit for second gear
    static const int THIRD_GEAR_LIMIT = 1750; //this is the throttle limit for third gear
    static const int FOURTH_GEAR_LIMIT = PPM_MAX_VALUE; //this is the throttle limit for fourth gear
    int GEAR_LIMIT[NUM_GEARS] = {FIRST_GEAR_LIMIT,SECOND_GEAR_LIMIT,THIRD_GEAR_LIMIT,FOURTH_GEAR_LIMIT};
    
    unsigned long lastShiftUpMillis;
    unsigned long lastShiftDownMillis;
    
    int currentGear;
    int channel[NUM_CHANNELS] = {};
    void mapGasValue(uint32_t value);
    void mapBreakValue(uint32_t value);
    void mapChannelValue(boolean invert, int channel, uint32_t value, uint32_t minValue, uint32_t maxValue, int minPPM, int maxPPM);
    long mapf(float x, float in_min, float in_max, float out_min, float out_max);
    void shiftUp();
    void shiftDown();
};
