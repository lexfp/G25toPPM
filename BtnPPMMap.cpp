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
  PPM_THROTTLE_MAX = GEAR_FORWARD_LIMIT[0];
  PPM_REVERSE_MAX = GEAR_REVERSE_LIMIT[0];
  channel[CH_THROTTLE] = PPM_THROTTLE_NEUTRAL;
  channel[CH_STEERING] = WHEEL_CENTER;
  channel[CH_SHIFTER] = GEAR_FORWARD_LIMIT[0];
  channel[CH_4] = PPM_FAIL_SAFE_VALUE;
  channel[CH_5] = PPM_FAIL_SAFE_VALUE;
  channel[CH_6] = PPM_FAIL_SAFE_VALUE;
  channel[CH_7] = PPM_FAIL_SAFE_VALUE;
  channel[CH_8] = PPM_FAIL_SAFE_VALUE;
}

int BtnPPMMap::getNumChannels() {
  return NUM_CHANNELS;  
}

int BtnPPMMap::getChannelValue(int c) {
  return channel[c];
}

void BtnPPMMap::mapGas(uint32_t value) {  
  if (value < MAX_GAS_INPUT) {
    //stepping on break
    mapBreakValue(value);
  } else if (value < NEUTRAL_GAS_INPUT) {
    //stepping on gas
    mapGasValue(value);
  }
  
}

void BtnPPMMap::mapShift(long value){
  //shift up and down for gears
  if (value == SHIFT_UP_INPUT) {
    shiftUp();
  } else if (value == SHIFT_DOWN_INPUT) {
    shiftDown();
  }
}

void BtnPPMMap::mapSteer(long value){
  if (value < WHEEL_CENTER_INPUT) {
    //turning left
    mapChannelValue(false, CH_STEERING, value, WHEEL_MIN_INPUT, WHEEL_CENTER_INPUT, WHEEL_LEFT_TURN_LIMIT, WHEEL_CENTER);
  } else {
    //turning right
    mapChannelValue(false, CH_STEERING, value, WHEEL_CENTER_INPUT, WHEEL_MAX_INPUT, WHEEL_CENTER, WHEEL_RIGHT_TURN_LIMIT);
  }
}

void BtnPPMMap::mapGasValue(uint32_t value) {
  mapChannelValue(true, CH_THROTTLE, value, MAX_GAS_INPUT, NEUTRAL_GAS_INPUT, PPM_THROTTLE_NEUTRAL, PPM_THROTTLE_MAX);
}

void BtnPPMMap::mapBreakValue(uint32_t value) {
  mapChannelValue(false, CH_THROTTLE, value, MAX_BREAK_INPUT, NEUTRAL_GAS_INPUT, PPM_REVERSE_MAX, PPM_THROTTLE_NEUTRAL);
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
    if (currentGear < NUM_GEARS-1) {
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
  Serial.print("T:");
  Serial.print(channel[CH_THROTTLE]);
  Serial.print(" W:");
  Serial.print(channel[CH_STEERING]);
  Serial.print(" FM:");
  Serial.print(PPM_THROTTLE_MAX);
  Serial.print(" RM:");
  Serial.print(PPM_REVERSE_MAX);
  
  Serial.print(" -a:");
  Serial.print(GEAR_REVERSE_LIMIT[0]);
  Serial.print(" -b:");
  Serial.print(GEAR_REVERSE_LIMIT[1]);
  Serial.print(" -c:");
  Serial.print(GEAR_REVERSE_LIMIT[2]);
  Serial.print(" -d:");
  Serial.print(GEAR_REVERSE_LIMIT[3]);
  
  Serial.println("");
}
