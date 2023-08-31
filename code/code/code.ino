
#include <SPI.h>
#include <ESP8266WiFi.h>                    // Needed for EPS8266


// MAX7219 items
#define Number_MAX7219 1        // 3 chips = 24 digits
#define MAX7219_CS  15          // pin the MAX7219's CS pin is connected to
#define bright 15    // brightness level 0-15

#include <MAX7219_8_Digit_Driver.h>

int magSens = 4;
bool clapActive = false;

// make an instance of MAX7219_Digit called My_Display and set CS pin
MAX7219_8_Digit_Driver My_Display(MAX7219_CS, Number_MAX7219);

int milli = 0; int sec = 0; int minu = 0; int hour = 0;
String formatMilli; String formatSec; String formatMinu; String formatHour;

void setup() {

  Serial.begin(115200); Serial.println(""); Serial.println("Up and Clackin");

  // write data to display plus the brightness level 0-15
  My_Display.String_To_Buffer("  CLAP  ", bright);
  pinMode(magSens, INPUT);
  delay(1000);


} // end of setup


void loop() {

  if (digitalRead(magSens)) {
    clapActive = false;
    for (int i = 0; i<100; i++) {
      if (digitalRead(magSens) == 0) {
        clapActive = true;
        break;
      }
    }
  }

  if (clapActive) {
    timerWrite();
  }

}

void timerWrite() {

  delay(10);
  milli += 10;
  sec = int(milli/1000);
  minu = int(sec/60);
  hour = int(minu/60);

  if(int((milli%1000)/10) < 10) {
    formatMilli = "0" + String(int((milli%1000)/10));
  } else {
    formatMilli = String(int((milli%1000)/10));
  }

  if(sec%60 < 10) {
    formatSec = "0" + String(sec%60);
  } else {
    formatSec = String(sec%60);
  }

  if(minu%60 < 10) {
    formatMinu = "0" + String(minu%60);
  } else {
    formatMinu = String(minu%60);
  }

  if(hour%60 < 10) {
    formatHour = "0" + String(hour%60);
  } else {
    formatHour = String(hour%60);
  }

  My_Display.String_To_Buffer(formatHour + "." + formatMinu + "." + formatSec + "." + formatMilli, bright);

}