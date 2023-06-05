//***************************************************
// 
// Teensy Synth DIY Workshop 
//
// A set of helpful stuff
// rmarogna 2021
//
//  TEENSY to PCM5102 connections:
//  BCLK1 —> BCK
//  LRCLK1 —> LCK
//  OUT1A —> DIN
//
//
//***************************************************
 

#include <Smoothed.h>  
#include <Wire.h>

int loop_ms = 5; 
int smoothersize = 30;

//  Available Teensy AnalogIn Pins:
//  14. A0 -> Knob 14
//  15. A1 -> Knob 15
//  16. A2 -> Knob 16
//  17. A3 -> Knob 17
//  18. A4 -> Knob 18
//  19. A5 -> Knob 19
//  22. A8 -> Knob 22
static const int cNumKnobs=7;
Smoothed <float> knob[cNumKnobs]; 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// callme @ setup
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setupKnobs() {

  // setup analog inputs pins
  pinMode(14,INPUT);
  pinMode(15,INPUT);
  pinMode(16,INPUT);
  pinMode(17,INPUT);
  pinMode(18,INPUT);
  pinMode(19,INPUT);
  pinMode(22,INPUT);

  // setup inputs smoothers
  for (int i=0; i<cNumKnobs; ++i){
    knob[i].begin(SMOOTHED_AVERAGE, smoothersize);  
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Aux funct to read smoothed analog value 
// arg is pin to make it easier to check 
// consistency with hardware
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float readKnob( int pinNumber ){

    switch (pinNumber)
    {
        case 14: return knob[0].get(); break;
        case 15: return knob[1].get(); break;
        case 16: return knob[2].get(); break;
        case 17: return knob[3].get(); break;
        case 18: return knob[4].get(); break;
        case 19: return knob[5].get(); break;
        case 22: return knob[6].get(); break;
    
    default:
    return -666; // should not happen!
        break;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Callme @ loop rate
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void updateKnobs(){
    knob[0].add( analogRead(14) );
    knob[1].add( analogRead(15) );
    knob[2].add( analogRead(16) );
    knob[3].add( analogRead(17) );
    knob[4].add( analogRead(18) );
    knob[5].add( analogRead(19) );
    knob[6].add( analogRead(22) );  
}


// Some Aux Modules

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// A Simple LFO  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int lfo_timer=0;
float lfo_out=0.0;

float LFO(float rate,float amp,float shape){
  
  if (rate<0.01f) return 1.f; // bypass @ 0 rate
  
  int lfo_period = (int)roundf(1.0/rate * 1000.0 / loop_ms);
  int lfo_attack = (int)roundf(lfo_period*shape);
  int lfo_release = lfo_period-lfo_attack;
  float step = lfo_timer <= lfo_attack ? 1.f/lfo_attack : -1.f/lfo_release;
  lfo_out += step;
  lfo_out = lfo_out < 0.f ? 0.f : lfo_out;
  lfo_out = lfo_out > 1.f ? 1.f : lfo_out;
  lfo_timer = ++lfo_timer % lfo_period;
  
  return lfo_out*amp;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// A Simple Random Sequencer - 
// returns a freq ratio (to be multiplied by base_freq)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static const int scaleSize = 6;
    static const float minorPent[scaleSize] = {1, 6.f/5.f, 4.f/3.f, 3.f/2.f, 9.f/5.f, 2};

class RandomPitchSequencer 
{
    
public:

    RandomPitchSequencer(){}
    ~RandomPitchSequencer(){}
    
  float GetPitch( float rate, int noctaves, float scale=0 ){
    int period = (int)roundf(1.0/rate * 1000.0 / loop_ms);
    if (randseq_timer++ >= period ){
      noctaves = max(noctaves,1) + 1;
      int index = random(0,scaleSize); 
      int mult = random(1,noctaves);
      fratio = minorPent[index] * mult;   
      randseq_timer=0;
      //Serial.println(mult);
    }
  
    return fratio;
  }
    
private:
    int randseq_timer{0};
    float fratio{1.f};
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// A Simple Random Sequencer -
// returns a freq ratio (to be multiplied by base_freq)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*const int scaleSize = 6;
const float minorPent[scaleSize] = {1, 6.f/5.f, 4.f/3.f, 3.f/2.f, 9.f/5.f, 2};
int randseq_timer=0;
float fratio=1.f;

float RandomPitchSequencer( float rate, int noctaves, float scale=0 ){
    int period = (int)roundf(1.0/rate * 1000.0 / loop_ms);
    if (randseq_timer++ >= period ){
        noctaves = max(noctaves,1) + 1;
        int index = random(0,scaleSize);
        int mult = random(1,noctaves);
        fratio = minorPent[index] * mult;
        randseq_timer=0;
        Serial.println(mult);
    }
    
    return fratio;
}*/
