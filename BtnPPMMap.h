#include <usbhid.h>

/**
  Button to PPM Mapping - Maps the joystick buttons and actions to different PPM values
  @Author github.com/lexfp
*/
class BtnPPMMap
{
  public:
    BtnPPMMap();
    void mapGas(uint32_t value);
    void mapShift(long value);
    void mapSteer(long value);
    int getChannelValue(int channel);
    void debug();
    void failsafe();
    void disArm();
    int getNumChannels();

  private:
    //please note that these values below can be different if the wheel is not plugged into AC, so please plug in your wheel if fine tuning values below
    static const int WHEEL_MIN_INPUT = 0;
    static const int WHEEL_MAX_INPUT = 1024;
    static const int WHEEL_CENTER_INPUT = 512;
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
    int PPM_THROTTLE_MAX; 
    int PPM_REVERSE_MAX; 
    static const int NUM_GEARS = 4;    

#define CAR_DEFAULT //change the CAR_DEFAULT values or add another one here for your own needs   

//Feel free to change the settings below for the type of feel that you want in your car
#ifdef CAR_DEFAULT
    static const int NUM_CHANNELS = 6; //set this to however many channels your rx supports
    static const int PPM_THROTTLE_NEUTRAL = 1500; //50/50 (1500) or 70/30 (1300)
    static const bool WHEEL_REVERSE_STEERING = false;
    static const int WHEEL_LEFT_TURN_LIMIT = PPM_MIN_VALUE; //set the turn limits to avoid stressing your servos
    static const int WHEEL_CENTER = PPM_CENTER_VALUE; //this is the steering center trim value
    static const int WHEEL_RIGHT_TURN_LIMIT = PPM_MAX_VALUE;
    static const int FIRST_GEAR_FORWARD_LIMIT_PERCENT = 10; 
    static const int SECOND_GEAR_FORWARD_LIMIT_PERCENT = 30;
    static const int THIRD_GEAR_FORWARD_LIMIT_PERCENT = 50; 
    static const int FOURTH_GEAR_FORWARD_LIMIT_PERCENT = 100;
    static const int FIRST_GEAR_REVERSE_LIMIT_PERCENT = 30; 
    static const int SECOND_GEAR_REVERSE_LIMIT_PERCENT = 50;
    static const int THIRD_GEAR_REVERSE_LIMIT_PERCENT = 70; 
    static const int FOURTH_GEAR_REVERSE_LIMIT_PERCENT = 100;
#endif
#ifdef CAR_MICRO_T 
    static const int NUM_CHANNELS = 6;
    static const int PPM_THROTTLE_NEUTRAL = 1450; 
    static const bool WHEEL_REVERSE_STEERING = false;
    static const int WHEEL_LEFT_TURN_LIMIT = 1100;
    static const int WHEEL_CENTER = 1435;
    static const int WHEEL_RIGHT_TURN_LIMIT = 1800; 
    static const int FIRST_GEAR_FORWARD_LIMIT_PERCENT = 18; 
    static const int SECOND_GEAR_FORWARD_LIMIT_PERCENT = 40;
    static const int THIRD_GEAR_FORWARD_LIMIT_PERCENT = 75; 
    static const int FOURTH_GEAR_FORWARD_LIMIT_PERCENT = 100;
    static const int FIRST_GEAR_REVERSE_LIMIT_PERCENT = 30; 
    static const int SECOND_GEAR_REVERSE_LIMIT_PERCENT = 40;
    static const int THIRD_GEAR_REVERSE_LIMIT_PERCENT = 70; 
    static const int FOURTH_GEAR_REVERSE_LIMIT_PERCENT = 100;
#endif
#ifdef CAR_MINI_Q5 
    static const int NUM_CHANNELS = 6;
    static const int PPM_THROTTLE_NEUTRAL = 1450; 
    static const bool WHEEL_REVERSE_STEERING = true;
    static const int WHEEL_LEFT_TURN_LIMIT = 1000;
    static const int WHEEL_CENTER = 1450;
    static const int WHEEL_RIGHT_TURN_LIMIT = 2000;   
    static const int FIRST_GEAR_FORWARD_LIMIT_PERCENT = 15; 
    static const int SECOND_GEAR_FORWARD_LIMIT_PERCENT = 50;
    static const int THIRD_GEAR_FORWARD_LIMIT_PERCENT = 70; 
    static const int FOURTH_GEAR_FORWARD_LIMIT_PERCENT = 100;
    static const int FIRST_GEAR_REVERSE_LIMIT_PERCENT = 30; 
    static const int SECOND_GEAR_REVERSE_LIMIT_PERCENT = 50;
    static const int THIRD_GEAR_REVERSE_LIMIT_PERCENT = 70; 
    static const int FOURTH_GEAR_REVERSE_LIMIT_PERCENT = 100;
#endif
#ifdef CAR_MICRO_TRUGGY  //the following are examples values for different cars
    static const int NUM_CHANNELS = 6;
    static const int PPM_THROTTLE_NEUTRAL = 1470; 
    static const bool WHEEL_REVERSE_STEERING = false;
    static const int WHEEL_LEFT_TURN_LIMIT = 1080;
    static const int WHEEL_CENTER = 1500;
    static const int WHEEL_RIGHT_TURN_LIMIT = 1920; 
    static const int FIRST_GEAR_FORWARD_LIMIT_PERCENT = 10; 
    static const int SECOND_GEAR_FORWARD_LIMIT_PERCENT = 30;
    static const int THIRD_GEAR_FORWARD_LIMIT_PERCENT = 50; 
    static const int FOURTH_GEAR_FORWARD_LIMIT_PERCENT = 100;
    static const int FIRST_GEAR_REVERSE_LIMIT_PERCENT = 30; 
    static const int SECOND_GEAR_REVERSE_LIMIT_PERCENT = 50;
    static const int THIRD_GEAR_REVERSE_LIMIT_PERCENT = 70; 
    static const int FOURTH_GEAR_REVERSE_LIMIT_PERCENT = 100;
#endif

