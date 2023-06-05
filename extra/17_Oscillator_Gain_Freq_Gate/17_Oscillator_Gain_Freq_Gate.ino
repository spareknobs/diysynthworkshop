//***************************************************
// 
// Teensy Synth DIY Workshop 
//
// Tutorial #4
//
// An Oscillator with gain and frequency controls
// and a Button to switch it on/off
// 
// Wiring:
//        Gain Pot on Pin 14
//        Frequency Pot on Pin 15
//        Button between Pin 1 and GND
//
// r.marogna 2021
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

// useful header - do not remove
#include "DIYSynthWorkshop.h"  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Setup: The stuff in here is executed 
// by Teensy only once at startup
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {

  // setup input knobs to control the synth parameters
  setupKnobs();

  // setup button on pin 1
  pinMode(1, INPUT_PULLUP);
  
  // Allocate memory for the audio processing - do not remove this line!
  AudioMemory(50);

  Serial.begin(9600);
  waveform1.begin( 0.01, 100, WAVEFORM_SINE );
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Setup: The stuff in here is executed 
// by Teensy only once at startup
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {

  // do not remove this
  updateKnobs();

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Read button status and convert it to 
  // 0 when depressed, 1 when pressed
  float gate = 1.f - (float)digitalRead(1);
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Set Gain from Pot 14
  
  // Read Potentiometer connected at pin 14
  // the value you get is in the range [0,1023]
  float pot14 = readKnob(14);

  // Map the value from the range [0,1023] to the desired gain range
  float amp = map( pot14, 0.0, 1023.0, 0.0, 0.5 );

  // Set the oscillator gain according to pot14 and gate 
  waveform1.amplitude( amp * gate );

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Set Frequency from Pot 15
  
  // Read Potentiometer connected at pin 15
  // the value you get is in the range [0,1023]
  float pot15 = readKnob(15);

  // Map pot value to frequency
  // since we are dealing with a frequency, let's bend the curve a little
  float freq = 20.0 + powf( pot15 / 1023.0, 4 ) * 4000.0;
  
  // Set the oscillator frequency
  waveform1.frequency( freq );

  delay(5);
}
