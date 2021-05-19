#ifndef _FREQPOT_H
#define _FREQPOT_H

#include <Arduino.h>
#define FREQ_POT 4

const int numFreqPotSamples = 50;

int freqPotSamples[numFreqPotSamples];
int freqPotSampleIdx = 0;
int freqPotTotal = 0;

void freqPotInit() {
  for (int i = 0; i < numFreqPotSamples; i++) {
    freqPotSamples[i] = 0;
  }
}

int getAvgFreqPotValue() {
    freqPotTotal = freqPotTotal - freqPotSamples[freqPotSampleIdx];
  // read from the sensor:
  freqPotSamples[freqPotSampleIdx] = analogRead(FREQ_POT);
  // add the reading to the total:
  freqPotTotal = freqPotTotal + freqPotSamples[freqPotSampleIdx];
  // advance to the next position in the array:
  freqPotSampleIdx++;

  // if we're at the end of the array...
  if (freqPotSampleIdx >= numFreqPotSamples) {
    // ...wrap around to the beginning:
    freqPotSampleIdx = 0;
  }

  return freqPotTotal / numFreqPotSamples;
}

#endif // _FREQPOT_H