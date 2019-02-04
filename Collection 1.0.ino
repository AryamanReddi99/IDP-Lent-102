#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  AFMS.begin();
 
}

int movespeed = 250;
int turnspeed = 200;

void forward(int forward){
  Motor1->setSpeed(movespeed);
  Motor2->setSpeed(movespeed);
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  delay(forward);

}

void backward(int backward){
  Motor1->setSpeed(movespeed);
  Motor2->setSpeed(movespeed);
  Motor1->run(BACKWARD);
  Motor2->run(FORWARD);
  delay(backward);
}
void turnright(){
  Motor1->setSpeed(turnspeed);
  Motor2 ->setSpeed(turnspeed);
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  delay(1200);
}
void turnleft(){
  Motor1->setSpeed(turnspeed);
  Motor2 ->setSpeed(turnspeed);
  Motor1->run(BACKWARD);
  Motor2->run(BACKWARD);
  delay(1110);
  
}

void bump(){
  Motor1->run(RELEASE);
  Motor2->run(RELEASE);
  delay(400);
  Motor1->run(BACKWARD);
  Motor2->run(FORWARD);
  delay(100);
  Motor1->setSpeed(0);
  Motor2 ->setSpeed(0);
  Motor1->run(BACKWARD);
  Motor2->run(FORWARD);
  delay(200);
  Motor1->run(RELEASE);
  Motor2->run(RELEASE);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  forward(10000);
  bump();
  turnright();
  backward(2000);
  
  forward(10000);//start zigzag
  bump();
  turnright();
  forward(500);
  delay(200);
  turnright();
  backward(2000);//end zigzag
  
  forward(10000);
  bump();
  turnleft();
  forward(500);
  delay(200);
  turnleft();
  backward(2000);
  
  
}
