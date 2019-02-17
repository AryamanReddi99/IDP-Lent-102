const int infrared = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(infrared, INPUT);
  Serial.begin(9600);

}

void loop() {
  Serial.println(analogRead(infrared));
  delay(100);

}
