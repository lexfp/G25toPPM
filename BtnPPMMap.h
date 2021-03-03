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
    void failsafe();
    void disArm();
    void changeCar(int car);
    int getNumChannels();
    void debug();
    void debugCurrentCar();

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

#define CAR_TOTAL 3 //total number of models we have
#define CAR_DEFAULT 0
#define CAR_MICRO_T 1
#define CAR_MINI_Q5 2
#define CAR_MICRO_TRUGGY 3
    int CURRENT_CAR = CAR_DEFAULT;

    int NUM_CHANNELS[CAR_TOTAL];
    int PPM_THROTTLE_NEUTRAL[CAR_TOTAL];
    bool WHEEL_REVERSE_STEERING[CAR_TOTAL];
    int WHEEL_LEFT_TURN_LIMIT[CAR_TOTAL];
    int WHEEL_CENTER[CAR_TOTAL];
    int WHEEL_RIGHT_TURN_LIMIT[CAR_TOTAL];
    int FIRST_GEAR_FORWARD_LIMIT_PERCENT[CAR_TOTAL];
    int SECOND_GEAR_FORWARD_LIMIT_PERCENT[CAR_TOTAL];
    int THIRD_GEAR_FORWARD_LIMIT_PERCENT[CAR_TOTAL];
    int FOURTH_GEAR_FORWARD_LIMIT_PERCENT[CAR_TOTAL];
    int FIRST_GEAR_REVERSE_LIMIT_PERCENT[CAR_TOTAL];
    int SECOND_GEAR_REVERSE_LIMIT_PERCENT[CAR_TOTAL];
    int THIRD_GEAR_REVERSE_LIMIT_PERCENT[CAR_TOTAL];
    int FOURTH_GEAR_REVERSE_LIMIT_PERCENT[CAR_TOTAL];

    int GEAR_FORWARD_LIMIT[CAR_TOTAL][NUM_GEARS];
    int GEAR_REVERSE_LIMIT[CAR_TOTAL][NUM_GEARS];

    unsigned long lastShiftUpMillis;
    unsigned long lastShiftDownMillis;

    int currentGear;
#define MAX_CHANNELS 16
    int channel[MAX_CHANNELS] = {};
    void mapGasValue(uint32_t value);
    void mapBreakValue(uint32_t value);
    void mapChannelValue(boolean invert, int channel, uint32_t value, uint32_t minValue, uint32_t maxValue, int minPPM, int maxPPM);
    long mapf(float x, float in_min, float in_max, float out_min, float out_max);
    void shiftUp();
    void shiftDown();
};
