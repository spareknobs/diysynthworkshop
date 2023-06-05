#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform3;      //xy=179.75001525878906,272.75000190734863
AudioSynthWaveformModulated waveformMod1;   //xy=367.74999237060547,191.74999523162842
AudioSynthWaveformSineModulated sine_fm1;       //xy=388.75,247.75
AudioSynthWaveform       waveform2;      //xy=507.7500343322754,510.7500247955322
AudioMixer4              mixer1;         //xy=575.75,191.75
AudioFilterLadder        ladder1;        //xy=680.7499809265137,302.75003242492676
AudioOutputI2S           i2s1;           //xy=911.7500267028809,303.75000190734863
AudioConnection          patchCord1(waveform3, sine_fm1);
AudioConnection          patchCord2(waveformMod1, 0, mixer1, 0);
AudioConnection          patchCord3(sine_fm1, 0, mixer1, 1);
AudioConnection          patchCord4(waveform2, 0, ladder1, 1);
AudioConnection          patchCord5(mixer1, 0, ladder1, 0);
AudioConnection          patchCord6(ladder1, 0, waveformMod1, 0);
AudioConnection          patchCord7(ladder1, 0, i2s1, 0);
AudioConnection          patchCord8(ladder1, 0, i2s1, 1);
// GUItool: end automatically generated code


void setup() {

  AudioMemory(50);
  
  //waveform1.begin(1.0,6.0,WAVEFORM_SAMPLE_HOLD);
  waveform2.begin(1.0,50.0,WAVEFORM_SAMPLE_HOLD);
  waveform2.begin(1.0,20.0,WAVEFORM_SAMPLE_HOLD);
  waveform3.begin(1.0,500.0,WAVEFORM_TRIANGLE);

  waveformMod1.begin(0.5,500,WAVEFORM_SINE);
  waveformMod1.frequencyModulation(10);
  
  ladder1.octaveControl(5);

//  combine1.setCombineMode(AudioEffectDigitalCombine::OR);
//  pink1.amplitude(0.5);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(25);

}
