// Includes the Servo library
#include <Servo.h>
//Include the LCD display library
#include <LiquidCrystal.h>

char line0[21]; // line 1 of the display 
char line1[21]; // line 2

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;

// Variables for the duration and the distance
long duration;
int distance;

// create object LCD for 4 bit mode
LiquidCrystal lcd(9, 8, 7, 6, 5, 4, 3);

Servo myServo; // Creates a servo object for controlling the servo motor

void setup() {
  pinMode(13, OUTPUT); // LED pin
  pinMode(12, OUTPUT); // SERVO PIN
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin is the servo motor attached
  /* Initialize 16x2 LCD */
  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for(int i = 15; i <= 165; i++){  
    myServo.write(i);
    delay(30);
    Serial.print(i); // Sends the current degree into the Serial Port
    Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
   distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
    Serial.print(distance); // Sends the distance value into the Serial Port
    Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    updateDisplay(i, distance);
  }
  
  // Repeats the previous lines from 165 to 15 degrees
  for(int i = 165; i >= 15; i--){
    myServo.write(i);
    delay(30);
   distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    updateDisplay(i, distance);
  }
}
// update LCD display infos
void updateDisplay(int deg, int dist){
  lcd.setCursor(0,0);
  lcd.print(line0);
  sprintf(line0, "POSITION: %d%c ", deg, (char)223);
  lcd.setCursor(0,1);
  lcd.print(line1);
  if(dist < 40){
    sprintf(line1, "DISTANCE: %d cm ", dist);  
  } else {
    sprintf(line1, "DISTANCE: none ", dist);  
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // set the trigPin HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = (duration * 0.034) / 2;
  // if distance < 40 turn on the LED
  if(distance < 40) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  return distance;
}
