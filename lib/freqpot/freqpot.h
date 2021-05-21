#ifndef _FREQPOT_H
#define _FREQPOT_H

#include <Arduino.h>
#define FREQPOT_PIN 4
#define FREQPOT_SAMPLE_CNT 50


int freqPotSamples[FREQPOT_SAMPLE_CNT];
int freqPotSampleIdx = 0;
int freqPotTotal = 0;
int freqPot = 0;

void freqPotInit() {
  for (int i = 0; i < FREQPOT_SAMPLE_CNT; i++) {
    freqPotSamples[i] = 0;
  }
}

int getAvgFreqPotValue() {
  freqPotTotal = freqPotTotal - freqPotSamples[freqPotSampleIdx];
  // read from the sensor:
  freqPotSamples[freqPotSampleIdx] = analogRead(FREQPOT_PIN);
  // add the reading to the total:
  freqPotTotal = freqPotTotal + freqPotSamples[freqPotSampleIdx];
  // advance to the next position in the array:
  freqPotSampleIdx++;

  // if we're at the end of the array...
  if (freqPotSampleIdx >= FREQPOT_SAMPLE_CNT) {
    // ...wrap around to the beginning:
    freqPotSampleIdx = 0;
  }

  // return freqPotTotal / FREQPOT_SAMPLE_CNT;
  // Even more smoothening
  freqPot = ((9*freqPot) + (freqPotTotal / FREQPOT_SAMPLE_CNT)) / 10;
  return freqPot;
}

#endif // _FREQPOT_H