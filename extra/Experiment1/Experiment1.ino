#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoisePink      pink1;          //xy=245.75,193.75
AudioSynthWaveform       waveform1;      //xy=258.75,95.75
AudioSynthWaveform       waveform2;      //xy=433.75002670288086,180.75001049041748
AudioSynthWaveformModulated waveformMod1;   //xy=457.74999237060547,103.74999904632568
AudioFilterLadder        ladder1;        //xy=650.7500114440918,181.75000953674316
AudioEffectDigitalCombine combine1;       //xy=679.75,334.75
AudioOutputI2S           i2s1;           //xy=971.7500267028809,179.7500057220459
//AudioConnection          patchCord1(pink1, 0, waveformMod1, 1);
AudioConnection          patchCord2(pink1, 0, combine1, 0);
AudioConnection          patchCord3(waveform1, 0, waveformMod1, 0);
AudioConnection          patchCord4(waveform2, 0, ladder1, 1);
AudioConnection          patchCord5(waveformMod1, 0, combine1, 1);
AudioConnection          patchCord6(ladder1, 0, i2s1, 0);
AudioConnection          patchCord7(ladder1, 0, i2s1, 1);
AudioConnection          patchCord8(combine1, 0, ladder1, 0);
// GUItool: end automatically generated code


void setup() {

  AudioMemory(30);
  
  waveform1.begin(1.0,6.0,WAVEFORM_SAMPLE_HOLD);
  waveform2.begin(1.0,5.0,WAVEFORM_SAMPLE_HOLD);
  waveformMod1.begin(0.5,500,WAVEFORM_SAWTOOTH);
  waveformMod1.frequencyModulation(10);
  ladder1.octaveControl(4);
  combine1.setCombineMode(AudioEffectDigitalCombine::MODULO);
  pink1.amplitude(1.0);

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(25);

}
