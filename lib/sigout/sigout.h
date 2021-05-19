#ifndef _SIGOUT_H
#define _SIGOUT_H

#include <Arduino.h>
#include <driver/dac.h>

void sigOutInit() {
  dac_output_enable(DAC_CHANNEL_1);
  dac_output_enable(DAC_CHANNEL_2);
}

void sendSignalSample(int val) {
  sendSignalSample(val, DAC_CHANNEL_1);
}

void sendSignalSample(int val, dac_channel_t channel) {
  if (val < 256) dac_output_voltage(channel, val);
}

#endif // _SIGOUT_H