#include <Arduino.h>
#include <Servo.h>

const int analogInPin1 = 20;	// Analog input pin that the joystick X potentiometer is attached to
const int analogInPin2 = 18;	// Analog input pin that the joystick Y potentiometer is attached to

int Servo1Pin = 4;				// variable to read the value from the analog pin
int Servo2Pin = 5;				// variable to read the value from the analog pin

int sensorValue1 = 0;  			// value read from the pot
int sensorValue2 = 0;  			// value read from the pot

int angle = 0;					// variable to hold the angle for the servo motor
int angleDiff;
int oldAngle;
int newAngle;

int angle2 = 0;					// variable to hold the angle for the servo motor
int angleDiff2;
int oldAngle2;
int newAngle2;

Servo Servo1;					// create a servo object
Servo Servo2;					// create a servo object

void setup() {
  Servo1.attach(Servo1Pin);		// attaches the servo on pin 4 to the servo object
  Servo2.attach(Servo2Pin);		// attaches the servo on pin 5 to the servo object

  Serial.begin(115200);			// debugging

  pinMode(LED_BUILTIN, OUTPUT); // power on indicator.
  digitalWrite(LED_BUILTIN, HIGH); 

}

void loop() {
  sensorValue1 = int(analogRead(analogInPin)/5);	// dividing ranges makes for less "jittery" motion
  sensorValue2 = int(analogRead(analogInPin2)/5);

// scale the numbers from the pot into usable microsecond pulse range
  angle = map(sensorValue, 0, 205, 50, 250);
  angle2 = map(sensorValue2, 205, 0, 50, 250);
  
// "Ease" halfway toward the target on each loop. This smooths out the servo motion.  
  angleDiff = angle - oldAngle;
  newAngle = int(oldAngle + (angleDiff / 2));
  
  angleDiff2 = angle2 - oldAngle2;
  newAngle2 = int(oldAngle2 + (angleDiff2 / 2));

  Servo2.writeMicroseconds(newAngle2 * 10);		// multiply, again to reduce "jitter"
  Servo1.writeMicroseconds(newAngle * 10);

  oldAngle = newAngle;
  oldAngle2 = newAngle2;

// debugging
  Serial.println(sensorValue);
  Serial.println(sensorValue2);

  Serial.println("-");

  delay(10);
 
}
