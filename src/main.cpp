#include <Arduino.h>
#include <sampler.h>
#include <freqpot.h>
#include <sigout.h>
#include <driver/dac.h>

#define MICPIN 15

void setup() {
   Serial.begin(115200); 
  sigOutInit();
  samplerInit();
}

static void checkChanged(int val) {
  static int prevVal = 0;
  if (val != prevVal) {
    Serial.println("Changed");
    prevVal = val;
  }
}

void loop() {
  // int tst = getAvgFreqPotValue();
  // checkChanged(tst);
  // Serial.println(tst);
  
  static unsigned long prevSwitch = 0;
  static int waveType = 0;
  
  int val;

  if (millis() - prevSwitch > 5000) {
      waveType ++;
      if (waveType > MaxWaveTypes) waveType = 0;
      prevSwitch = millis();
  }

  if (waveType == MaxWaveTypes) {
      val = map(analogRead(MICPIN),0,4096,0,255);
  } else {
      val = getMappedNextSampleByIdx(waveType);            
  }

  //val = getMappedNextSampleByType(square);
  
  //Serial.println(val);
  sendSignalSample(val, DAC_CHANNEL_1);
}