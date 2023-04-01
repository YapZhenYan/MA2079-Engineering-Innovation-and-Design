  #include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>  
#define liq_trigPin 3                  // ultrasonic sensor for liq
#define liq_echoPin 4                 // ultrasonic sensor for liq
#define trigPin 10                      // ultrasonic sensor for manual mode
#define echoPin 11                    // ultrasonic sensor for manual mode
#define System_pin 6                  // on and off
#define Mode_pin 5                    // manual & automatic
#define buzzer A2
#define BlueLED 12
#define GreenLED 13
#define RedLED 7
#define Blue 8 
int system_state;
int mode_state;
bool buzz = true;
int liq;

Servo myservo;

void setup() {

//Serial.begin(9600);
Wire.begin();
pinMode(System_pin, INPUT);
pinMode(Mode_pin, INPUT);
pinMode(BlueLED, OUTPUT);
pinMode(GreenLED, OUTPUT);
pinMode(RedLED, OUTPUT);
pinMode(Blue, OUTPUT);
pinMode(buzzer, OUTPUT);
pinMode(liq_trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
pinMode(liq_echoPin, INPUT); // Sets the echoPin as an INPUT
pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
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
    liq_detection();                                        //Red blink --> Low liq,  Red --> No liq,
    delay(1000);
    int outcome = mode + liq;
    Wire.beginTransmission(9);
    Wire.write(outcome);
    Wire.endTransmission();
    digitalWrite(BlueLED, LOW);
    digitalWrite(GreenLED,HIGH);
    spray();                           // spray mechanism
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
    manual_detection();                        // manual detection + spray
    return;
  }

  else                     // off the system
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
 //Serial.println(liq_distance);
  //delay(500);
  if (liq_distance >=0 && liq_distance <= 6)   // suff liq.
    {
      liq = 0;
      digitalWrite(Blue, LOW);
      digitalWrite(RedLED, LOW);           
    }
    else if (liq_distance >= 12)      // no liq
    {
      liq = 2;
      digitalWrite(Blue, LOW);
      digitalWrite(RedLED, HIGH);           // Red
      
    }
    else
    {
      liq = 1;                      // Purple
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
  int duration, distance;     // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);    // Measure the pulse input in echo pin
  distance = (duration/2) / 29.1;         // Distance is half the duration devided by 29.1 (from datasheet)
  delay(500);
  //Serial.println(distance);
  //delay(1000);
  if (distance>= 0 && distance <= 7)
    {
      tone(buzzer, 300, 300);  // buzzer will buzz to show successful detection
      delay(2000);
      for (int i =0; i<=2; i++)   // buzzer will buzz 3times before spraying
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
      for (int i =0; i<=2; i++)   // buzzer will buzz 3times before spraying
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
