#include "BtnPPMMap.h"

/**
  Button to PPM Mapping - Maps the joystick buttons and actions to different PPM values
  @Author github.com/lexfp
*/
BtnPPMMap::BtnPPMMap()
{
  currentGear = 0;
  lastShiftUpMillis = millis();
  lastShiftDownMillis = millis();
  channel[CH_THROTTLE] = PPM_THROTTLE_NEUTRAL;
  channel[CH_STEERING] = WHEEL_CENTER;
  channel[CH_3] = PPM_FAIL_SAFE_VALUE;
  channel[CH_4] = PPM_FAIL_SAFE_VALUE;
  channel[CH_5] = PPM_FAIL_SAFE_VALUE;
  channel[CH_6] = PPM_FAIL_SAFE_VALUE;
  channel[CH_7] = PPM_FAIL_SAFE_VALUE;
  channel[CH_8] = PPM_FAIL_SAFE_VALUE;
}

void BtnPPMMap::changeCar(int car) {
  int FIRST_GEAR_FORWARD_LIMIT_PERCENT;
  int SECOND_GEAR_FORWARD_LIMIT_PERCENT;
  int THIRD_GEAR_FORWARD_LIMIT_PERCENT;
  int FOURTH_GEAR_FORWARD_LIMIT_PERCENT;
  int FIRST_GEAR_REVERSE_LIMIT_PERCENT;
  int SECOND_GEAR_REVERSE_LIMIT_PERCENT;
  int THIRD_GEAR_REVERSE_LIMIT_PERCENT;
  int FOURTH_GEAR_REVERSE_LIMIT_PERCENT;

  if (car == CAR_DEFAULT) {
    NUM_CHANNELS = 6; //set this to however many channels your rx supports
    PPM_THROTTLE_NEUTRAL = 1500; //50/50 (1500) or 70/30 (1300)
    WHEEL_REVERSE_STEERING = false;
    WHEEL_LEFT_TURN_LIMIT = PPM_MIN_VALUE; //set the turn limits to avoid stressing your servos
    WHEEL_CENTER = PPM_CENTER_VALUE; //this is the steering center trim value
    WHEEL_RIGHT_TURN_LIMIT = PPM_MAX_VALUE;
    FIRST_GEAR_FORWARD_LIMIT_PERCENT = 10;
    SECOND_GEAR_FORWARD_LIMIT_PERCENT = 30;
    THIRD_GEAR_FORWARD_LIMIT_PERCENT = 50;
    FOURTH_GEAR_FORWARD_LIMIT_PERCENT = 100;
    FIRST_GEAR_REVERSE_LIMIT_PERCENT = 30;
    SECOND_GEAR_REVERSE_LIMIT_PERCENT = 50;
    THIRD_GEAR_REVERSE_LIMIT_PERCENT = 70;
    FOURTH_GEAR_REVERSE_LIMIT_PERCENT = 100;
  } else if (car == CAR_MICRO_T) {
    NUM_CHANNELS = 6;
    PPM_THROTTLE_NEUTRAL = 1450;
    WHEEL_REVERSE_STEERING = false;
    WHEEL_LEFT_TURN_LIMIT = 1100;
    WHEEL_CENTER = 1435;
    WHEEL_RIGHT_TURN_LIMIT = 1800;
    FIRST_GEAR_FORWARD_LIMIT_PERCENT = 18;
    SECOND_GEAR_FORWARD_LIMIT_PERCENT = 40;
    THIRD_GEAR_FORWARD_LIMIT_PERCENT = 75;
    FOURTH_GEAR_FORWARD_LIMIT_PERCENT = 100;
    FIRST_GEAR_REVERSE_LIMIT_PERCENT = 30;
    SECOND_GEAR_REVERSE_LIMIT_PERCENT = 40;
    THIRD_GEAR_REVERSE_LIMIT_PERCENT = 70;
    FOURTH_GEAR_REVERSE_LIMIT_PERCENT = 100;
  } else if (car == CAR_MINI_Q5) {
    NUM_CHANNELS = 6;
    PPM_THROTTLE_NEUTRAL = 1450;
    WHEEL_REVERSE_STEERING = true;
    WHEEL_LEFT_TURN_LIMIT = 1000;
    WHEEL_CENTER = 1450;
    WHEEL_RIGHT_TURN_LIMIT = 2000;
    FIRST_GEAR_FORWARD_LIMIT_PERCENT = 15;
    SECOND_GEAR_FORWARD_LIMIT_PERCENT = 50;
    THIRD_GEAR_FORWARD_LIMIT_PERCENT = 70;
    FOURTH_GEAR_FORWARD_LIMIT_PERCENT = 100;
    FIRST_GEAR_REVERSE_LIMIT_PERCENT = 30;
    SECOND_GEAR_REVERSE_LIMIT_PERCENT = 50;
    THIRD_GEAR_REVERSE_LIMIT_PERCENT = 70;
    FOURTH_GEAR_REVERSE_LIMIT_PERCENT = 100;
  } else if (car == CAR_MICRO_TRUGGY) {
    NUM_CHANNELS = 6;
    PPM_THROTTLE_NEUTRAL = 1470;
    WHEEL_REVERSE_STEERING = false;
    WHEEL_LEFT_TURN_LIMIT = 1080;
    WHEEL_CENTER = 1500;
    WHEEL_RIGHT_TURN_LIMIT = 1920;
    FIRST_GEAR_FORWARD_LIMIT_PERCENT = 10;
    SECOND_GEAR_FORWARD_LIMIT_PERCENT = 30;
    THIRD_GEAR_FORWARD_LIMIT_PERCENT = 50;
    FOURTH_GEAR_FORWARD_LIMIT_PERCENT = 100;
    FIRST_GEAR_REVERSE_LIMIT_PERCENT = 30;
    SECOND_GEAR_REVERSE_LIMIT_PERCENT = 50;
    THIRD_GEAR_REVERSE_LIMIT_PERCENT = 70;
    FOURTH_GEAR_REVERSE_LIMIT_PERCENT = 100;
  }

  int PPM_THROTTLE_FORWARD_RANGE = PPM_MAX_VALUE - PPM_THROTTLE_NEUTRAL;
  int PPM_THROTTLE_REVERSE_RANGE = PPM_THROTTLE_NEUTRAL - PPM_MIN_VALUE;
  GEAR_FORWARD_LIMIT[0] = ((FIRST_GEAR_FORWARD_LIMIT_PERCENT / 100.0) * PPM_THROTTLE_FORWARD_RANGE) + PPM_THROTTLE_NEUTRAL;
  GEAR_FORWARD_LIMIT[1] = ((SECOND_GEAR_FORWARD_LIMIT_PERCENT / 100.0) * PPM_THROTTLE_FORWARD_RANGE) + PPM_THROTTLE_NEUTRAL;
  GEAR_FORWARD_LIMIT[2] = ((THIRD_GEAR_FORWARD_LIMIT_PERCENT / 100.0) * PPM_THROTTLE_FORWARD_RANGE) + PPM_THROTTLE_NEUTRAL;
  GEAR_FORWARD_LIMIT[3] = ((FOURTH_GEAR_FORWARD_LIMIT_PERCENT / 100.0) * PPM_THROTTLE_FORWARD_RANGE) + PPM_THROTTLE_NEUTRAL;
  GEAR_REVERSE_LIMIT[0] = (PPM_THROTTLE_NEUTRAL - ((FIRST_GEAR_REVERSE_LIMIT_PERCENT / 100.0) * PPM_THROTTLE_REVERSE_RANGE));
  GEAR_REVERSE_LIMIT[1] = (PPM_THROTTLE_NEUTRAL - ((SECOND_GEAR_REVERSE_LIMIT_PERCENT / 100.0) * PPM_THROTTLE_REVERSE_RANGE));
  GEAR_REVERSE_LIMIT[2] = (PPM_THROTTLE_NEUTRAL - ((THIRD_GEAR_REVERSE_LIMIT_PERCENT / 100.0) * PPM_THROTTLE_REVERSE_RANGE));
  GEAR_REVERSE_LIMIT[3] = (PPM_THROTTLE_NEUTRAL - ((FOURTH_GEAR_REVERSE_LIMIT_PERCENT / 100.0) * PPM_THROTTLE_REVERSE_RANGE));

  PPM_THROTTLE_MAX = GEAR_FORWARD_LIMIT[currentGear];
  PPM_REVERSE_MAX = GEAR_REVERSE_LIMIT[currentGear];
}

