//***************************************************
// 
// Teensy Synth DIY Workshop 
//
// Testing all the potentiometers
//
//
//***************************************************

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// useful header - do not remove
#include "DIYSynthWorkshop.h"  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Setup: The stuff in here is executed 
// by Teensy only once at startup
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {

   // setup input knobs to control the synth parameters
  setupKnobs();
  
  // setup serial communication with your laptop to print some
  // debug info
  Serial.begin(9600);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Loop: the stuff in here is executed by Teensy
// in an endless loop at maximum speed
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {

  // do not remove this
  updateKnobs();
  
  float val14 = readKnob(14);
  float val15 = readKnob(15);
  float val16 = readKnob(16);
  float val17 = readKnob(17);
  float val18 = readKnob(18);
  float val19 = readKnob(19);
  float val22 = readKnob(22);
  
  // Plot the value in the Serial Plotter
  Serial.print("14:"); Serial.print(val14);
  Serial.print(" 15:"); Serial.print(val15);
  Serial.print(" 16:"); Serial.print(val16);
  Serial.print(" 17:"); Serial.print(val17);
  Serial.print(" 18:"); Serial.print(val18);
  Serial.print(" 19:"); Serial.print(val19);
  Serial.print(" 22:"); Serial.print(val22);
  Serial.println(" ");
  
  delay(5);  
}
