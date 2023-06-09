//***************************************************
// 
// Teensy Synth DIY Workshop 
//
//  Pin 1. connect it to a metal surface
//  Pin 14 - Freq Knob
//
//***************************************************

// useful header - do not remove
#include "DIYSynthWorkshop.h"  
 
// FastTouch Library from Adrian Freed 2019
#include "FastTouch.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=133.00000381469727,121.4444465637207
AudioFilterStateVariable VCF;        //xy=335.44445419311523,128.44445610046387
AudioAmplifier           master;           //xy=756.7500114440918,127.75000286102295
AudioOutputI2S           i2s1;           //xy=930.2222557067871,130.66667366027832
AudioConnection          patchCord3(waveform1, 0, VCF, 0);
AudioConnection          patchCord6(VCF, 0, master, 0);
AudioConnection          patchCord9(master, 0, i2s1, 0);
AudioConnection          patchCord10(master, 0, i2s1, 1);
// GUItool: end automatically generated code

Smoothed<float> touch;

void setup() {

  // setup input knobs to control the synth parameters
  setupKnobs();
    
  // Allocate memory for the audio processing - do not remove this line!
  AudioMemory(50);

  // setup serial communication for debugging
  Serial.begin(9600);

  // setup waveform1 module
  waveform1.begin( 0.5, 100, WAVEFORM_SAWTOOTH );

  // touch module
  touch.begin(SMOOTHED_AVERAGE, 10); 

  master.gain(1);
}

//***************************************************
void loop() {

  // do not remove this
  updateKnobs();

  // read touch pad connected to pin 1
  touch.add(fastTouchRead(11));
  float touchValue = touch.get();
  Serial.println(touchValue);
  
  // Set Oscillator Frequency
  //float val = map( readKnob(14),0.0, 1023.0, 0.0, 1.0 );

  //freq controlled by touch
  float val = map( touchValue,12.0, 70.0, 0.0, 1.0 );
  float freq = (powf(val,2)*2000.0);
  waveform1.frequency(freq );
  
  // VCF CUTOFF FREQ Controlled By Proximity
//  float cutoff = map( touchValue, 0.0, 100.0, 0.0, 8000.0 );

  float cutoff = map( readKnob(16), 0.0, 1023.0, 0.0, 8000.0 );
  VCF.frequency( 200.f + cutoff);

  // VCA GAIN Controlled by Proximity
  
  // gate the gain
  //touchValue = touchValue < 30.f ? 0.f : touchValue;
  //touchValue = max( ( touchValue - 30.f ) / 30.f,0.0);
  //float amp = map( touchValue, 0.f, 1.f, 0.0, 1.0 );
  //master.gain(amp);
  
  delay(5);  
}
