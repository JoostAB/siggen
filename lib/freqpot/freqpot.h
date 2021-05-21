#pragma once
#ifndef _FREQPOT_H
#define _FREQPOT_H

#include <Arduino.h>
#define FREQ_POT 4
#define FREQPOT_SAMPLE_CNT 50

class FreqPot {
  public:
    FreqPot();

    void scanPot();
    int getAvg();

  private:
//    const int numFreqPotSamples = 50;

    int freqPotSamples[FREQPOT_SAMPLE_CNT];
    int freqPotSampleIdx = 0;
    int freqPotTotal = 0;
    int freqPotAvg = 0;
    
};

// FreqPot fp;

// int getAvgFreqPotValue() {
//   fp.scanPot();
//   return fp.getAvg();
// }

#endif // _FREQPOT_H