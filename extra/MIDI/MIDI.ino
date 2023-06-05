//***************************************************
// 
// Teensy Synth DIY Workshop v. Nov 2022
//
// How to add MIDI control to the synth
//
// note: remember to set Tools: USB Type: Serial+MIDI
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


//-------------------------------------------------------------------
// MIDI
static const float gcNoteFreqs[128] = 
{8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 
13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 
23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 
41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 
73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 
130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 
220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 
391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 
698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659,
1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 
1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 
3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 
5587.652, 5919.911, 6271.927, 6644.875,7040, 7458.62, 7902.133, 8372.018, 8869.844,
9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};

byte mCurNote = 0;
byte mCurVelocity = 0;
static const byte gcKeysBufferSize = 32; // keys buffer
static byte mKeysBuffer[gcKeysBufferSize];
static byte mBufSize = 0;

void ManageKey( byte note, bool playNote ) {
    
  // Add Note
  if ( playNote == true && ( mBufSize < gcKeysBufferSize ) ) {

    ///*** THIS IS WHERE WE USE THE MIDI NOTE TO SET THE OSC FREQ ****
     float freq = gcNoteFreqs[note];
      osc.frequency(freq );
      
    mKeysBuffer[mBufSize] = note;
    mBufSize++;
    return;
  }

  // Remove Note
  else if ( playNote == false ) 
  {
    if ( mBufSize == 0 ){
      
      return;
    }

    for ( byte found = 0; found < mBufSize; found++ ) {

      if (mKeysBuffer[found] == note) {
        
        // shift back the notes in the queue
        for (byte gap = found; gap < (mBufSize - 1); gap++) {
          mKeysBuffer[gap] = mKeysBuffer[gap + 1];
        }
        mBufSize--;
        mKeysBuffer[mBufSize] = 255; // set to invalid
        
        if ( mBufSize != 0 ) {
          // retrigger prev key in buffer
          ///*** THIS IS WHERE WE USE THE MIDI NOTE TO SET THE OSC FREQ ****
          float freq = gcNoteFreqs[mKeysBuffer[mBufSize - 1]];
          osc.frequency(freq );
          return;
        }
        else {
          
          return;
        }
      }
    }
  }
}

void NoteOn(byte channel, byte note, byte velocity) {
  mCurNote = note;
  mCurVelocity = velocity;
  ManageKey(note, true);
}

void NoteOff(byte channel, byte note, byte velocity){
  ManageKey(note, false);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Buttons
#include <Bounce.h>

Bounce button1 = Bounce( 1, 5 ); 
bool button1State = 0;

Bounce button2 = Bounce( 2, 5 ); 
bool button2State = 0;

Bounce button3 = Bounce( 3, 5 ); 
bool button3State = 0;

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
  pinMode(1, INPUT_PULLUP);

  // setup button 2 on pin 2
  pinMode(2, INPUT_PULLUP);

  // setup button 3 on pin 3
  pinMode(3, INPUT_PULLUP);

  // setup LED pin
  pinMode(5,OUTPUT);

  usbMIDI.setHandleNoteOff(NoteOff);
  usbMIDI.setHandleNoteOn(NoteOn); 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Loop: the stuff in here is executed by Teensy
// in an endless loop
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {

  // read midi messages from usb
  usbMIDI.read();
 
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

  // read osc gain from knob at pin 14
  float amp = map( readKnob(14),0.0, 1023.0, 0.0, 1.0 );
  osc.amplitude(amp);
  
  // read osc rate from knob at pin 15
  float val = map( readKnob(15),0.0, 1023.0, 0.0, 1.0 );
  float freq = (powf(val,4)*2000.0 + 30.0) * fratio;
  //osc.frequency(freq ); controlled by MIDI now

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
  
  if (button1.fallingEdge()){
    button1State = !button1State;
    Serial.print("Switch Button1: ");
    Serial.println(button1State);
    lfo2osc.gain(button1State);
    
  }

  // Read button status 
  button2.update();
  
  if (button2.fallingEdge()){
    button2State = !button2State;
    Serial.print("Switch Button2: ");
    Serial.println(button2State);
    lfo2filter.gain(button2State);
  }

   // Read button status 
  button3.update();
  
  if (button3.fallingEdge()){
    button3State = !button3State;
    Serial.print("Switch Button3: ");
    Serial.println(button3State);
  }
  
  delay(5);  
}
