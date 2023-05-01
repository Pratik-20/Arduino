int IRSensor = 8; // connect IR sensor module to Arduino pin D8
int LED = 13; // connect LED to Arduino pin 13

void setup(){
  Serial.begin(9600);                               // Init Serial at 9600 Baud Rate.
  Serial.println("Serial Working");                 // Test to check if serial is working or not
  pinMode(IRSensor, INPUT);                         // IR Sensor pin INPUT
  pinMode(LED, OUTPUT);                             // LED Pin Output
}

void loop(){
  int sensorStatus = digitalRead(IRSensor);          // Set the GPIO as Input
  if (sensorStatus == 1)                             // Check if the pin high or not
  {
    // if the pin is high turn off the onboard Led
    digitalWrite(LED, LOW);                          // LED LOW
    Serial.println("Object Not Present!");           // print Motion Detected! on the serial monitor window
  }
  else  {
    //else turn on the onboard LED
    digitalWrite(LED, HIGH); // LED High
    Serial.println("Object Present!");               // print Motion Ended! on the serial monitor window
  }
}