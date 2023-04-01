#include <LiquidCrystal.h>
#include<Wire.h>
#define backlight 8
int outcome;

const int rs = 2 , en = 3 , d4 = 5, d5 = 4, d6 = 6, d7 = 7 ;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  lcd.begin(16, 2);                          // put your LCD parameters here
  pinMode(backlight, OUTPUT);
  digitalWrite(backlight, LOW);              // light up LCD
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  Serial.print("slave");
}

void receiveEvent()
{
  outcome = Wire.read();
  Serial.print("Hi");
  Serial.println(outcome);
  delay(1000);
}
  
void loop()
{
  if (outcome == 0)                // Manual Mode + Suff liq.
  {
  digitalWrite(backlight, HIGH);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Manual Mode");
  lcd.setCursor(0,1);
  lcd.print("Suff. Liquid");
  delay(1000);

  }
  if (outcome == 1)               // Manual Mode + Low Liq.
  {
  digitalWrite(backlight, HIGH);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Manual Mode");     
  lcd.setCursor(0,1);
  lcd.print("Low Liquid");
  delay(1000);
  }
    if (outcome == 2)            // Manual Mode + No Liq.
  {
  digitalWrite(backlight, HIGH);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Manual Mode");     
  lcd.setCursor(0,1);
  lcd.print("No Liquid");
  delay(1000);
  }  
  if (outcome == 3)              // Automatic Mode + Suff liq.
  {
  digitalWrite(backlight, HIGH);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Automatic Mode");  
  lcd.setCursor(0,1);
  lcd.print("Suff. Liquid");   
  delay(1000);
  } 
  if (outcome == 4)              // Automatic Mode + Low liq.
  {
  digitalWrite(backlight, HIGH);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Automatic Mode");     
  lcd.setCursor(0,1);
  lcd.print("Low Liquid");
  delay(2000);
  }  
  if (outcome == 5)              // Automatic Mode + No liq.
  {
  digitalWrite(backlight, HIGH);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Automatic Mode");    
  lcd.setCursor(0,1);
  lcd.print("No Liquid");
  delay(1000);
  }  
  if (outcome == 6)              // Off the system
  {
    lcd.setCursor(0,0);
    lcd.clear();
    digitalWrite(backlight, LOW);
    delay(500);
  }
}
 