    static const int PPM_THROTTLE_FORWARD_RANGE = PPM_MAX_VALUE-PPM_THROTTLE_NEUTRAL; 
    static const int PPM_THROTTLE_REVERSE_RANGE = PPM_THROTTLE_NEUTRAL-PPM_MIN_VALUE; 
    static const int FIRST_GEAR_FORWARD_LIMIT = ((FIRST_GEAR_FORWARD_LIMIT_PERCENT/100.0)*PPM_THROTTLE_FORWARD_RANGE)+PPM_THROTTLE_NEUTRAL; 
    static const int SECOND_GEAR_FORWARD_LIMIT = ((SECOND_GEAR_FORWARD_LIMIT_PERCENT/100.0)*PPM_THROTTLE_FORWARD_RANGE)+PPM_THROTTLE_NEUTRAL; 
    static const int THIRD_GEAR_FORWARD_LIMIT = ((THIRD_GEAR_FORWARD_LIMIT_PERCENT/100.0)*PPM_THROTTLE_FORWARD_RANGE)+PPM_THROTTLE_NEUTRAL; 
    static const int FOURTH_GEAR_FORWARD_LIMIT = ((FOURTH_GEAR_FORWARD_LIMIT_PERCENT/100.0)*PPM_THROTTLE_FORWARD_RANGE)+PPM_THROTTLE_NEUTRAL; 
    static const int FIRST_GEAR_REVERSE_LIMIT = (PPM_THROTTLE_NEUTRAL-((FIRST_GEAR_REVERSE_LIMIT_PERCENT/100.0)*PPM_THROTTLE_REVERSE_RANGE)); 
    static const int SECOND_GEAR_REVERSE_LIMIT = (PPM_THROTTLE_NEUTRAL-((SECOND_GEAR_REVERSE_LIMIT_PERCENT/100.0)*PPM_THROTTLE_REVERSE_RANGE)); 
    static const int THIRD_GEAR_REVERSE_LIMIT = (PPM_THROTTLE_NEUTRAL-((THIRD_GEAR_REVERSE_LIMIT_PERCENT/100.0)*PPM_THROTTLE_REVERSE_RANGE)); 
    static const int FOURTH_GEAR_REVERSE_LIMIT = (PPM_THROTTLE_NEUTRAL-((FOURTH_GEAR_REVERSE_LIMIT_PERCENT/100.0)*PPM_THROTTLE_REVERSE_RANGE)); 
    int GEAR_FORWARD_LIMIT[NUM_GEARS] = {FIRST_GEAR_FORWARD_LIMIT,SECOND_GEAR_FORWARD_LIMIT,THIRD_GEAR_FORWARD_LIMIT,FOURTH_GEAR_FORWARD_LIMIT};
    int GEAR_REVERSE_LIMIT[NUM_GEARS] = {FIRST_GEAR_REVERSE_LIMIT,SECOND_GEAR_REVERSE_LIMIT,THIRD_GEAR_REVERSE_LIMIT,FOURTH_GEAR_REVERSE_LIMIT};

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
