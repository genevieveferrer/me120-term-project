// ME120 Term Project
// this is for the servo motor part that rotates one laser
// May 20, 2022

// add library for servo
#include <Servo.h>

// names servo motor laserservo
Servo laserservo;

// set integer for potentiometer value; but this changes
int var;
int mapped_var;
// pin of the rotating laser
int rotating_laser = 3;
// pin of the stationary laser
// int stationary_laser = 5;

// set it up
void setup() {
  // connects actual servo from pin 9 to servo label on code
  laserservo.attach(9);
  // set the rate of the serial monitor
  Serial.begin(9600);
  // set the pin of the rotating laser to be an output
  pinMode(rotating_laser,OUTPUT);
}

void loop() {
  // turn the rotating laser on
  digitalWrite(rotating_laser, HIGH);
  // turn the stationary laser on
  // digitalWrite(stationary_laser, LOW);
  // assigns the potentiometer value to be read from analog pin 0 (potentiometer values go from 0 to 1023)
  var = analogRead(A0);
  // scale potentiometer values to servo values (0 degrees to 90 degrees)
  mapped_var = map(var, 10, 1023, 5, 95);
  // puts analog value of potentiometer to the servo so servo will rotate
  laserservo.write(mapped_var);
  // display the value on the serial monitor
  Serial.println(var);
  // delay between readings in ms to get servo to catch up
  delay(10);
}
