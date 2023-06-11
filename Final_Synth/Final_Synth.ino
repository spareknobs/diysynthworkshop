//***************************************************
// 
// Teensy Synth DIY Workshop v. Nov 2022
//
// A Simple Full Synth Example
//
//
// Connection to Teensy:
//
//  Pin G  --> ground bus
//  Pin 3v --> 3v bus
//
//  Pin 5v --> dac board Vcc
//  Pin 20 --> dac board LCK
//  Pin 21 --> dac board BCK
//  Pin 7  --> dac board DIN
//
//  Pin 14 --> Potentiometer OSC GAIN 
//  Pin 15 --> Potentiometer OSC FREQ
//  Pin 16 --> Potentiometer FILTER CUTOFF
//  Pin 17 --> Potentiometer LFO RATE
//  Pin 18 --> Potentiometer SEQUENCER SPEED
//  Pin 19 --> Potentiometer SEQUENCER OCTAVES RANGE
//   [all connections to pots central pin]
//
//  Pin 1 --> Button 1 Osc freq modulation on/off
//  Pin 2 --> Button 2 Cutoff Modulation on/off
//  [the other pin of each button --> Ground]
//
//  Pin 5 --> resistor --> LED+
//  Led- --> Ground
//
//  dac board SCK --> Ground bus
//  dac board XMT --> 3v bus
//  dac board GND,FMT,SCL,DMP,FLT --> Ground bus
//
//***************************************************

// useful header - do not remove
#include "DIYSynthWorkshop.h"  

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;      //xy=175.5601348876953,308.89320945739746
AudioAmplifier           lfo2osc;           //xy=320.00451278686523,176.671049118042
AudioAnalyzeRMS          rms1;           //xy=363.0038948059082,427.003897190094
AudioAmplifier           lfo2filter;           //xy=471.1155776977539,311.11552143096924
AudioSynthWaveformModulated osc;   //xy=476.6712112426758,182.22658920288086
AudioFilterStateVariable filter1;        //xy=668.8933334350586,188.89325396219886
AudioOutputI2S           i2s1;           //xy=927.6457901000977,185.7009572982788
AudioConnection          patchCord1(lfo, lfo2filter);
AudioConnection          patchCord2(lfo, lfo2osc);
AudioConnection          patchCord3(lfo, rms1);
AudioConnection          patchCord4(lfo2osc, 0, osc, 0);
AudioConnection          patchCord5(lfo2filter, 0, filter1, 1);
AudioConnection          patchCord6(osc, 0, filter1, 0);
AudioConnection          patchCord7(filter1, 0, i2s1, 0);
AudioConnection          patchCord8(filter1, 0, i2s1, 1);
// GUItool: end automatically generated code



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sequencer
RandomPitchSequencer sequencer;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Buttons
#include <Bounce2.h>

Bounce button1 = Bounce(); 
bool button1State = 0;

Bounce button2 = Bounce(); 
bool button2State = 0;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Setup: The stuff in here is executed 
// by the Teensy only once at startup
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
  
  // Allocate memory for the audio processing - do not remove this line!
  // if your synth will become more complex, you may need to increase this value
  AudioMemory(50);

  // setup input knobs to control the synth parameters
  setupKnobs();
  
  // init serial communication with your laptop to debug
  Serial.begin(9600);

  // setup LFO module.args are level, frequency, shape
  lfo.begin( 0.5, 1.0, WAVEFORM_SAWTOOTH );

  // setup waveform1 module. args are level, frequency, shape
  osc.begin( 0.25, 150.0, WAVEFORM_SAWTOOTH );
  
  // set Fm range (in octaves)
  osc.frequencyModulation(4.0);
  
  filter1.frequency(2000);
  filter1.resonance(2.0);
  filter1.octaveControl(4);

  // LFO 2 Frequency Mod switch set to off (0)
  lfo2osc.gain(0);

  // LFO 2 Cutoff Mod switch set to off (0)
  lfo2filter.gain(0);

  // setup button 1 on pin 1
  button1.attach(1,INPUT_PULLUP); 
  button1.interval(25);

  // setup button 2 on pin 2
  button2.attach(2, INPUT_PULLUP);
  button2.interval(25);

  // setup LED pin
  pinMode(5,OUTPUT);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Loop: the stuff in here is executed by Teensy
// in an endless loop
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {

  // do not remove this
  updateKnobs();
  
  // LFO RATE

  // read lfo rate from knob at pin 17
  float rate = map( readKnob(17),0.0, 1023.0, 0.0, 1.0 );
  rate = powf(rate,4) * 200.f;
  lfo.frequency(rate);

  // declare the frequency ratio variable and set it to a default value of 1.0 
  // this will be modified by the sequencer, if active
  float fratio = 1.0; 
  
  // read sequencer rate from knob at pin 18
  float seqrate = map( readKnob(18),0.0, 1023.0, 0.1f, 16.f );
  int noctaves = map( readKnob(19),0.0, 1023.0, 0, 6 );
  
  // disables the sequencer if the octave range is at zero 
  if (noctaves>0){
    fratio = sequencer.GetPitch(seqrate,noctaves);
  }

  // read osc gain from knob at pin 14
  float amp = map( readKnob(14),0.0, 1023.0, 0.0, 1.0 );
  osc.amplitude(amp);
  
  // read osc rate from knob at pin 15
  float val = map( readKnob(15),0.0, 1023.0, 0.0, 1.0 );
  float freq = (powf(val,4)*2000.0 + 30.0) * fratio;
  osc.frequency(freq );

  // read filter cutoff frequency from knob at pin 16
  float cutoff = map( readKnob(16),0.0, 1023.0, 0.0, 12000.0 );
  filter1.frequency(50.f + cutoff);

  // control LED with LFO
  if (rms1.available()){
    float val = rms1.read(); 
    byte fadeValue = map(val,0.0,1.0,0,255);
    analogWrite(5, fadeValue);
  }

  // Read button status 
  button1.update();
  
  if (button1.fell()){
    button1State = !button1State;
    Serial.print("Switch Button1: ");
    Serial.println(button1State);

    // toggle the frequency modulation switch
    lfo2osc.gain(button1State);
  }

  // Read button status 
  button2.update();
  
  if (button2.fell()){
    button2State = !button2State;
    Serial.print("Switch Button2: ");
    Serial.println(button2State);

    // toggle the filter cutoff modulation switch
    lfo2filter.gain(button2State);
  }
  
  delay(5);  
}
