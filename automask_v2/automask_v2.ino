#include <Servo.h>
#include <FastLED.h>

// Define connection pins:
//PIR Sensors
#define LEFT_PIR_PIN 2
#define RIGHT_PIR_PIN 5
#define BACK_PIR_PIN 8

//Servo
#define SERVO_PIN 7

//LEDS
#define LEFT_LED_PIN 3
#define RIGHT_LED_PIN 6
#define CENTER_LED_PIN 4

//Define LED colors here
#define SAFECOLOR CRGB( 50, 100, 150)
#define DANGERCOLOR CRGB( 255, 0, 0)
#define SENSORCOLOR CRGB( 0, 0, 100)

// FastLED CRGB object
CRGB leftLED[3];
CRGB rightLED[3];
CRGB centerLED[1];



Servo myservo;  // create servo object to control a servo
int pos = 100;    // variable to store the servo position

int timer = 0;
int timerLimit = 500;
// Create variables:
int val0 = 0;
int val1 = 0;
bool motionState = false; // We start with no motion detected.
bool isSafe = false;

void setup() {
  // Configure the pins as input or output:
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(LEFT_PIR_PIN, INPUT);
  pinMode(RIGHT_PIR_PIN, INPUT);
  myservo.attach(SERVO_PIN);
  FastLED.addLeds<NEOPIXEL, LEFT_LED_PIN>(leftLED, 3);
  FastLED.addLeds<NEOPIXEL, RIGHT_LED_PIN>(rightLED, 3);
  for (int i = 0; i <= 3; i++ ) {
    leftLED[i] = SAFECOLOR;
    rightLED[i] = SAFECOLOR;
    FastLED.show();
    delay(300);
  }




  // Begin serial communication at a baud rate of 9600:


  Serial.begin(9600);
  delay(1000);
}
void loop() {



  // Read out the pirPin and store as val:
  val0 = digitalRead(LEFT_PIR_PIN);
  val1 = digitalRead(RIGHT_PIR_PIN);
  // If motion is detected (pirPin = HIGH), do the following:
  if (val0 == HIGH || val1 == HIGH) {

    // Change the motion state to true (motion detected):
    if (motionState == false) {
     

//close the door, then it is safe
      pos = 80;
      myservo.write(pos);
      

       Serial.print("is it Safe? ");
      if (isSafe) {
        Serial.print(" SAFE");
      }
      else {
        Serial.print(" DANGER");
      }
      
      if (val0 == HIGH) {

        Serial.println("MotionA detected!");

        if (isSafe == false) {
          for (int i = 0; i < 3; i++ ) {
            leftLED[i] = DANGERCOLOR;
            FastLED.show();
            delay(70);
          }
        }
        else {
          for (int i = 0; i < 3; i++ ) {
            leftLED[i] = SENSORCOLOR;
            FastLED.show();
            delay(70);
          }
        }


      }

      else if (val1 == HIGH) {

        Serial.println("MotionB detected!");
        if (isSafe == false) {
          for (int i = 0; i < 3; i++ ) {
            rightLED[i] = DANGERCOLOR;
            FastLED.show();
            delay(70);
          }
        }
        else {
          for (int i = 0; i < 3; i++ ) {
            rightLED[i] = SENSORCOLOR;
            FastLED.show();
            delay(70);
          }
        }

      }
   

      timer = timerLimit;
      isSafe = true;
      Serial.print("Not Safe Anymore"); 
      if (isSafe) {
        Serial.println(" SAFE");
      }
      else {
        Serial.println(" DANGER");
      }
      
      motionState = true;

    }
  }

  // If no motion is detected (pirPin = LOW), do the following:
  else {

    // Change the motion state to false (no motion):
    if (motionState == true) {
      Serial.println("Motion ended!");

      for (int i = 0; i <= 3; i++ ) {
        leftLED[i] = SAFECOLOR;
        rightLED[i] = SAFECOLOR;
        FastLED.show();
        delay(300);
      }
      delay(500);
      motionState = false;

    }
    if (timer == 0) {
     
        isSafe = false;//door openning
        Serial.println("Door Open");

         if (isSafe) {
        Serial.println(" SAFE");
      }
      else {
        Serial.println(" DANGER");
      }
      

      if (pos >= 0) {
        pos = pos - 20;
        myservo.write(pos);
        delay(30);
      }
    }
    else {
      timer--;
      //Serial.println(timer);
      delay(10);
    }
  }
}
