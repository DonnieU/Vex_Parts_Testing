#include <Servo.h>

#define LINETRACKER1 0  // A0
#define POT1 1          // A1
#define TRIGGER_PIN 11   // Digital pin 50
#define ECHO_PIN 12   // Digital pin 52

Servo servo1;
int val = 0;
long duration = 0;

/*  void motorTest(void)
 *  VEX Motor Controller 29 with VEX 2-wire 393 Motor using Arduino Servo library:
 *  Full stop = 1500   
 *  Full speed forward = 2000
 *  Full speed reverse = 1000
 *  EX: servo1.write(2000) == motor turns full speed forward
 */
void motorTest(void) {
  servo1.write(1500);   // Stop motor
  delay(1000);
  servo1.write(2000);   // Full speed ahead!
  delay(2000);
  servo1.write(1750);   // Half speed forward!
  delay(2000);
  servo1.write(1500);   // Stop
  delay(1000);
  servo1.write(1000);   // Full speed reverse
  delay(2000);
  servo1.write(1250);   // Half speed reverse
  delay(2000);
} // end motorTest()

/*
 * lineTrackerTest(void)
 * VEX Line Tracker acquired ranges on MEGA 2650 analog pin with
 * Dr. Mitchell designed Arduino proto-shield:
 * -- varying distance using hand:
 * Observed Min: 44
 * Observed Max: 1021
 */
void lineTrackerTest(void) {
  val = analogRead(LINETRACKER1); // read input pin of LINETRACKER1
  Serial.print("Line tracker value: ");
  Serial.print(val);
} // end lineTrackerTest

/*
 * potTest(void)
 * VEX potentiometer acquired ranges on MEGA 2650 analog pin with
 * Dr. Mitchell designed Arduino proto-shield:
 * Observed Min: 0
 * Observed Max: 1023 
 */
void potTest(void) {
  val = analogRead(POT1); // read input pin of POT1
  Serial.print("    Potentiometer value: ");
  Serial.print(val);
} // end potTest

/*
 * ultrasonicTest()
 * VEX Ultrasonic Range Module acquired ranges on MEGA 2650 analog pin with
 * Dr. Mitchell designed Arduino proto-shield:
 * Observed Min: 214
 * Observed Max: 10534
 */
void ultrasonicTest(void) {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  
  Serial.print("    Ultrasonic ECHO duration: ");
  Serial.println(duration, DEC);
} // end ultrasonicTest

void setup() {
  Serial.begin(9600);
  Serial.println("");
  
  servo1.attach(13);   // PWM 13
  servo1.write(1500);  // stop motor by default

  pinMode(TRIGGER_PIN, OUTPUT); // with reference to the INPUT on the Ultrasonic Module
  pinMode(ECHO_PIN, INPUT); // with reference to the OUTPUT on the Ultrasonic Module
  
  Serial.println("Beginning parts and sensors tests...");
 
} // end setup()

void loop() {
  //motorTest();
  lineTrackerTest();
  potTest();
  ultrasonicTest();
} // end loop()
