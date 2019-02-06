const int bump = 7;
int bumpvalue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(bump, INPUT);
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  bumpvalue = digitalRead(bump);
  Serial.println(bumpvalue);
  delay(10);
  

}
