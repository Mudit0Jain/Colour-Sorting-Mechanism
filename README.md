# Color Detection and Action with TCS3200 Color Sensor and Motors

## Description
This Arduino project uses a TCS3200 color sensor to detect different colors and perform specific actions based on the detected color. The detected colors control the rotation and movement of motors.

## Components
- Arduino Uno
- TCS3200 Color Sensor
- DC Motors (2)
- Motor Driver (L298N or equivalent)
- Jumper wires
- Breadboard

## Connections

### TCS3200 Color Sensor
- `S0`: Arduino pin 4
- `S1`: Arduino pin 5
- `S2`: Arduino pin 6
- `S3`: Arduino pin 7
- `OUT`: Arduino pin 8
- `VCC`: 5V
- `GND`: GND

### Motor Driver
- `enA`: Arduino pin 11
- `in1`: Arduino pin 10
- `in2`: Arduino pin 13
- `enB`: Arduino pin 2
- `in3`: Arduino pin 3
- `in4`: Arduino pin 12
- `VCC`: External power supply (typically 12V)
- `GND`: GND

## Arduino Code

```cpp
#include <tcs3200.h>

#define enA 11 // PWM
#define in1 10 // PWM
#define in2 13
#define in3 3  // PWM
#define in4 12
#define enB 2

int f = 500;
int quat = 1000; // 1200

#define num_of_colors 4
int distinctRGB[num_of_colors][3] = {{1,1,1}, {3,1,2}, {1,2,2}, {2,4,7}};
String distinctColors[num_of_colors] = {"white", "red", "green", "blue"};

int positionArray[4] = {0, 1, 2, 3};

const int S0 = 4;
const int S1 = 5; // PWM
const int S2 = 6; // PWM
const int S3 = 7;
const int outPin = 8;

int red, green, blue, black, white;

tcs3200 tcs(S0, S1, S2, S3, outPin);

void stop1() {
  digitalWrite(in1, LOW); // clockwise
  digitalWrite(in2, LOW);
}

void stop2() {
  digitalWrite(in3, LOW); // clockwise
  digitalWrite(in4, LOW);
}

void clockWise(int v) {
  int temp = positionArray[0];
  int temp2 = positionArray[1];
  int temp3 = positionArray[2];
  positionArray[0] = positionArray[3];
  positionArray[1] = temp;
  positionArray[2] = temp2;
  positionArray[3] = temp3;
  digitalWrite(in1, HIGH); // clockwise
  digitalWrite(in2, LOW);
  if (v == 180) {
    delay(1990);
  } else {
    delay(quat);
  }
}

void counterClockWise() {
  int temp = positionArray[2];
  int temp2 = positionArray[1];
  int temp3 = positionArray[3];
  positionArray[3] = positionArray[0];
  positionArray[0] = temp2;
  positionArray[1] = temp;
  positionArray[2] = temp3;
  digitalWrite(in1, LOW); // anticlockwise
  digitalWrite(in2, HIGH);
  delay(1300);
}

void push() {
  digitalWrite(in3, HIGH); // clockwise
  digitalWrite(in4, LOW);
  delay(1295);
  digitalWrite(in3, LOW); // anticlockwise
  digitalWrite(in4, HIGH);
  delay(1270);
}

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  Serial.begin(9600);
}

void loop() {
  red = tcs.colorRead('r');
  green = tcs.colorRead('g');
  blue = tcs.colorRead('b');

  if ((red > green) && (red > blue)) {
    if (positionArray[0] == 0) {
      delay(f);
      stop1();
      push();
      stop2();
      delay(f);
    } else if (positionArray[0] == 1) {
      delay(f);
      clockWise(90);
      stop1();
      push();
      stop2();
      delay(f);
    } else if (positionArray[0] == 2) {
      delay(f);
      clockWise(180);
      stop1();
      push();
      stop2();
      delay(f);
    } else if (positionArray[0] == 3) {
      delay(f);
      counterClockWise();
      stop1();
      push();
      stop2();
      delay(f);
    }
    Serial.println("was red");
    Serial.println(red);
    for (int i = 0; i < 5; i++) {
      Serial.print(positionArray[i] + ",");
    }
  }

  if ((red < green) && (green > blue)) {
    if (positionArray[0] == 1) {
      delay(f);
      stop1();
      push();
      stop2();
      delay(f);
    } else if (positionArray[0] == 2) {
      delay(f);
      clockWise(90);
      stop1();
      push();
      stop2();
      delay(f);
    } else if (positionArray[0] == 3) {
      delay(f);
      clockWise(180);
      stop1();
      push();
      stop2();
      delay(f);
    } else if (positionArray[0] == 0) {
      delay(f);
      counterClockWise();
      stop1();
      push();
      stop2();
      delay(f);
    }
    Serial.println("was g");
    Serial.println(green);
    for (int i = 0; i < 5; i++) {
      Serial.print(positionArray[i] + ",");
    }
  } else if ((blue > green) && (red < blue)) {
    if (positionArray[0] == 2) {
      delay(f);
      stop1();
      push();
      stop2();
      delay(f);
    } else if (positionArray[0] == 3) {
      delay(f);
      clockWise(90);
      stop1();
      push();
      stop2();
      delay(f);
    } else if (positionArray[0] == 0) {
      delay(f);
      clockWise(180);
      delay(quat);
      stop1();
      push();
      stop2();
      delay(f);
    } else if (positionArray[0] == 1) {
      delay(f);
      counterClockWise();
      stop1();
      push();
      stop2();
      delay(f);
    }
    Serial.println("was b");
    Serial.println(blue);
    for (int i = 0; i < 5; i++) {
      Serial.print(positionArray[i] + ",");
    }
  } else if ((red == green) && (green == blue)) {
    stop1();
    stop2();
    Serial.println("was w");
    Serial.println(white);
    for (int i = 0; i < 5; i++) {
      Serial.print(positionArray[i] + ",");
    }
  }
}
```

## How it works
* The TCS3200 color sensor reads the RGB values.
* The program compares the values to determine the detected color
* Based on the detected color, the program rotates the motor to a specific position and performs a push action

## Notes
* Adjust the delay values in the clockWise, counterClockWise, and push functions according to your specific motor and application requirements
* Ensure that the motor driver is capable of handling the current required by your motors
