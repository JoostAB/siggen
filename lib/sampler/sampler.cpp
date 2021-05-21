// #include <sampler.h>

// void Sampler::begin() {
//   timer = timerBegin(0, 80, true);                  // Prescaler to 80 (80Mhz / 80 -> 1 Mhz timer)
//   timerAttachInterrupt(timer, &isrSampler, true);      // Attach timer to isr
//   //timerAlarmWrite(timer, 1000000, true);          // Set freq of interupt (1Mhz / 1000000 -> 1Hz)
//   timerAlarmWrite(timer, 1000000 / (freq * Num_Samples) , true);
//   timerAlarmEnable(timer);
// }

// void Sampler::isrSampler() {
//   sampleCtr ++;
//   if (sampleCtr >= Num_Samples) sampleCtr = 0;
// }

// int Sampler::getMappedNextSample(wavetype type) {

// }