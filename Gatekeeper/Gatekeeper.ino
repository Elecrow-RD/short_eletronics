#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(9);  
  pinMode(8, INPUT);  
  servo.write(0);
}

void loop() {
  int state = digitalRead(8);
  if(!state)
  {
    servo.write(120);
    delay(5000); 
    servo.write(0);
    //delay(1000); 
  }
}



  
