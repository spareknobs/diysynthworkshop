//***************************************************
// 
// Teensy Synth DIY Workshop 
//
//***************************************************

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=382,454
AudioOutputI2S           i2s1;           //xy=799,460
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
// GUItool: end automatically generated code

void setup() {
  AudioMemory(50);
  waveform1.begin( 0.2, 300, WAVEFORM_SINE );
}

void loop() {
  waveform1.frequency(random(600));
  delay(150);
}
