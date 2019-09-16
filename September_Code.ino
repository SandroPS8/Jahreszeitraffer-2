                      // Theseus Version [Erweiterte Version mit automatischer Kamereinschatung via Pin 2 und RTC
                      //  CODE AB 1. SEPTEMBER 2019. HOCHLADEN AM 1.9. AB 0.00 UHR
                    
#include <Wire.h>
#include "DS3231.h"
RTClib RTC;

// Startzeit Auslösungen
int shutterstd1[30] = {14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};   // Stunde
int shutterminu1[30] = {42, 43, 45, 46, 47, 49, 50, 51, 53, 54, 55, 57, 58, 59, 1, 2, 3, 5, 6, 7, 9, 10, 11, 13, 14, 15, 17, 18};                // Minute
int shuttersecs1[30] = {20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0};          //Sekunde
//Einschaltzeit Kamera
int caminstd1[30] = {14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};     // Stunde
int caminminu1[30] = {41, 43, 44, 45, 47, 48, 49, 51, 52, 53, 55, 56, 57, 59, 0, 1, 3, 4, 5, 7, 8, 9, 11, 12, 13, 15, 16, 17, 19, 20};           // Minute
int caminsecs1[30] = {50, 10, 30, 50, 10, 30, 50, 10, 30, 50, 10, 30, 50, 10, 30, 50, 10, 30, 50, 10, 30, 50, 10, 30, 50, 10, 30, 50, 10, 30};  // Sekunde
// Ausschaltzeit Kamera
int camoutstd1[30] = {14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};  // Stunde
int camoutminu1[30] = {44, 45, 47, 48, 49, 51, 52, 53, 55, 56, 57, 59, 0, 1, 3, 4, 5, 7, 8, 9, 11, 12, 13, 15, 16, 17, 19, 20, 21, 23};        // Minute
int camoutsecs1[30] = {20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0, 20, 40, 0};         // Sekunde



const int Shutter = 3;
const int PWRCam = A1;
const int LED = 9;


void setup() {

    pinMode(Shutter, OUTPUT);
    pinMode(PWRCam, OUTPUT);
    pinMode(LED, OUTPUT);
    Wire.begin();
}

void loop() {
  DateTime now = RTC.now();
if (caminstd1[now.day()-1] == now.hour() && caminminu1[now.day()-1] == now.minute() && caminsecs1[now.day()-1] == now.second()){
    digitalWrite(PWRCam, HIGH);
    digitalWrite(LED, HIGH);
      }
if(camoutstd1[now.day()-1] == now.hour() && camoutminu1[now.day()-1] == now.minute() && camoutsecs1[now.day()-1] == now.second()){
   digitalWrite(PWRCam, LOW);
   digitalWrite(LED, LOW);
        }
if(shutterstd1[now.day()-1] == now.hour() && shutterminu1[now.day()-1] == now.minute() && shuttersecs1[now.day()-1] == now.second()){
    for(int i = 0; i<9; i++){
              
        digitalWrite(Shutter, HIGH);
        delay(1000);
        digitalWrite(Shutter, LOW),
        delay(9000);
      }
        }
          }
            
            
