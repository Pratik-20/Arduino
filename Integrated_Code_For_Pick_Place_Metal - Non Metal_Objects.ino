// include Servo Library to run Servo Motors
#include <Servo.h>

// connect Sensors

int MetalSensor = A0;
int IRSensor = 8; 
int LED = 13; 
   

// create Servo objects to control servos

Servo shoulder;
Servo elbow;
Servo wrist1;
Servo wrist2;
Servo hand;
Servo base;

void setup() {

// Input from Sensors
Serial.begin(9600);                               // Init Serial at 9600 Baud Rate.
Serial.println("Serial Working");                 // Test to check if serial is working or not

pinMode(MetalSensor, INPUT);                      // Metal Sensor pin INPUT
pinMode(IRSensor, INPUT);                         // IR Sensor pin INPUT
pinMode(LED, OUTPUT);                             // LED Pin Output
                                     

// Attach each servo object to a pin number

shoulder.attach(11);
elbow.attach(10);
wrist1.attach(9);
wrist2.attach(6);
hand.attach(5);
base.attach(3);


}
void loop() {
  // nothing here!
  stable();
  delay(5000);
  pick_place();
  delay(2000);
  //stable();
}

/*
 * sweep function to make servos move slowly!
 * 
 * input the servo object, the current servo angle, the angle you 
 * want the servo to move to, and the speed at which you want to turn 
 * the servo. Bigger number ==> slower speed. Smaller number ==> faster speed.
 */
 
void sweep(Servo servo,int oldPos, int newPos, int servoSpeed){
  // if you want the servo to move clockwise
  if (oldPos <= newPos){
    // increase the servo angle by one every servoSpeed ms
    for (oldPos; oldPos <= newPos; oldPos += 1){
      servo.write(oldPos);
      delay(servoSpeed);
   }
  }

  // if you want the servo to move counter-clockwise
  else if (oldPos >= newPos){
    // decrease the servo angle by one every servoSpeed ms
    for (oldPos; oldPos >= newPos; oldPos -= 1){
      servo.write(oldPos);
      delay(servoSpeed);
    }
  }
}

// Function to stay arm stable after placing an Object

void stable(){
  Serial.println("In a Stable Position...!");
  sweep(elbow, 90, 160, 90);
  sweep(hand, 90, 160, 30);
  delay(2000); 
}

// Function To Pick Metal object, then Place It and return to Centre Position

void metal(){
  // Picking UP an Object..!
  Serial.println("Picking UP Metal Object..!");
  sweep(wrist2, 90, 160, 50);
  sweep(shoulder, 90, 30, 50);
  sweep(hand, 160, 0, 50);
  // Placing an  Object..!
  Serial.println("Placing an  Object in Metal's Bucket..!...!");
  sweep(shoulder, 30, 90, 30);
  sweep(elbow, 160, 0, 30);
  sweep(wrist2, 160, 90, 30);
  sweep(base, 90, 120, 30);
  sweep(hand, 0, 160, 30);  
  delay(1000);
  Serial.println("Returning to Stable Position...!");
  sweep(base, 120, 90, 50);
}


// Function To Pick Non Metal object, then Place It and return to Centre Position

void nonMetal(){                                                   

  // Picking UP an Object..!
  Serial.println("Picking UP Non-Metal Object..!");
  sweep(wrist2, 90, 160, 50);
  sweep(shoulder, 90, 30, 50);
  sweep(hand, 160, 0, 50);
  // Placing an  Object..!
  Serial.println("Placing an  Object in Non - Metal's Bucket..!...!");
  sweep(shoulder, 30, 90, 30);
  sweep(elbow, 160, 0, 30);
  sweep(wrist2, 160, 90, 30);
  sweep(base, 90, 60, 30);
  sweep(hand, 0, 160, 30);
  delay(1000);
  // Return to Centre Position
  Serial.println("Returning to Stable Position...!");
  sweep(base, 60, 90, 50);   
}


void pick_place(){

  int sensorInputValue = analogRead(MetalSensor);                         //The Input value is integer (input from Analog Pin)
  int sensorStatus = digitalRead(IRSensor);                              

  if ((sensorStatus == 0) && (sensorInputValue == 0))                     // IF IR Detects object and Metal Sensor metal then - there will be Metal Object 
  {
    digitalWrite(LED, HIGH);                                              // LED High
    Serial.println("Object Present!");                                    // print Motion Ended! on the serial monitor window
    Serial.println("Metal Object...!");                                   // print Metal Object Present! on the serial monitor window
    //Serial.println(sensorInputValue);                                   // Uncomment this line to see input values on serial monitor window
    //Serial.println(sensorStatus);                                       // Uncomment this line to see input values from IR sensor on serial monitor window   

    metal();                                                              // Calling Metal() Function To Pick & place Metal Object
  }

  else if ((sensorStatus == 0) && (sensorInputValue != 0)){               // IF IR Detects object and Metal Sensor detects non metal or no object then - there will be non Metal Object 

    Serial.println("Non-metal Object Present...!");                       // print Non-metal Object Present..! on the serial monitor window
    //Serial.println(sensorInputValue);                                      
    //Serial.println(sensorStatus);                                        

    nonMetal();                                                           // Calling nonMetal() Function To Pick & place Non Metal Object
  }

  else{                                                                   // If IR Didn't detected presence of any onject then this condition executes
    Serial.println("Object Not Present!");                                // Print Object Not Present! on the serial monitor window
    //Serial.println(sensorStatus);                                           
    pick_place();                                                         // Calling pick_place function Again & Again to stay in loop until IR detects Presence of any Object
  }
}