# DIY Synth Workshop

Repository of the Arduino code for the DIY Synth Workshop - 2023 Edition

spare knobs [2023]

- Click on CODE –> Download Zip, then Unzip  it in your favourite spot [ If you want, rename it (the folder, and the .ino file inside –  BUT use the same name for both!) ]

-  Install Arduino IDE + Teensy board libraries following these instructions:  https://www.pjrc.com/teensy/td_download.html

- Open Tools → Library Manager. Search for _Smoothed _. Install it.

- Connect the Teensy to your Laptop using the micro usb cable. 

- In the Arduino IDE, select the Teensy Board.

- File → Open → Navigate to the folder Start_Here → select Start_Here.ino

- Audio System Design Tool: Open browser, got to:  https://www.pjrc.com/teensy/gui/index.html


# SYNTH PINOUT


//  Pin G  --> ground bus

//  Pin 3v --> 3v bus

//  Pin 5v --> dac board Vcc

//  Pin 20 --> dac board LCK

//  Pin 21 --> dac board BCK

//  Pin 7  --> dac board DIN

//  dac board SCK --> Ground bus

//  Pin 14 --> Potentiometer OSC GAIN 

//  Pin 15 --> Potentiometer OSC FREQ

//  Pin 16 --> Potentiometer FILTER CUTOFF

//  Pin 17 --> Potentiometer LFO RATE

//  Pin 18 --> Potentiometer SEQUENCER SPEED

//  Pin 19 --> Potentiometer SEQUENCER OCTAVES RANGE

//   [all connections to pots central pin]

//  Pin 1 --> Button 1 Osc freq modulation on/off

//  Pin 2 --> Button 2 Cutoff Modulation on/off

//  [the other pin of each button --> Ground]

//  Pin 5 --> resistor --> LED+

//  Led- --> Ground









