//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Light sensor using a Photoresistor
// (see circuit schematic ) 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int light = 0; 

void setup() {
    Serial.begin(9600); 
}

void loop() {
    
    // read and save value from Photoresistor
    int light = analogRead(15);   
    
    // print current light value
    Serial.println(light); 
 
    delay(20); 
}