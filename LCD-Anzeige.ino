#include <LiquidCrystal.h>
#include <Wire.h>
#include "DS3231.h"
#include <EEPROM.h>
RTClib RTC;

const int RelayRead = 8;
const int LCDButton = A2 ;
const int LCD = A3;
const int CamPWRRead = 6;

unsigned  long lastMillis1;

int Frames;
int counter2 = 0;
int CamPWRHIGH;
int nowday;
int RelayReadHIGH = 0;
  
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup (){
  Wire.begin();
  lcd.begin(16, 2);
  DateTime now = RTC.now();
    
  pinMode(RelayRead, INPUT); //Messpin für Auslösereleis
  pinMode(LCDButton, INPUT); //Messpin für Display an
  pinMode(CamPWRRead, INPUT); //Messpin für Kamerastrom
  pinMode(LCD, OUTPUT); //Wenn HIGH,  LCD Hintergrundbeleuchtung an
  
  lastMillis1 = millis ();

  Frames = EEPROM.read(0);
  CamPWRHIGH = EEPROM.read(1);
  nowday = EEPROM.read(2);
  
}
 
void loop (){
DateTime now = RTC.now();

 //Zählt die Auslösungen
if(digitalRead(RelayRead)) 
 {     
   RelayReadHIGH = 1;
 } 
if(!digitalRead(RelayRead) && RelayReadHIGH == 1)
 {
   Frames++;
   counter2++;
   RelayReadHIGH = 0;
 }

 
  //Lässt das Display bei Knopfdruck 15 Sekunden aufleuchten
 {
if(digitalRead(LCDButton)) 
  {
    lastMillis1 = millis ();
  }
if(millis () - lastMillis1 <= 15000) 
  {
    digitalWrite(LCD, HIGH);
  }
else
  {
    digitalWrite(LCD, LOW);
  }

  
  //Wenn Auslösungen geschehen, leuchtet ein X auf
{
if(digitalRead(CamPWRRead) && !digitalRead(RelayRead) && counter2 >= 9)
  {
    CamPWRHIGH = 1;
    nowday = now.day();
  }

lcd.setCursor(15,1);
  if(CamPWRHIGH == 1 && nowday == now.day()) 
  {
    lcd.print("X");
  }

else
  {
    lcd.setCursor(15,1);
    lcd.print(" ");
  }
       
// Speichert alle relevanten Werte 3 Sekunden nach abschalten der Kamera im EEPROM.  
if(!digitalRead(CamPWRRead) && counter2 >= 8)
{ 
  delay(250);
  EEPROM.write(0, Frames); 
  EEPROM.write(1, CamPWRHIGH);
  EEPROM.write(2, nowday);
  delay(250);
  counter2 = 0;
}
  }
  
{  
// Logik des Ganzen (Zeigt aktulle Uhrzeit der RTC, belichtete Frame Anzahl und ob an dem Tag bereits ausgelöst wurde.)
  { 
  //Obere Zeile: Zeit      
lcd.setCursor(0,0);
lcd.print("Time:  ");
if(now.hour()<10) lcd.print("0");
lcd.print(now.hour()); 
lcd.print(":");
if(now.minute()<10) lcd.print("0");
lcd.print(now.minute());
lcd.print(":");
if(now.second()<10) lcd.print("0");
lcd.print(now.second());

//Untere Zeile: Frames und ob bereits ausgelöst wurde
lcd.setCursor(0,1); 
lcd.print("Frames:   ");
//lcd.print("Frames:  ");
//if(Frames <10) lcd.print("000");
//if(Frames <100) lcd.print("00");
//if(Frames <1000) lcd.print("0");   
lcd.print(Frames);

delay(210);
}
  }
    }
      }
