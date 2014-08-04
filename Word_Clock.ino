//I2C uses 2 pins
//LCD Shift uses 3 pins (2,3,4) share data/clock?
//LED Shift uses 3 pins (2,3,5,6)
//switches use 3 pins (7,8,9)

//Comment out to disable debug info (Should speed up execution and save space)
#define DEBUG

//Use I2C LCD instead of Shiftregister LCD
#define I2CLCD

//Define shift register pins
#define DATAPIN 4
#define CLOCKPIN 5
#define LCDLACHPIN 6
#define LEDLACHPIN 7
// use output enable for dimming
#define LEDOUTPUTENABLEPIN 8

#define BUTTON1 9
#define BUTTON2 10
#define BUTTON3 11

#include <Wire.h> //required for DS1307RTC.h
#include <DS1307RTC.h> //required for RTC

#include <Time.h> //Required for timekeeping
#include <TimeAlarms.h> //Time Scheduling
#include <Timezone.h>    //Required to set the timzone

#ifdef I2CLCD
#include "OLedI2C.h"             // I2C LCD
#else
#include <LiquidCrystal595.h>    // LCD on shift register
#endif


#include <EEPROM.h> //Used to read and write the time to EEPROM

Timezone myTZ(124);
TimeChangeRule *tcr;        //pointer to the time change rule, use to get TZ abbrev
time_t utc, local;

void setup()
{ 
  Wire.begin();
  setupDisplay();
  setupShiftRegister();
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  
  #ifdef DEBUG
  Serial.begin(9600);
  //delay(5000);
  //while (!Serial) ; // wait until Arduino Serial Monitor opens
  if(timeStatus()!= timeSet) {
    Serial.println(F("Unable to sync with the RTC"));
  } else {
    Serial.println(F("RTC has set the system time"));
  }
  #endif

  if(timeStatus()!= timeSet) {
    eepromDateTime();
    errorLCD("-----ERROR-----", " RTC not found ");
    Alarm.timerOnce(3600, saveHour);
  } else {
    saveHour();
  }

  setSyncInterval(3600); //Resync clock with RTC daily
  ledDisplayTime();

  Alarm.alarmRepeat(1, 0, 0, saveDate);

  #ifdef DEBUG
  Alarm.timerRepeat(60, switchLCD);
  Alarm.timerRepeat(20, digitalClockDisplay);
  #endif
  
  Alarm.timerRepeat(30, ledDisplayTime);

  wordsoff();
  lcd.display();
}

int time[6];
int date[4];

void loop()
{
  #ifdef DEBUG
    updateLCDClock();
  #endif
  
  Alarm.delay(100);
}


//
//------------------------------------------
// Code Info
//------------------------------------------
//http://www.pjrc.com/teensy/td_libs_DS1307RTC.html
//http://www.pjrc.com/teensy/td_libs_Time.html
//http://www.pjrc.com/teensy/td_libs_TimeAlarms.html
//https://code.google.com/p/arduino-lcd-3pin/
//http://learn.adafruit.com/adafruit-arduino-lesson-4-eight-leds/overview
//http://arduino.cc/en/Tutorial/ShiftOut
//https://github.com/JChristensen/Timezone/
//
//------------------------------------------
// other info
//------------------------------------------
//http://learn.adafruit.com/memories-of-an-arduino
//http://www.instructables.com/id/My-Arduino-WordClock/?ALLSTEPS
//http://www.instructables.com/id/The-Word-Clock-Arduino-version/?ALLSTEPS
//http://docs.macetech.com/doku.php/chronodot_v2.0
//http://www.tek.com/blog/tutorial-digital-analog-conversion-%E2%80%93-r-2r-dac
//http://mbed.org/users/4180_1/notebook/powerssr-tail-and-zerocross-tail/
//
