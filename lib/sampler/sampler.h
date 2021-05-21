#ifndef _SAMPLER_H
#define _SAMPLER_H

#include <Arduino.h>
#include <waves.h>

volatile int sampleCtr = 0;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
//int freq = 440; // 440 Hz = A
int freq = 1000; // 1kHz

void isrSampler() {
    sampleCtr ++;
    if (sampleCtr >= Num_Samples) sampleCtr = 0;
}

void samplerInit() {
  timer = timerBegin(0, 80, true);                  // Prescaler to 80 (80Mhz / 80 -> 1 Mhz timer)
  timerAttachInterrupt(timer, &isrSampler, true);      // Attach timer to isr
  //timerAlarmWrite(timer, 1000000, true);          // Set freq of interupt (1Mhz / 1000000 -> 1Hz)
  timerAlarmWrite(timer, 1000000 / (freq * Num_Samples) , true);
  timerAlarmEnable(timer);
}

int getNextSample(wavetype type) {
  return WaveFormTable[type][sampleCtr];
}

int getMappedNextSampleByType(wavetype type) {
  int val = getNextSample(type);
  if (type == sine) {
      val = map(val,0x40,0xC0,0,255);
  }
  return val;
}

int getMappedNextSampleByIdx(int t) {
  return getMappedNextSampleByType(static_cast<wavetype>(t));
}

#endif // _SAMPLER_H