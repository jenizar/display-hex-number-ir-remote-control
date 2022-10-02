#include <SPI.h>
#include <Wire.h> 
#include "DS3231.h"
#include <IRremote.h>
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27,20,4); // Initialize LCD Display at address 0x27 / 0X3F 

int RECV_PIN = 7;
const int buzer = 5;
char dateBuffer[12];
IRrecv irrecv(RECV_PIN);

decode_results results;

RTClib RTC;

void setup()
{
  Serial.begin(9600);
  pinMode(buzer,OUTPUT);
   Wire.begin();
    lcd.init();
    lcd.backlight();
  SPI.begin(); // Init SPI bus
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Welcome, prepare remote control");
    lcd.clear();
  lcd.setCursor(5, 0);
    lcd.print("IR Remote");
  lcd.setCursor(2, 1);
    lcd.print("Display Hex Data");
}

void loop() {
  if (irrecv.decode(&results)) {
    digitalWrite(buzer, HIGH);
    delay(300);
    digitalWrite(buzer, LOW);    
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Remote Control");
    lcd.setCursor(3,1);
    lcd.print("Hex Data :");   
    lcd.setCursor (6, 2);
    lcd.print(results.value, HEX); 
  }

    lcd.setCursor(0,3);

    DateTime now = RTC.now();
   sprintf(dateBuffer,"%02u/%02u/%04u ",now.day(),now.month(),now.year());
   lcd.print(dateBuffer);
   
  lcd.setCursor(15, 3);

  sprintf(dateBuffer,"%02u:%02u ",now.hour(),now.minute());
  lcd.print(dateBuffer);
  delay(100);
}
