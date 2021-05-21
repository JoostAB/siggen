#include <freqpot.h>

FreqPot::FreqPot() {
  for (int i = 0; i < FREQPOT_SAMPLE_CNT; i++) {
    this->freqPotSamples[i] = 0;
  }
}

void FreqPot::scanPot() {
  freqPotTotal = freqPotTotal - freqPotSamples[freqPotSampleIdx];
  // read from the sensor:
  freqPotSamples[freqPotSampleIdx] = analogRead(FREQ_POT);
  // add the reading to the total:
  freqPotTotal = freqPotTotal + freqPotSamples[freqPotSampleIdx];
  // advance to the next position in the array:
  freqPotSampleIdx++;

  // if we're at the end of the array...
  if (freqPotSampleIdx >= FREQPOT_SAMPLE_CNT) {
    // ...wrap around to the beginning:
    freqPotSampleIdx = 0;
  }
}

int FreqPot::getAvg() {
  return freqPotTotal / FREQPOT_SAMPLE_CNT;
}