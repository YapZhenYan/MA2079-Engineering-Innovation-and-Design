// Created by @YapZhenYan on 17/05/2022
// Respective libaries
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>

// parameters
#define liq_trigPin 3                 // ultrasonic sensor for liq
#define liq_echoPin 4                 
#define Mode_pin 5                    // manual & automatic mode
#define System_pin 6                  // on and off button
#define RedLED 7
#define Blue 8 
#define trigPin 10                    // ultrasonic sensor for manual mode
#define echoPin 11                    
#define BlueLED 12
#define GreenLED 13
#define buzzer A2

int system_state;
int mode_state;
bool buzz = true;
int liq;
Servo myservo;

void setup() {
Wire.begin();
pinMode(System_pin, INPUT);
pinMode(Mode_pin, INPUT);
pinMode(BlueLED, OUTPUT);
pinMode(GreenLED, OUTPUT);
pinMode(RedLED, OUTPUT);
pinMode(Blue, OUTPUT);
pinMode(buzzer, OUTPUT);
pinMode(liq_trigPin, OUTPUT); 
pinMode(liq_echoPin, INPUT); 
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
myservo.attach(9);            
}

void loop() {
  system_state = digitalRead(System_pin);
  delay(200);
  mode_state = digitalRead(Mode_pin);
  delay(200);


  if (system_state == HIGH && buzz == true)      // system is on
  {
    buzz = false;
    tone(buzzer, 200, 200);
    return; 
  }

  else if (system_state == HIGH && buzz == false && mode_state == HIGH)      // automatic mode  --> Green LED
  { 
    int mode = 3;
    liq_detection();                  //Red blink --> Low liq,  Red --> No liq,
    delay(1000);
    int outcome = mode + liq;
    Wire.beginTransmission(9);
    Wire.write(outcome);
    Wire.endTransmission();
    digitalWrite(BlueLED, LOW);
    digitalWrite(GreenLED,HIGH);
    spray();
    delay(500);
    return;
  }
  
  else if (system_state == HIGH && buzz == false && mode_state == LOW)      // manual mode  --> Blue LED                                  
  {
    int mode = 0;
    liq_detection();                  //Red blink --> Low liq,  Red --> No liq,
    int outcome = mode + liq ;
    Wire.beginTransmission(9);
    Wire.write(outcome);
    Wire.endTransmission();
    digitalWrite(GreenLED, LOW);
    digitalWrite(BlueLED, HIGH);
    manual_detection();
    return;
  }

  else                      // off the system
  {
    buzz = true;
    int outcome = 6;
    Wire.beginTransmission(9);
    Wire.write(outcome);
    Wire.endTransmission();
    digitalWrite(GreenLED, LOW);
    digitalWrite(BlueLED, LOW);   
    digitalWrite(RedLED, LOW);
    digitalWrite(Blue, LOW); 
    return;
  }
}

void liq_detection()
{
  // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
  int liq_duration, liq_distance;
  digitalWrite(liq_trigPin, HIGH); 
  delayMicroseconds(2);
  digitalWrite(liq_trigPin, LOW);
  delayMicroseconds(10);

  // Measure the pulse input in echo pin
  liq_duration = pulseIn(liq_echoPin, HIGH);
  // Distance is half the duration devided by 29.1 (from datasheet)
  liq_distance = (liq_duration/2) / 29.1;
  delay(500);

  if (liq_distance >=0 && liq_distance <= 6)    // suff liq. -> No Light
    {
      liq = 0;
      digitalWrite(Blue, LOW);
      digitalWrite(RedLED, LOW);           
    }
    else if (liq_distance >= 12)               // no liq -> Red Light
    {
      liq = 2;
      digitalWrite(Blue, LOW);
      digitalWrite(RedLED, HIGH);           
      
    }
    else
    {
      liq = 1;                                   // low liq -> Purple
      digitalWrite(RedLED, HIGH);
      digitalWrite(Blue, HIGH);
      }
    }
      
void manual_spray()
{
  myservo.attach(9);
  myservo.write(0);    // turns
  delay(800);                
  myservo.detach();    // stops 
  delay(2000);         
  myservo.attach(9);
  myservo.write(170);  // turns
  delay(250);         
  myservo.detach();    // stops
  delay(2000);         
  return;
}

void manual_detection()
{
  int duration, distance;     
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);   
  distance = (duration/2) / 29.1;         
  delay(500);

  if (distance>= 0 && distance <= 7)
    {
      tone(buzzer, 300, 300);          // buzzer will buzz to show successful detection
      delay(2000);
      for (int i =0; i<=2; i++)        // buzzer will buzz 3 times before spraying
      {
      tone(buzzer, 200, 1000);
      delay(500);
      noTone(buzzer);
      delay(500);
      }
      manual_spray();
      return;
    }
  else
  {
      noTone(buzzer);
      return;
  }
}

void spray()
{ 
  for (int j = 0 ; j <= 12; j++)
  {
    mode_state = digitalRead(Mode_pin);
    system_state = digitalRead(System_pin);
    delay(500);
    if (j == 12)
    {
      for (int i =0; i<=2; i++)         // buzzer will buzz 3times before spraying
      {
      tone(buzzer, 200, 1000);
      delay(500);
      noTone(buzzer);
      delay(500);
      }
      manual_spray();
      return;
    }
    if (mode_state == LOW || system_state == LOW)
    {
     return;
    }
  }
}
