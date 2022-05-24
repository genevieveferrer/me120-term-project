// 04/13/2022

// digital pins for CLK and DT
int pinA = 3; // Connected to CLK on KY-040
int pinB = 4; // Connected to DT on KY-040

// starting the encoder value at 0
int encoderPosCount = 0;

// declaring the variables to be integers
int pinALast;
int aVal;
int var;

// declaring bCW to be boolean --> only true/false values
boolean bCW;

// max and min aVals that were found when turning the rotary encoder 180 degrees and seeing what values it prints out
int aVal_max = 20;
int bVal_max = -20;

// include the library to use the servo
#include <Servo.h>

// name the servo
Servo laserservo;

// set up
void setup() {
  // for CLK pin to be input
  pinMode (pinA,INPUT);
  // for DT pin to be input
  pinMode (pinB,INPUT);
  // Whatever state it's in will reflect the last position; read the pinA value
  pinALast = digitalRead(pinA);
  // set the data rate (bits/second) for the serial monitor
  Serial.begin(9600);

  // connects actual servo from pin 9 to servo label on code
  laserservo.attach(9);
}

void loop() {
  // aVal will start off as the reading of pinA
  aVal = digitalRead(pinA);
  // 
  if (aVal != pinALast){ // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    if (digitalRead(pinB) != aVal) {
      // Means pin A Changed first - We're Rotating Clockwise
      // add onto the current encoder count because encoder is moving CW
      encoderPosCount ++;
      // sets the CW value as true
      bCW = true;
    }
    
    else {
      // Otherwise B changed first and we're moving CCW
      bCW = false;
      // subtract from the current encoder count because encoder is moving CCW
      encoderPosCount--;
    }

// taking this out at the moment...but do we really need it?? idk    
//    Serial.print ("Rotated: ");
//    if (bCW){
//      Serial.println ("clockwise");
//    }
//    
//    else{
//      Serial.println("counterclockwise");
//    }
//    
//    Serial.print("Encoder Position: ");
//    Serial.println(encoderPosCount);

    // if the encoder position is greater than the extreme/maximum values
    if (aVal > aVal_max || aVal < bVal_max ) {
      Serial.println("bruh motor can't go that far");
    }

    // if the encoder position is less than the extreme/maximum values
    else {
      // scale encoder position value to the servo motor
      var = map(encoderPosCount, bVal_max, aVal_max, 0, 180);
      // make the motor move to encoder position
      laserservo.write(var);
      // give the motor time i guess
      delay(500);
      }

    // let the previous value of pinA loop around
    pinALast = aVal; 
    
    }
    
  }
