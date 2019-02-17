//***********Included 
//Libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

//Create objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);
Servo rack;
Servo gate;

//movement parameters
int forwardspeed = 250;
int backwardspeed = 250;
int turnspeed = 200;
int rackdelay(20);

//output 
const int MovementLED = 2;
const int CarryLED = 3;
const int ServoRack = 9;
const int ServoBack = 10;
int pos = 90;

//analog input
const int BumpRead1 = 0;
const int BumpRead2 = 1;
const int BumpRead3 = 2;
const int BumpRead4 = 3;

//digital input
const int infrared = 18;

const int HallRead = 10;

void setup() {
  Serial.begin(9600);
  
  AFMS.begin();
  pinMode(MovementLED, OUTPUT);
  pinMode(CarryLED, OUTPUT);
  pinMode(HallRead, INPUT);
  rack.attach(ServoRack);
  gate.attach(ServoBack);
  
  pinMode(BumpRead1, INPUT);
  pinMode(BumpRead2, INPUT);
  pinMode(BumpRead3, INPUT);
  pinMode(BumpRead4, INPUT);

  pinMode(infrared, INPUT);
  
}
//*************************************** OPERATION CODE **********************************************
void loop() {
  MovementLight(true);
  CarryLight(false);
  gate.write(170);
  rack.write(90);
  while (true){
  
  delay(1000);
  forwardbump();
  delay(1000);
  backwardbump();
  }
  
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
    if (i==0){
      CarryLight(true);
    }
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
  backward(700);
  forward(4000);
  gate.write(20);
  delay(4000);
  
  
  forward(6000);
}



//************************************** MOVEMENT SUBROUTINES *****************************************
//*************Blind Movement****************************
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
  brake();
}

//turn left
//using 1100 turns approx 90 degrees
void turnleft(int turntime){
  Motor1->setSpeed(turnspeed);
  Motor2 ->setSpeed(turnspeed);
  Motor1->run(BACKWARD);
  Motor2->run(FORWARD);
  delay(turntime);
  brake();
}
//**********Bump Movement**************************************
//moves forward until a wall is reached
void forwardbump(){
  Motor1->setSpeed(forwardspeed);
  Motor2->setSpeed(forwardspeed);
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  while (true){
    delay(50);
    if (analogRead(BumpRead1)>200 && analogRead(BumpRead2)>200){
      break;
    }
    if (digitalRead(infrared)==1){
      infra();
    }
  }
  brake();
}
void backwardbump(){
  Motor1->setSpeed(backwardspeed);
  Motor2->setSpeed(backwardspeed);
  Motor1->run(BACKWARD);
  Motor2->run(BACKWARD);
  while (true){
    delay(100);
    if (analogRead(BumpRead3)>200 && analogRead(BumpRead4)>200){
      break;
    }
  }
  brake();
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
void CarryLight(bool state){
  if (state == true){
    digitalWrite(CarryLED,HIGH);
    
  }else{
    digitalWrite(CarryLED,LOW);
  }
}
  

//**************************************** DETECTION SUBROUTINES **************************************
//INFRARED DETECTION
void infra(){
  delay(50);
  brake();
  delay(500);
  if (analogRead(HallRead)<900){ // unsafe blocks
    rack.write(120);
    delay(500);
    forward(250);
    delay(500);
    rack.write(90);
    delay(500);
  }else{ // safe blocks
    rack.write(60);
    delay(500);
    forward(250);
    delay(500);
    rack.write(90);
    delay(500);
    CarryLight(true);
  } 
  
  forwardbump();
}
