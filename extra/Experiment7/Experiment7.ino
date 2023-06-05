#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSineModulated sine_fm1;       //xy=346.75,145.75
AudioSynthWaveformSineModulated sine_fm5;       //xy=356.74999237060547,484.7500057220459
AudioSynthWaveformSineModulated sine_fm6;       //xy=444.25,553.25
AudioSynthWaveformSineModulated sine_fm3;       //xy=490.75,326.75
AudioMixer4              mixer2;         //xy=580.25,454.25
AudioSynthWaveformSineModulated sine_fm2;       //xy=585.7500038146973,160.7499942779541
AudioSynthWaveformSineModulated sine_fm4;       //xy=684.7500114440918,370.74999141693115
AudioMixer4              mixer1;         //xy=926.7500267028809,307.75
AudioOutputI2S           i2s1;           //xy=1071.7499961853027,309.7500066757202
AudioConnection          patchCord1(sine_fm1, sine_fm2);
AudioConnection          patchCord2(sine_fm5, 0, mixer2, 0);
AudioConnection          patchCord3(sine_fm6, 0, mixer2, 1);
AudioConnection          patchCord4(sine_fm3, 0, mixer1, 1);
AudioConnection          patchCord5(sine_fm3, sine_fm5);
AudioConnection          patchCord6(mixer2, sine_fm4);
AudioConnection          patchCord7(sine_fm2, sine_fm3);
AudioConnection          patchCord8(sine_fm2, 0, mixer1, 0);
AudioConnection          patchCord9(sine_fm4, sine_fm1);
AudioConnection          patchCord10(sine_fm4, 0, mixer1, 2);
AudioConnection          patchCord11(mixer1, 0, i2s1, 0);
AudioConnection          patchCord12(mixer1, 0, i2s1, 1);
// GUItool: end automatically generated code

void setup() {

  AudioMemory(80);
  
  sine_fm1.frequency(560);
  sine_fm2.frequency(700);
  sine_fm3.frequency(0.23);
  sine_fm4.frequency(600);
  sine_fm5.frequency(400);
  sine_fm6.frequency(0.11);
  
  mixer1.gain(0,0.5);
  mixer1.gain(1,0.5);
  mixer1.gain(2,0.5);

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(25);

}
