//I2C uses 2 pins
//LCD Shift uses 3 pins (2,3,4) share data/clock?
//LED Shift uses 4 pins (2,3,5,6)
//switches use 3 pins (7,8,9)

//Comment out to disable debug info (Should speed up execution and save space)
#define DEBUG

//Use enable to use LCD
//#define LCD

//Use I2C LCD instead of Shiftregister LCD
#define I2CLCD

//Define shift register pins
#define DATAPIN 2
#define CLOCKPIN 5
#define LCDLACHPIN 4 //broken in Rev1 board
#define LEDLACHPIN 3
// use output enable for dimming
#define LEDOUTPUTENABLEPIN 6

#define BUTTON1 10
#define BUTTON2 A0
#define BUTTON3 A3

#define BLINKLENGHT 500

#include <Wire.h> //required for DS1307RTC.h
#include <Time.h> //Required for timekeeping
#include <DS1307RTC.h> //required for RTC
#include <TimeAlarms.h> //Time Scheduling
#include <Timezone.h>    //Required to set the timzone
#include "I2C_LED.h"
#include <EEPROM.h> //Used to read and write the time to EEPROM

#ifdef LCD
#ifdef I2CLCD
#include "OLedI2C.h"             // I2C LCD
#else
#include <LiquidCrystal595.h>    // LCD on shift register
#endif
#endif

TimeChangeRule myDST = {"CDT", Second, Sun, Mar, 2, -300};    //Daylight time = UTC - 5 hours
TimeChangeRule mySTD = {"CST", First, Sun, Nov, 2, -360};     //Standard time = UTC - 6 hours
Timezone myTZ(myDST, mySTD);
TimeChangeRule *tcr;        //pointer to the time change rule, use to get TZ abbrev
time_t utc, local;
char Display[3]={0,0,0};
long previousMillis = 0;
unsigned long currentMillis = millis();
long menuMillis1 = currentMillis;

void setup()
{ 
  
  #ifdef DEBUG
  Serial.begin(9600);
  delay(5000);
  #endif
  
  pinMode(BUTTON1, INPUT_PULLUP);  
  pinMode(BUTTON2, INPUT_PULLUP);  
  pinMode(BUTTON3, INPUT_PULLUP);  

  randomSeed(analogRead(7));//random seed

  setupShiftRegister();
  analogWrite(LEDOUTPUTENABLEPIN, 0);
  wordsoff();
  updateShiftRegister();

  Wire.begin();
  
  BlinkM_stopScript(0x09);
  BlinkM_setFadeSpeed(0x09,255);
  
  #ifdef LCD
  setupDisplay();
  #endif
  
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  
  #ifdef DEBUG
  if(timeStatus()!= timeSet) {
    Serial.println(F("Unable to sync with the RTC"));
  } else {
    Serial.println(F("RTC has set the system time"));
  }
  #endif

  if(timeStatus()!= timeSet) {
    eepromDateTime();
    #ifdef LCD
    errorLCD("-----ERROR-----", " RTC not found ");
    #endif
    Alarm.timerOnce(3600, saveHour);
  } else {
    saveHour();
  }

  setSyncInterval(3600); //Resync clock with RTC daily

  setColor(); //Update the color
  
  Alarm.alarmRepeat(1, 0, 0, alarmHourly);//run alarmHourly() every hour
  Alarm.timerRepeat(30, alarm30sec); // run ledDisplayTime() every 30 seconds

  #ifdef DEBUG
  Alarm.timerRepeat(60, alarm60sec); // run switchLCD() every 60 seconds
  Alarm.timerRepeat(20, alarm20sec); // run digitalClockDisplay() every 20 seconds
  #endif
  
  ledDisplayTime();
  setBrightness();
}

int time[6];
int date[4];

void loop()
{
  #ifdef DEBUG
  #ifdef LCD
    updateLCDClock();
  #endif
  #endif
  
  Alarm.delay(100);// delay for 100ms and run alarms
  currentMillis = millis();
  if (digitalRead(BUTTON1)==LOW){
    if(currentMillis - menuMillis1 > 6000) {//reset menu timer ot current millis when more than 6000 different
      menuMillis1 = currentMillis;
    } else if(currentMillis - menuMillis1 > 4000) {//enter menu when timer is more than 4000 different from current
      menuMillis1 = currentMillis;
      while (digitalRead(BUTTON1)==LOW){
        currentMillis = millis();
        //don't change menus until button is released
        if(currentMillis - previousMillis > BLINKLENGHT) {
          previousMillis = currentMillis;
          Display[0] ^= (1<<0); //Menu LED toggle
        }
        updateShiftRegister();
      }
      configMenu();
    }
  }
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
//http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
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
