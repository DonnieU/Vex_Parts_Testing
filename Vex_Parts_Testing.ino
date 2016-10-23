#include <Servo.h>

// pin (PWM) 13 used for motor
#define LINETRACKER1 A0      // A0 in analog mode
#define POT1 A1              // A1 in analog mode
#define TRIGGER_PIN A4       // A4 in digital mode; used to "start" Ultrasonic module
#define ECHO_PIN A3          // A3 in digital mode; used to determine time duration from Ultrasonic module
#define DELAY_1_SEC 1000     // time delay used for motor controller, in ms
#define DELAY_2_SEC 2000     // time delay used for motor controller, in ms

Servo motor1;
int val = 0;                          // temp variable used for sensors
long duration = 0;                    // duration found from Ultrasonic module
static unsigned long prevTime = 0;    // used in calculation of time lapse for motorTest
static unsigned int state = 0;

/*  
 *  void motorTest(void)
 *  VEX Motor Controller 29 with VEX 2-wire 393 Motor using Arduino Servo.h library:
 *  Full stop = 1500   
 *  Full speed forward = 2000
 *  Full speed reverse = 1000
 *  EX: motor1.write(2000) == motor turns full speed forward
 */
void motorTest(void) {
  unsigned long currTime = millis();

 // check time and decide when to increment 
  if ( (currTime - prevTime >= DELAY_1_SEC) && (!state || (state == 3)) ) { 
    prevTime = currTime;
    state++;
  } else if (currTime - prevTime >= DELAY_2_SEC) { 
    prevTime = currTime;
    state++; 
  }
  
  if (state > 5) { state = 0; } // start over
  
  // for testing just kept it simple by keeping track of current state and incrementing
  switch (state) {
    case 0: motor1.write(1500); break; // motor stop
    case 1: motor1.write(2000); break; // Full speed ahead!
    case 2: motor1.write(1750); break; // half speed forward
    case 3: motor1.write(1500); break; // motor stop
    case 4: motor1.write(1000); break; // full reverse speed
    case 5: motor1.write(1250); break; // half speed reverse
    default: motor1.write(1500); // motor stop
  }
 
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
  
  motor1.attach(13);   // PWM 13
  motor1.write(1500);  // stop motor by default

  pinMode(TRIGGER_PIN, OUTPUT); // with reference to the INPUT on the Ultrasonic Module
  pinMode(ECHO_PIN, INPUT);     // with reference to the OUTPUT on the Ultrasonic Module
  
  Serial.println("Beginning parts and sensors tests...");
 
} // end setup()

void loop() {
  motorTest();
  lineTrackerTest();
  potTest();
  ultrasonicTest();
} // end loop()
