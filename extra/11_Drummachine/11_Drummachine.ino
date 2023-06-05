// Minimal random drummachine
//
// Pots:
// 14 - drum1 gain
// 15 - drum2 gain
// 16 - drum3 gain
// 17 - drum4 gain

// useful header - do not remove
#include "DIYSynthWorkshop.h"  

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum2;          //xy=399,244
AudioSynthSimpleDrum     drum3;          //xy=424,310
AudioSynthSimpleDrum     drum1;          //xy=431,197
AudioSynthSimpleDrum     drum4;          //xy=464,374
AudioMixer4              mixer1;         //xy=737,265
AudioOutputI2S           i2s1;           //xy=979,214
AudioConnection          patchCord1(drum2, 0, mixer1, 1);
AudioConnection          patchCord2(drum3, 0, mixer1, 2);
AudioConnection          patchCord3(drum1, 0, mixer1, 0);
AudioConnection          patchCord4(drum4, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
// GUItool: end automatically generated code

long int prevTimeStamp = 0;
long int intervalMs = 100; // ms

void setup() {

  AudioMemory(50);

  AudioNoInterrupts();

  drum1.frequency(60);
  drum1.length(100);
  drum1.secondMix(0.0);
  drum1.pitchMod(0.0);
  
  drum2.frequency(200);
  drum2.length(50);
  drum2.secondMix(0.0);
  drum2.pitchMod(0.0);

  drum3.frequency(1000);
  drum3.length(20);
  drum3.secondMix(0.0);
  drum3.pitchMod(0.0);

  drum4.frequency(2000);
  drum4.length(10);
  drum4.secondMix(0.0);
  drum4.pitchMod(0.0);

  mixer1.gain(0,0.25);
  mixer1.gain(1,0.2);
  mixer1.gain(2,0.1);
  mixer1.gain(3,0.1);

    // setup input knobs to control the synth parameters
  setupKnobs();
  
  AudioInterrupts();

}

void loop() {

  updateKnobs();
  
  mixer1.gain(0,map( readKnob(14),0.0, 1023.0, 0.0, 1.0 ));
  mixer1.gain(1,map( readKnob(15),0.0, 1023.0, 0.0, 1.0 ));
  mixer1.gain(2,map( readKnob(16),0.0, 1023.0, 0.0, 1.0 ));
  mixer1.gain(3,map( readKnob(17),0.0, 1023.0, 0.0, 1.0 ));
  
  // a simple random sequencer  
  if( millis() - prevTimeStamp >= intervalMs ){
     
     prevTimeStamp = millis();
    
     if ( random(0,4)==0 ) drum1.noteOn();
     
     if ( random(0,2)==0 ) drum2.noteOn();

     if ( random(0,4)==0 ) drum3.noteOn();

     if ( random(0,4)==0 ) drum4.noteOn();
   }

  delay(5);  
}
