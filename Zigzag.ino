#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);

void setup() {
  AFMS.begin();

}

int forwardspeed = 250;
int turnspeed = 200;
int backwardspeed = 250;

//operation code
void loop() {
  //first leg
  forward(12000);
  backward(400);
  turnright(1100);
  backward(2000);

  forward(12000);
  backward(400);
  turnright(1100);
  backward(2000);
  forward(1000);
  turnright(1100);
  backward(2000);
  
  for (int i=0; i<=6; i++){
    forward(12000);
    backward(400);
    turnleft(1100);
    forward(1000);
    turnleft(1100);
    backward(3000);
    
    
    forward(12000);
    backward(400);
    turnright(1100);
    forward(1000);
    turnright(1100);
    backward(2000);

    
    
  }
  
  
  
  
  
}
//braking subroutine
void brake(){
  Motor1->setSpeed(0);
  Motor2->setSpeed(0);
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  delay(50);
}

//forward
void forward(int forwardtime){
  Motor1->setSpeed(forwardspeed);
  Motor2->setSpeed(forwardspeed);
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  delay(forwardtime);
  brake();
}

//backward
void backward(int backwardtime){
  Motor1->setSpeed(backwardspeed);
  Motor2->setSpeed(backwardspeed);
  Motor1->run(BACKWARD);
  Motor2->run(BACKWARD);
  delay(backwardtime);
  brake();
}
//turn right
//using 1100 turns approx 90 degrees
void turnright(int turntime){
  Motor1->setSpeed(turnspeed);
  Motor2 ->setSpeed(turnspeed);
  Motor1->run(FORWARD);
  Motor2->run(BACKWARD);
  delay(turntime);
}

//turn left
//using 1100 turns approx 90 degrees
void turnleft(int turntime){
  Motor1->setSpeed(turnspeed);
  Motor2 ->setSpeed(turnspeed);
  Motor1->run(BACKWARD);
  Motor2->run(FORWARD);
  delay(turntime);
}
