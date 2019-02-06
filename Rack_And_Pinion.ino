#include <Servo.h>
Servo rack;

int pos = 90;
const int ServoPort = 1;

void setup() {
  // put your setup code here, to run once:
  rack.attach(ServoPort);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  for (pos = 90; pos<=180;pos +=1){
    rack.write(pos);
    delay(10);
  }
  for (pos=180;pos>=90;pos-=1){
    rack.write(pos);
    delay(10);
  }
  delay(1000);
  for (pos = 90; pos>=0;pos -=1){
    rack.write(pos);
    delay(10);
  }
  for (pos=0;pos<=90;pos+=1){
    rack.write(pos);
    delay(10);
  }
  delay(1000);

}
