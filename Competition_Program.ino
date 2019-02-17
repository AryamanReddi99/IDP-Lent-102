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

//digital output 
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
const int infrared = 11;
const int HallRead = 8;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  pinMode(HallRead, INPUT);
  pinMode(infrared, INPUT);
  pinMode(BumpRead1, INPUT);
  pinMode(BumpRead2, INPUT);
  pinMode(BumpRead3, INPUT);
  pinMode(BumpRead4, INPUT);
  pinMode(MovementLED, OUTPUT);
  pinMode(CarryLED, OUTPUT);
  rack.attach(ServoRack);
  gate.attach(ServoBack);
}
//*************************************** OPERATION CODE **********************************************
void loop() {
  MovementLight(false);
  CarryLight(false);
  gate.write(160);
  rack.write(90);
  brake();
  //wait for 3 seconds after plugging in power so user can get out of the way
  delay(3000);
  
  //main code
  bigzag();
}
 
//************************************** PATHWAY SUBROUTINES *****************************************
//Bigzag2 **************************************Bigzag == Big Zigzag********************************
void bigzag(){
  //Wait until a bump sensor is touched - manual start for convenience
  while(true){
    if (analogRead(BumpRead1)>800 || analogRead(BumpRead2)>800){
      MovementLight(true);
      delay(1000);
      break;
    }
  }
  //move to back of field
  forwardbump();
  backward(400);
  turnright(1100);
  backwardbump();
  forwardbump(); 
  backward(400);
  turnright(1100);
  backwardbump();
  forward(1100);
  turnright(1100);
  backwardbump();
  //begin the zigzagging
  for (int i = 0;i<2;i++){
    //zig
    forwardbump();
    backward(600);
    turnleft(1100);
    forward(900);
    turnleft(1100);
    backwardbump();
    //zag
    forwardbump();
    backward(600);
    turnright(1100);
    forward(900);
    turnright(1100);
    backwardbump();
  }
  //exit danger zone
  forwardbump();
  backward(800);
  turnleft(1100);
  forwardbump();
  backward(500);
  turnleft(1100);
  backwardbump();
  //move to green zone and open storage gate
  forward(5000);
  brake();
  delay(500);
  gate.write(0);
  delay(500);
  CarryLight(false);
  //execute happy dance subroutine to dislodge blocks from storage area
  happy();
  //move to end zone and stop
  forwardbump();
  backward(700);
  turnleft(1100);
  backwardbump();
  forward(600);
  brake();
  MovementLight(false); 
  delay(1000000000);
}

//************************************** MOVEMENT SUBROUTINES *****************************************
//*************Blind Movement****************************
//braking subroutine - position control is more precise when brakes are applied 
void brake(){
  Motor1->setSpeed(0);
  Motor2->setSpeed(0);
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  delay(50);
}
//forward
void forward(int forwardtime){
  //move forward for certain time
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
//using turntime = 1100 turns approx 90 degrees
void turnright(int turntime){
  //turn both wheels at equal rate in opposite directions
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
    //check if the wall has been reached
    if (analogRead(BumpRead1)>800 && analogRead(BumpRead2)>800){
      delay(400);
      break;
    }
    //check  if the infrared beam has been broken (block present)
    if (digitalRead(infrared)==1){
      //goto sorting subroutine
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
    if (analogRead(BumpRead3)>800 && analogRead(BumpRead4)>800){
      delay(400);
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
  delay(100);
  brake();
  delay(500);
  //detect whether block is safe or unsafe and move rack and pinion mechanism accordingly
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
  turnright(15);
  forwardbump();
}
void happy(){
  //shakes the robot around in green zone as blocks were getting lodged in the storage area
  forward(300);
  turnleft(300);
  turnright(300);
  forward(300);
  turnleft(300);
  turnright(300);
  forward(300);
  turnleft(300);
  turnright(300);
}