int BtnPPMMap::getNumChannels() {
  return NUM_CHANNELS;
}

int BtnPPMMap::getChannelValue(int c) {
  return channel[c];
}

void BtnPPMMap::mapGas(uint32_t value) {
  if (value < MAX_GAS_INPUT) {
    //stepping on brake
    mapBrakeValue(value);
  } else if (value < NEUTRAL_GAS_INPUT) {
    //stepping on gas
    mapGasValue(value);
  }

}

void BtnPPMMap::mapShift(long value) {
  //shift up and down for gears
  if (value == SHIFT_UP_INPUT) {
    shiftUp();
  } else if (value == SHIFT_DOWN_INPUT) {
    shiftDown();
  }
}

void BtnPPMMap::mapSteer(long value) {
  if (value < WHEEL_CENTER_INPUT) {
    //turning left
    if (WHEEL_REVERSE_STEERING) {
      //reverse steering
      mapChannelValue(true, CH_STEERING, value, WHEEL_MIN_INPUT, WHEEL_CENTER_INPUT, WHEEL_CENTER, WHEEL_RIGHT_TURN_LIMIT);
    } else {
      mapChannelValue(false, CH_STEERING, value, WHEEL_MIN_INPUT, WHEEL_CENTER_INPUT, WHEEL_LEFT_TURN_LIMIT, WHEEL_CENTER);
    }
  } else {
    //turning right
    if (WHEEL_REVERSE_STEERING) {
      //reverse steering
      mapChannelValue(true, CH_STEERING, value, WHEEL_CENTER_INPUT, WHEEL_MAX_INPUT, WHEEL_LEFT_TURN_LIMIT, WHEEL_CENTER);
    } else {
      mapChannelValue(false, CH_STEERING, value, WHEEL_CENTER_INPUT, WHEEL_MAX_INPUT, WHEEL_CENTER, WHEEL_RIGHT_TURN_LIMIT);
    }
  }
}

