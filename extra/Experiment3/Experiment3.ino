#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform3;      //xy=188.75001525878906,265.75
AudioSynthWaveformModulated waveformMod1;   //xy=457.74999237060547,103.74999904632568
AudioSynthWaveform       waveform2;      //xy=507.7500343322754,510.7500247955322
AudioFilterLadder        ladder1;        //xy=680.7499809265137,302.75003242492676
AudioEffectChorus        chorus1;        //xy=845.75,142.75
AudioOutputI2S           i2s1;           //xy=911.7500267028809,303.75000190734863
AudioConnection          patchCord1(waveformMod1, 0, ladder1, 0);
AudioConnection          patchCord2(waveform2, 0, ladder1, 1);
AudioConnection          patchCord3(ladder1, 0, waveformMod1, 0);
AudioConnection          patchCord4(ladder1, chorus1);
AudioConnection          patchCord5(chorus1, 0, i2s1, 0);
AudioConnection          patchCord6(chorus1, 0, i2s1, 1);
// GUItool: end automatically generated code


// Number of samples in each delay line
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
// Allocate the delay lines for left and right channels
short l_delayline[CHORUS_DELAY_LENGTH];
short r_delayline[CHORUS_DELAY_LENGTH];

void setup() {

  AudioMemory(50);
  
  //waveform1.begin(1.0,6.0,WAVEFORM_SAMPLE_HOLD);
  waveform2.begin(1.0,50.0,WAVEFORM_SAMPLE_HOLD);
  waveform3.begin(1.0,500.0,WAVEFORM_TRIANGLE);
  waveformMod1.begin(0.5,500,WAVEFORM_SINE);
  waveformMod1.frequencyModulation(10);
  ladder1.octaveControl(4);
//  combine1.setCombineMode(AudioEffectDigitalCombine::OR);
  //pink1.amplitude(1.0);
  if(!chorus1.begin(l_delayline,CHORUS_DELAY_LENGTH,3)) {
    Serial.println("AudioEffectChorus -  begin failed");
    while(1);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(25);

}
