/* Example code for HC-SR501 PIR motion sensor with Arduino. More info: www.makerguides.com */
// Define connection pins:
#define pirPin0 2
#define pirPin1 5
#define ledPin 13

#include <Servo.h>
#include <FastLED.h>
#define NUM_LEDS 3
#define DATA_PIN 3
#define DATA_PIN1 6
CRGB leds[NUM_LEDS];
CRGB leds1[NUM_LEDS];

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 100;    // variable to store the servo position

int timer = 0;
int timerLimit = 500;
// Create variables:
int val0 = 0;
int val1 = 0;
bool motionState = false; // We start with no motion detected.


void setup() {
  // Configure the pins as input or output:
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin0, INPUT);
  pinMode(pirPin1, INPUT);
  myservo.attach(7);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN1>(leds1, NUM_LEDS);
   leds[0] = CRGB::White;
       leds[1] = CRGB::White;
        leds[2] = CRGB::White;
         leds1[0] = CRGB::White;
       leds1[1] = CRGB::White;
        leds1[2] = CRGB::White;
      FastLED.show();
      
  
  // Begin serial communication at a baud rate of 9600:

  
  Serial.begin(9600);
  delay(1000);
}
void loop() {



  // Read out the pirPin and store as val:
  val0 = digitalRead(pirPin0);
  val1 = digitalRead(pirPin1);
  // If motion is detected (pirPin = HIGH), do the following:
  if (val0 == HIGH || val1 == HIGH) {
    digitalWrite(ledPin, HIGH); // Turn on the on-board LED.
    // Change the motion state to true (motion detected):
    if (motionState == false) {
      
      pos = 80;
      myservo.write(pos);

      if(val0 ==HIGH){
        motionState = true;
        Serial.println("MotionA detected!");
         leds[0] = CRGB::Red;
      leds[1] = CRGB::Red;
      leds[2] = CRGB::Red;
        }
     
      else if(val1 ==HIGH){
        motionState = true;
        Serial.println("MotionB detected!");
         leds1[0] = CRGB::Red;
      leds1[1] = CRGB::Red;
      leds1[2] = CRGB::Red;
        }
      
      FastLED.show();
      delay(500);
      
      timer = timerLimit;
    }
  }
  // If no motion is detected (pirPin = LOW), do the following:
  else {
    digitalWrite(ledPin, LOW); // Turn off the on-board LED.
    // Change the motion state to false (no motion):
    if (motionState == true) {
      Serial.println("Motion ended!" + timer);

      leds[0] = CRGB::White;
       leds[1] = CRGB::White;
        leds[2] = CRGB::White;
         leds1[0] = CRGB::White;
       leds1[1] = CRGB::White;
        leds1[2] = CRGB::White;
      FastLED.show();
      delay(500);
      motionState = false;

    }
    if (timer == 0) {
      if (pos >= 0) {
        pos = pos - 20;
        myservo.write(pos);
        delay(10);
      }
    }
    else {
      timer--;
      Serial.println(timer);
      delay(10);
    }
  }
}
