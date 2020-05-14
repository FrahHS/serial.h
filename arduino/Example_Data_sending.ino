void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Data from arduino");
  delay(300);
  Serial.print(".");
  delay(300);
  Serial.print(".");
  delay(300);
  Serial.println(".");
  delay(1000);
}
