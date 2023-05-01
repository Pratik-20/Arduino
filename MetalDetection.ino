/*
1)  Sensor Used - Robocraze LJ18A3-8-Z/BX 8mm Approach Sensor Inductive Proximity ( Inductive Proximity Sensor NPN )
2)  This sensor works on Analog Pins only (so it will not work on rest pins like Digital Pins - if used will always show Non-Metal object present)
3)  This sensor gives integer values only as- (0 = Metal), (127 = Non-Metal) 
4)  Make Sure that you are using Analog Pins only For Input 
*/

int MetalSensor = A0;                                                       // connect MetalSensor( Inductive Proximity Sensor NPN ) module to Arduino pin A0
int LED = 13;                                                               // connect LED to Arduino pin 13

void setup(){
  Serial.begin(9600);                                                       // Initialize Serial at 9600 Baud Rate.
  Serial.println("Serial Working");                                         // Test to check if serial is working or not
  pinMode(MetalSensor, INPUT);                                              // Set MetalSensor pin as INPUT
  pinMode(LED, OUTPUT);                                                     // LED Pin Output
}

void loop(){
  int sensorInputValue = analogRead(MetalSensor);                           //The Input value is integer (input from Analog Pin)
  //Serial.println(sensorInputValue);                                       // Uncomment this line to see input values on serial monitor window
  if (sensorInputValue == 0)                                                // Check if the pin high or not
  {
    // if the pin input is "0" then turn off the onboard Led
    digitalWrite(LED, HIGH);                                                // LED High
    Serial.println("Metal Object Present!");                                // print Metal Object Present! on the serial monitor window
  }
  else  {
    // ACtually for Non-Metal Object it generates "127" value but we are using else condition if Input is not equal to zero then there is no object or Non-Metal object is present 
    //else turn off the onboard LED
    digitalWrite(LED, LOW);                                                 // LED Low
    Serial.println("Non-metal Object Present or No Object!");               // print Non-metal Object Present or No Object! on the serial monitor window
  }
}