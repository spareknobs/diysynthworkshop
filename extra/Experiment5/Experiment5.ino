#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform3;      //xy=179.75001525878906,272.75000190734863
AudioSynthNoisePink      pink1;          //xy=184.75000381469727,552.7499914169312
AudioSynthWaveformModulated waveformMod1;   //xy=204.75,413.7500219345093
AudioSynthWaveformSineModulated sine_fm1;       //xy=346.75,145.75
AudioSynthWaveformSineModulated sine_fm5;       //xy=366.7499885559082,560.7499904632568
AudioSynthWaveformSineModulated sine_fm2;       //xy=429.75,247.75
AudioSynthWaveformSineModulated sine_fm3;       //xy=490.75,326.75
AudioSynthWaveformSineModulated sine_fm4;       //xy=501.74999618530273,386.74999809265137
AudioEffectDigitalCombine combine3;       //xy=547.7500267028809,560.7499990463257
AudioMixer4              mixer1;         //xy=926.7500267028809,307.75
AudioOutputI2S           i2s1;           //xy=1071.7499961853027,309.7500066757202
AudioConnection          patchCord1(waveform3, sine_fm1);
AudioConnection          patchCord2(pink1, sine_fm5);
AudioConnection          patchCord3(waveformMod1, sine_fm4);
AudioConnection          patchCord4(sine_fm1, sine_fm2);
AudioConnection          patchCord5(sine_fm1, 0, combine3, 0);
AudioConnection          patchCord6(sine_fm5, 0, combine3, 1);
AudioConnection          patchCord7(sine_fm2, sine_fm3);
AudioConnection          patchCord8(sine_fm2, 0, mixer1, 0);
AudioConnection          patchCord9(sine_fm3, 0, mixer1, 1);
AudioConnection          patchCord10(sine_fm4, 0, mixer1, 3);
AudioConnection          patchCord11(combine3, 0, mixer1, 2);
AudioConnection          patchCord12(mixer1, 0, i2s1, 0);
AudioConnection          patchCord13(mixer1, 0, i2s1, 1);
// GUItool: end automatically generated code


void setup() {

  AudioMemory(100);
  sine_fm1.frequency(400);
  sine_fm2.frequency(200);
  sine_fm3.frequency(210);
  sine_fm4.frequency(110);
  sine_fm5.frequency(240);
  waveform3.begin(1.0,16.0,WAVEFORM_SAMPLE_HOLD);
  
  waveformMod1.begin(0.5,13,WAVEFORM_SAMPLE_HOLD);
  waveformMod1.frequencyModulation(10);
  
//  combine1.setCombineMode(AudioEffectDigitalCombine::OR);
//  combine2.setCombineMode(AudioEffectDigitalCombine::OR);
  combine3.setCombineMode(AudioEffectDigitalCombine::OR);
  pink1.amplitude(1.0);
  mixer1.gain(0,0.5);
  mixer1.gain(1,0.5);
  mixer1.gain(2,0.5);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(25);

}
