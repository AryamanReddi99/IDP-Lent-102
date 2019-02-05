#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);

int forwardspeed = 250;
int backwardspeed = 250;
int turnspeed = 200;

const int MovementLED = 3;
const int CarryLED = 5;

void setup() {
  AFMS.begin();
  pinMode(MovementLED, OUTPUT);
  
}




//*************************************** OPERATION CODE **********************************************
void loop() {
  BigZag();
  delay(100000000);
}

//************************************** PATHWAY SUBROUTINES *****************************************
//BigZag subroutine
void BigZag(){
  //first leg
  forward(10000);
  backward(400);
  turnright(1100);
  backward(2000);

  //second leg
  forward(12000);

  //positioning for zigzag
  backward(500);
  turnright(1100);
  backward(2000);
  forward(1000);
  turnright(1100);
  backward(2000);
  
  //begin zigzag
  for (int i=0; i<2; i++){
    forward(12000);
    backward(600);
    turnleft(1100);
    forward(1200);
    turnleft(1100);
    backward(3000);
    
    forward(12000);
    backward(600);
    turnright(1100);
    forward(1200);
    turnright(1100);
    backward(3000);   
  }

  forward(12000);
  backward(800);

  //exit danger zone
  turnleft(1100);
  forward(6000);
  backward(700);
  turnleft(1100);
  forward(6000);
  delay(4000);
  forward(6000);
}



//************************************** MOVEMENT SUBROUTINES *****************************************
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
//**************************************** INDICATION SUBROUTINES *************************************
//Indicate Movement
void MovementLight(bool state){
  if (state == true){
    digitalWrite(MovementLED,HIGH);
  }else{
    digitalWrite(MovementLED,LOW);
  }
}

//Indicate Carrying
void CarryingLight(bool state){
  if (state == true){
    digitalWrite(CarryLED,HIGH);
    
  }else{
    digitalWrite(CarryLED,LOW);
  }
}






//**************************************** DETECTION SUBROUTINES **************************************


/**
void CarryingLight(bool state){
  if (state == true){
    digitalWrite(CarryLED,HIGH);
    void MovementLight(bool state){
  if (state == true){
    digitalWrite(MovementLED,HIGH);
  }else{
    digitalWrite(MovementLED,LOW);
  }
}
  }else{
    digitalWrite(CarryLED,LOW);
  }



  **/
