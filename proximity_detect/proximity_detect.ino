/* 
  Demo sketch to validate that a microcontroller can detect 
  our IR proximity sensor.  We are using a resistor divider
  to drop 12V output to 3.3 for an Arduino Due.
*/

// constants
const int signal = 2;
const int led = 13;
int input = 0;
   
void setup() {
  pinMode(led, OUTPUT);
  pinMode(signal, INPUT);
}

void loop() {
  //Check for signal from input pin. 
  input = digitalRead(signal);
  
  //If HIGH, set led pin to HIGH, if false, set led pin to LOW
  if (input == HIGH){
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
