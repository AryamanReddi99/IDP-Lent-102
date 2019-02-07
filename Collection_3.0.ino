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

//movement parameters
int forwardspeed = 250;
int backwardspeed = 250;
int turnspeed = 200;

//output 
const int MovementLED = 5;
const int CarryLED = 6;
const int ServoPort = 7;
int pos = 90;

int FLAG1 = 0;
int FLAG2 = 0;

//input
const int BumpRead1 = 1;
const int BumpRead2 = 2;
const int BumpRead3 = 3;
const int BumpRead4 = 4;
const int InfraredRead = 8;
const int HallRead = 9;

bool HallState;

void setup() {
  AFMS.begin();
  pinMode(MovementLED, OUTPUT);
  pinMode(HallRead, INPUT);
  rack.attach(ServoPort);
  
  pinMode(BumpRead1, INPUT_PULLUP);
  pinMode(BumpRead2, INPUT_PULLUP);
  pinMode(BumpRead3, INPUT_PULLUP);
  pinMode(BumpRead4, INPUT_PULLUP);
  pinMode(InfraredRead, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BumpRead1), bump1, HIGH);
  attachInterrupt(digitalPinToInterrupt(BumpRead2), bump2, HIGH);
  attachInterrupt(digitalPinToInterrupt(BumpRead3), bump3, HIGH);
  attachInterrupt(digitalPinToInterrupt(BumpRead4), bump4, HIGH);
  attachInterrupt(digitalPinToInterrupt(InfraredRead), InfraredDetection, HIGH);

  
}




//*************************************** OPERATION CODE **********************************************
void loop() {
  delay(2000);
  turnright(2000);


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
//*************Blind Movement***************
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
//**********Bump Movement***************
//moves forward until a wall is reached
void forwardbump(){
  FLAG1=1;
  FLAG2=1;
  Motor1->setSpeed(forwardspeed);
  Motor2->setSpeed(forwardspeed);
  while (FLAG1==1 || FLAG2==1){
    Motor1->run(FORWARD);
    Motor2->run(FORWARD);
  }
  brake();
}
void backwardbump(){
  FLAG1=1;
  FLAG2=1;
  Motor1->setSpeed(backwardspeed);
  Motor2->setSpeed(backwardspeed);
  while (FLAG1==1 || FLAG2==1){
    Motor1->run(BACKWARD);
    Motor2->run(BACKWARD);
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
void CarryingLight(bool state){
  if (state == true){
    digitalWrite(CarryLED,HIGH);
    
  }else{
    digitalWrite(CarryLED,LOW);
  }
}


//**************************************** DETECTION SUBROUTINES **************************************
//Bump voids
void bump1(){
  FLAG1 = 0;
}
void bump2(){
  FLAG2=0;
}
void bump3(){
  FLAG1 = 0;
}
void bump4(){
  FLAG2=0;
}
//INFRARED DETECTION
void InfraredDetection(){
  delay(1000);
  brake();
  if (HallDetection==true){
    Rack(120, false);
    delay(200);
    forward(2000);
    Rack(120, true);
  }else{
    Rack(60, false);
    delay(200);
    forward(2000);
    Rack(60, true);
  }
  
}
//HALL EFFECT SENSOR
bool HallDetection(){
  if (digitalRead(HallRead)==1){
    return(true);
  }else{
    return(false);
  }
}
//Rack and pinion movement
void Rack(int pos, bool state){
  if (pos>90 && state==false){
    for (int i=90;i<=pos;i++){
      rack.write(pos);
    }
  }
  if (pos<90 && state==false){
    for (int i=90;i>=pos;i--){
      rack.write(pos);
    }
  }
  if (pos>90 && state==true){
    for (int i=pos;i>90;i--){
      rack.write(pos);
    }
  }
  if (pos<90 && state==true){
    for (int i=pos;i<90;i++){
      rack.write(pos);
    }
  }
}
