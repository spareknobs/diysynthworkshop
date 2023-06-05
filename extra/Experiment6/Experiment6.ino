#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform3;      //xy=179.75001525878906,272.75000190734863
AudioSynthWaveformModulated waveformMod1;   //xy=278.75,469.75
AudioSynthWaveformSineModulated sine_fm1;       //xy=346.75,145.75
AudioSynthNoisePink      pink1;          //xy=375.75,606.75
AudioSynthWaveformSineModulated sine_fm2;       //xy=429.75,247.75
AudioSynthWaveformSineModulated sine_fm3;       //xy=490.75,326.75
AudioSynthWaveformSineModulated sine_fm4;       //xy=501.74999618530273,386.74999809265137
AudioSynthWaveformSineModulated sine_fm5;       //xy=550.75,561.75
AudioEffectDigitalCombine combine3;       //xy=725.7500152587891,553.7500143051147
AudioEffectDigitalCombine combine1;       //xy=747.75,213.75
AudioEffectDigitalCombine combine2;       //xy=765.7500114440918,302.74999141693115
AudioMixer4              mixer1;         //xy=926.7500267028809,307.75
AudioMixer4              mixer2;         //xy=952.75,491.75
AudioOutputI2S           i2s1;           //xy=1071.7499961853027,309.7500066757202
AudioConnection          patchCord1(waveform3, sine_fm1);
AudioConnection          patchCord2(waveformMod1, sine_fm4);
AudioConnection          patchCord3(waveformMod1, 0, mixer2, 2);
AudioConnection          patchCord4(sine_fm1, sine_fm2);
AudioConnection          patchCord5(sine_fm1, 0, combine3, 0);
AudioConnection          patchCord6(pink1, sine_fm5);
AudioConnection          patchCord7(sine_fm2, sine_fm3);
AudioConnection          patchCord8(sine_fm2, 0, combine1, 0);
AudioConnection          patchCord9(sine_fm3, 0, combine2, 0);
AudioConnection          patchCord10(sine_fm3, 0, combine1, 1);
AudioConnection          patchCord11(sine_fm4, 0, combine2, 1);
AudioConnection          patchCord12(sine_fm5, 0, combine3, 1);
AudioConnection          patchCord13(combine3, 0, mixer2, 3);
AudioConnection          patchCord14(combine1, 0, mixer1, 0);
AudioConnection          patchCord15(combine2, 0, mixer1, 1);
AudioConnection          patchCord16(mixer1, 0, i2s1, 0);
AudioConnection          patchCord17(mixer2, 0, i2s1, 1);
// GUItool: end automatically generated code


void setup() {

  AudioMemory(80);
  
  sine_fm1.frequency(400);
  sine_fm2.frequency(600);
  sine_fm3.frequency(210);
  sine_fm4.frequency(310);
  sine_fm5.frequency(540);
  
  waveform3.begin(1.0,16.0,WAVEFORM_SAMPLE_HOLD);
  
  waveformMod1.begin(0.5,10,WAVEFORM_SAMPLE_HOLD);
  waveformMod1.frequencyModulation(10);
  //ladder1.octaveControl(4);
  combine1.setCombineMode(AudioEffectDigitalCombine::OR);
  combine2.setCombineMode(AudioEffectDigitalCombine::OR);
  combine3.setCombineMode(AudioEffectDigitalCombine::OR);
  pink1.amplitude(1.0);
  
  mixer1.gain(0,0.5);
  mixer1.gain(1,0.5);
  mixer1.gain(2,0.5);
  mixer2.gain(0,0.5);
  mixer2.gain(2,0.5);
  mixer2.gain(3,0.5);

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(25);

}
