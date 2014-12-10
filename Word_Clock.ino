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

#define BUTTON1 7
#define BUTTON2 8
#define BUTTON3 9

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
byte LEDbrightness = EEPROM.read(4);
char Display[3]={0,0,0};

void setup()
{ 
  
  #ifdef DEBUG
  Serial.begin(9600);
  //delay(5000);
  //while (!Serial) ; // wait until Arduino Serial Monitor opens
  #endif

  setupShiftRegister();
  setBrightness(LEDbrightness);
  wordsoff();
  updateShiftRegister();

  Wire.begin();
  
  Wire.beginTransmission(0x09);
  Wire.write('o');
  Wire.write('C');
  Wire.write(0xff);
  Wire.write(0xff);
  Wire.write(0xff);
  Wire.endTransmission();

  
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
  ledDisplayTime();

  Alarm.alarmRepeat(1, 0, 0, alarmHourly);//run alarmHourly() every hour
  Alarm.timerRepeat(30, alarm30sec); // run ledDisplayTime() every 30 seconds

  #ifdef DEBUG
  Alarm.timerRepeat(60, alarm60sec); // run switchLCD() every 60 seconds
  Alarm.timerRepeat(20, alarm20sec); // run digitalClockDisplay() every 20 seconds
  #endif
  
  wordsoff();
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
