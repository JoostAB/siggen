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

// void plotValue(int val, int max) {
//     sendSignalSample(val, DAC_CHANNEL_1);
// }

void loop() {

    // freqPot = ((9*freqPot) + getAvgFreqPotValue()) / 10;
    // Serial.println(freqPot);

    static unsigned long prevSwitch = 0;
    static int waveType = 0;
    
    if (millis() - prevSwitch > 5000) {
        waveType ++;
        if (waveType > MaxWaveTypes) waveType = 0;
        prevSwitch = millis();
    }

    int val;

    if (waveType == MaxWaveTypes) {
        // Get input from microphone
        val = map(analogRead(MICPIN),0,4096,0,255);
    } else {
        val = getMappedNextSampleByIdx(waveType);
    }
    sendSignalSample(val, DAC_CHANNEL_1);    
}