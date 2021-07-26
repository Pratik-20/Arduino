#include <AFMotor.h>

AF_DCMotor motor1(1);

void setup() {
  Serial.begin(9600); 
     
  pinMode(A2, INPUT_PULLUP);
  pinMode(13,OUTPUT);
 
}

void loop() {
    
   int ir = analogRead(2);
 
  if (ir>5) {
    digitalWrite(13,HIGH);
    delay(10);
 }
  else{
    digitalWrite(13,LOW);
    delay(15
        );
 }
    }
  
