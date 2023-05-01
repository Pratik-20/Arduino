/*
 * Basic code that will move robotic arm to preset location,
 * pick up an object, and drop it off behind the arm.
 * 
 * Uses my sweep function that will slow the rate at which 
 * the servo rotates.
 */


// include Servo Library
#include <Servo.h>

// create Servo objects to control servos
Servo shoulder;
Servo elbow;
Servo wrist1;
Servo wrist2;
Servo hand;
Servo base;

void setup() {
  // attach each servo object to a pin number
  shoulder.attach(11);
  elbow.attach(10);
  wrist1.attach(9);
  wrist2.attach(6);
  hand.attach(5);
  base.attach(3);

stable();
delay(5000);
pick();
nonMetal();
delay(2000);
stable();
delay(5000);
pick();
metal();
delay(2000);
stable();


  // set servos to pickup opbject
  /* sweep(hand, 90, 160, 30);  
   sweep(wrist2, 90, 160, 30);
   sweep(elbow, 90, 160, 30);
   sweep(shoulder, 90, 15, 30);
   sweep(hand, 160, 0, 30);

  // set servos to drop object
  sweep(shoulder, 15, 90, 30);
  sweep(elbow, 160, 0, 30);
  sweep(wrist2, 160, 90, 30);
  sweep(hand, 0, 160, 30);*/
}

void loop() {
  // nothing here!
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



void pick(){
  sweep(wrist2, 90, 160, 50);
  sweep(shoulder, 90, 15, 50);
  sweep(hand, 160, 0, 50);
}

void metal(){
  sweep(shoulder, 15, 90, 30);
  sweep(elbow, 160, 0, 30);
  sweep(wrist2, 160, 90, 30);
  sweep(base, 90, 120, 30);
  sweep(hand, 0, 160, 30);  
  delay(1000);
  sweep(base, 120, 90, 50);
}

void nonMetal(){
  sweep(shoulder, 15, 90, 30);
  sweep(elbow, 160, 0, 30);
  sweep(wrist2, 160, 90, 30);
  sweep(base, 90, 60, 30);
  sweep(hand, 0, 160, 30);
  delay(1000);
  sweep(base, 60, 90, 50);

   
}
void stable(){
  sweep(elbow, 90, 160, 90);
  sweep(hand, 90, 160, 30);
  delay(2000); 
}



