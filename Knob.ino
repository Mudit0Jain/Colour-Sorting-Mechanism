// Motor A
int enA = 2;
int in1 = 3;
int in2 = 12;
int f = 1390;
int b = 1290;

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Set motor A speed
  analogWrite(enA, 255);  // You can adjust the speed (0-255) here
}

void loop() {
  // Run the motor in one direction
  //digitalWrite(in1, HIGH);//clockwise
  //digitalWrite(in2, LOW);

  delay(f);  // Run for 2 seconds

  // Stop the motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  delay(200);  // Pause for 1 second

  // Run the motor in the other direction
  digitalWrite(in1, LOW); // anti
  digitalWrite(in2, HIGH);

  delay(200);  // Run for 2 seconds peechhe

  // Stop the motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  delay(2000);  // Pause for 1 second
}