void BtnPPMMap::mapGasValue(uint32_t value) {
  mapChannelValue(true, CH_THROTTLE, value, MAX_GAS_INPUT, NEUTRAL_GAS_INPUT, PPM_THROTTLE_NEUTRAL, PPM_THROTTLE_MAX);
}

void BtnPPMMap::mapBrakeValue(uint32_t value) {
  mapChannelValue(false, CH_THROTTLE, value, MAX_BRAKE_INPUT, NEUTRAL_GAS_INPUT, PPM_REVERSE_MAX, PPM_THROTTLE_NEUTRAL);
}

void BtnPPMMap::mapChannelValue(boolean invert, int c, uint32_t value, uint32_t minValue, uint32_t maxValue, int ppmMin, int ppmMax) {
  if (invert) {
    channel[c] = mapf(value, minValue, maxValue, ppmMax, ppmMin);
  } else {
    channel[c] = mapf(value, minValue, maxValue, ppmMin, ppmMax);
  }
}

long BtnPPMMap::mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void BtnPPMMap::failsafe() {
  //put your own code here for this functionality
  //be sure to set up your FC software to failsafe on this value as well
}

void BtnPPMMap::disArm() {
  //substitute your own disarm code below instead
  channel[CH_THROTTLE] = PPM_THROTTLE_NEUTRAL;
  channel[CH_STEERING] = PPM_CENTER_VALUE;
}

void BtnPPMMap::shiftUp() {
  if (millis() - lastShiftUpMillis > DELAY_BETWEEN_SHIFT_MILLIS) {
    if (currentGear < NUM_GEARS - 1) {
      currentGear++;
    }
    PPM_THROTTLE_MAX = GEAR_FORWARD_LIMIT[currentGear];
    PPM_REVERSE_MAX = GEAR_REVERSE_LIMIT[currentGear];
    lastShiftUpMillis = millis();
  }
}

void BtnPPMMap::shiftDown() {
  if (millis() - lastShiftDownMillis > DELAY_BETWEEN_SHIFT_MILLIS) {
    if (currentGear > 0) {
      currentGear--;
    }
    PPM_THROTTLE_MAX = GEAR_FORWARD_LIMIT[currentGear];
    PPM_REVERSE_MAX = GEAR_REVERSE_LIMIT[currentGear];
    lastShiftDownMillis = millis();
  }
}

void BtnPPMMap::debug()
{
  Serial.print("OUT - T:");
  Serial.print(channel[CH_THROTTLE]);
  Serial.print(" W:");
  Serial.print(channel[CH_STEERING]);
  Serial.print(" FM:");
  Serial.print(PPM_THROTTLE_MAX);
  Serial.print(" RM:");
  Serial.print(PPM_REVERSE_MAX);

  Serial.print(" TN:");
  Serial.print(PPM_THROTTLE_NEUTRAL);
  Serial.print(" -CG:");
  Serial.print(currentGear);
  Serial.print(" -FGL:");
  Serial.print(GEAR_FORWARD_LIMIT[currentGear]);
  Serial.print(" -RGL:");
  Serial.print(GEAR_REVERSE_LIMIT[currentGear]);

  Serial.println("");
}
