#include <Arduino.h>
#include <sampler.h>
#include <freqpot.h>
#include <sigout.h>
#include <driver/dac.h>

#define MICPIN 15


// volatile int sampleCtr = 0;
// hw_timer_t * timer = NULL;
// portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
// //int freq = 440; // 440 Hz = A
// int freq = 1000; // 1kHz
int freqPot = 0;

// void isrSample() {
//     sampleCtr ++;
//     if (sampleCtr >= Num_Samples) sampleCtr = 0;
// }

void setup() {
  
  Serial.begin(115200); 
  sigOutInit();
  samplerInit();
}

void plotValue(int val, int max) {
    // Serial.print("Min:0,Mic:");
    // Serial.print(val);
    // Serial.print(",Max:");
    // Serial.println(max);
    sendSignalSample(val);
}

void loop() {
    //freqPot = ((99*freqPot) + analogRead(FREQ_POT)) / 100;
    freqPot = ((9*freqPot) + getAvgFreqPotValue()) / 10;
    Serial.println(freqPot);
    //Serial.println(getAvgFreqPotValue());
    static unsigned long prevSwitch = 0;
    static int waveType = 0;
    
    if (millis() - prevSwitch > 5000) {
        waveType ++;
        if (waveType > MaxWaveTypes) waveType = 0;
        prevSwitch = millis();
    }

    if (waveType == MaxWaveTypes) {
        sendSignalSample(map(analogRead(MICPIN),0,4096,0,255));
    } else {
        // int val = WaveFormTable[waveType][sampleCtr];
        // if (waveType == sine) {
        //     val = map(val,0x40,0xC0,10,245);
        // } else {
        //     val = map(val,0,255,10,245);
        // }
        int val = getMappedNextSample(waveType);
        sendSignalSample(val);    
    }
}