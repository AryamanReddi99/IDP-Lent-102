const int MovementLED = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(MovementLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  MovementLight(true);
  delay(10000);
  MovementLight(false);
  delay(20000000);
  

}

void MovementLight(bool state){
  if (state == true){
    digitalWrite(MovementLED, HIGH);
    
  }else{
    digitalWrite(MovementLED, LOW);
  }
}
