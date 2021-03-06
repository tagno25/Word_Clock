/*
 * BlinkM_funcs.h -- Arduino 'library' to control BlinkM
 * --------------
 *
 *
 * Note: original version of this file lives with the BlinkMTester sketch
 *
 * Note: all the functions are declared 'static' because 
 *       it saves about 1.5 kbyte in code space in final compiled sketch.  
 *       A C++ library of this costs a 1kB more.
 *
 * 2007-11, Tod E. Kurt, ThingM, http://thingm.com/
 *
 * version: 20111201
 *
 * history:
 *  20080101 - initial release
 *  20080203 - added setStartupParam(), bugfix receiveBytes() from Dan Julio
 *  20081101 - fixed to work with Arduino-0012, added MaxM commands,
 *             added test script read/write functions, cleaned up some functions
 *  20090121 - added I2C bus scan functions, has dependencies on private 
 *             functions inside Wire library, so might break in the future
 *  20100420 - added BlinkM_startPower and _stopPower
 *  20111201 - updated to work with Arduino 1.0 (breaks compatibility with Arduino <= 0023)
 *
 */

#include <Arduino.h>


extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}


// format of light script lines: duration, command, arg1,arg2,arg3
typedef struct _blinkm_script_line {
  uint8_t dur;
  uint8_t cmd[4];    // cmd,arg1,arg2,arg3
} blinkm_script_line;


//
// each call to twi_writeTo() should return 0 if device is there
// or other value (usually 2) if nothing is at that address
//
static void BlinkM_scanI2CBus(byte from, byte to, 
                              void(*callback)(byte add, byte result) ) 
{
  byte rc;
  byte data = 0; // not used, just an address to feed to twi_writeTo()
  for( byte addr = from; addr <= to; addr++ ) {
    rc = twi_writeTo(addr, &data, 0, 1, 0 );
    callback( addr, rc );
  }
}

//
//
static int8_t BlinkM_findFirstI2CDevice() 
{
  byte rc;
  byte data = 0; // not used, just an address to feed to twi_writeTo()
  for( byte addr=1; addr < 120; addr++ ) {  // only scan addrs 1-120
    rc = twi_writeTo(addr, &data, 0, 1, 0);
    if( rc == 0 ) return addr; // found an address
  }
  return -1; // no device found in range given
}


// Gets the BlinkM firmware version
static int BlinkM_getVersion(byte addr)
{
  Wire.beginTransmission(addr);
  Wire.write('Z');
  Wire.endTransmission();
  Wire.requestFrom(addr, (byte)2);
  if( Wire.available() ) {
    byte major_ver = Wire.read();
    byte minor_ver = Wire.read();
    return (major_ver<<8) + minor_ver;
  }
  return -1;
}


// Sets the speed of fading between colors.  
// Higher numbers means faster fading, 255 == instantaneous fading
static void BlinkM_setFadeSpeed(byte addr, byte fadespeed)
{
  Wire.beginTransmission(addr);
  Wire.write('f');
  Wire.write(fadespeed);
  Wire.endTransmission();  
}

// Sets the light script playback time adjust
// The timeadj argument is signed, and is an additive value to all
// durations in a light script. Set to zero to turn off time adjust.
static void BlinkM_setTimeAdj(byte addr, byte timeadj)
{
  Wire.beginTransmission(addr);
  Wire.write('t');
  Wire.write(timeadj);
  Wire.endTransmission();  
}

// Fades to an RGB color
static void BlinkM_fadeToRGB(byte addr, byte red, byte grn, byte blu)
{
  Wire.beginTransmission(addr);
  Wire.write('c');
  Wire.write(red);
  Wire.write(blu);
  Wire.write(grn);
  Wire.endTransmission();
}


// Sets an RGB color immediately
static void BlinkM_setRGB(byte addr, byte red, byte grn, byte blu)
{
  Wire.beginTransmission(addr);
  Wire.write('n');
  Wire.write(red);
  Wire.write(blu);
  Wire.write(grn);
  Wire.endTransmission();
}

// Fades to a random RGB color
static void BlinkM_fadeToRandomRGB(byte addr, byte rrnd, byte grnd, byte brnd)
{
  Wire.beginTransmission(addr);
  Wire.write('C');
  Wire.write(rrnd);
  Wire.write(brnd);
  Wire.write(grnd);
  Wire.endTransmission();
}


//
static void BlinkM_playScript(byte addr, byte script_id, byte reps, byte pos)
{
  Wire.beginTransmission(addr);
  Wire.write('p');
  Wire.write(script_id);
  Wire.write(reps);
  Wire.write(pos);
  Wire.endTransmission();
}

//
static void BlinkM_stopScript(byte addr)
{
  Wire.beginTransmission(addr);
  Wire.write('o');
  Wire.endTransmission();
}

static void BlinkM_off(uint8_t addr)
{
  BlinkM_stopScript( addr );
  BlinkM_setFadeSpeed(addr,10);
  BlinkM_setRGB(addr, 0,0,0 );
}


//
static void BlinkM_setScriptLengthReps(byte addr, byte script_id, 
                                       byte len, byte reps)
{
  Wire.beginTransmission(addr);
  Wire.write('L');
  Wire.write(script_id);
  Wire.write(len);
  Wire.write(reps);
  Wire.endTransmission();
}

// Fill up script_line with data from a script line
// currently only script_id = 0 works (eeprom script)
static void BlinkM_readScriptLine(byte addr, byte script_id, 
                                  byte pos, blinkm_script_line* script_line)
{
  Wire.beginTransmission(addr);
  Wire.write('R');
  Wire.write(script_id);
  Wire.write(pos);
  Wire.endTransmission();
  Wire.requestFrom(addr, (byte)5);
  while( Wire.available() < 5 ) ; // FIXME: wait until we get 7 bytes
  script_line->dur    = Wire.read();
  script_line->cmd[0] = Wire.read();
  script_line->cmd[1] = Wire.read();
  script_line->cmd[2] = Wire.read();
  script_line->cmd[3] = Wire.read();
}

//
static void BlinkM_writeScriptLine(byte addr, byte script_id, 
                                   byte pos, byte dur,
                                   byte cmd, byte arg1, byte arg2, byte arg3)
{
#ifdef BLINKM_FUNCS_DEBUG
  Serial.print("writing line:");  Serial.print(pos,DEC);
  Serial.print(" with cmd:"); Serial.print(cmd); 
  Serial.print(" arg1:"); Serial.println(arg1,HEX);
#endif
  Wire.beginTransmission(addr);
  Wire.write('W');
  Wire.write(script_id);
  Wire.write(pos);
  Wire.write(dur);
  Wire.write(cmd);
  Wire.write(arg1);
  Wire.write(arg2);
  Wire.write(arg3);
  Wire.endTransmission();

}

//
static void BlinkM_writeScript(byte addr, byte script_id, 
                               byte len, byte reps,
                               blinkm_script_line* lines)
{
#ifdef BLINKM_FUNCS_DEBUG
  Serial.print("writing script to addr:"); Serial.print(addr,DEC);
  Serial.print(", script_id:"); Serial.println(script_id,DEC);
#endif
  for(byte i=0; i < len; i++) {
    blinkm_script_line l = lines[i];
    BlinkM_writeScriptLine( addr, script_id, i, l.dur,
                            l.cmd[0], l.cmd[1], l.cmd[2], l.cmd[3]);
    delay(20); // must wait for EEPROM to be programmed
  }
  BlinkM_setScriptLengthReps(addr, script_id, len, reps);
}

//
static void BlinkM_setStartupParams(byte addr, byte mode, byte script_id,
                                    byte reps, byte fadespeed, byte timeadj)
{
  Wire.beginTransmission(addr);
  Wire.write('B');
  Wire.write(mode);             // default 0x01 == Play script
  Wire.write(script_id);        // default 0x00 == script #0
  Wire.write(reps);             // default 0x00 == repeat infinitely
  Wire.write(fadespeed);        // default 0x08 == usually overridden by sketch 
  Wire.write(timeadj);          // default 0x00 == sometimes overridden by sketch
  Wire.endTransmission();
} 

//
static void BlinkM_setStartupParamsDefault( byte addr )
{
  BlinkM_setStartupParams( addr, 0x01, 0x00, 0x00, 0x08, 0x00 );
}


//
static int BlinkM_doFactoryReset() 
{

  delay(30);

  BlinkM_setStartupParamsDefault( 0x09 );

  delay(30);

  //  the example script we're going to write
  blinkm_script_line script1_lines[] = {
    {  1,  {'f',   10,  00,  00}},  // set fade speed to 10
    { 100, {'c', 0xff,0xff,0xff}},  // white
    {  50, {'c', 0xff,0x00,0x00}},  // red
    {  50, {'c', 0x00,0xff,0x00}},  // green
    {  50, {'c', 0x00,0x00,0xff}},  // blue 
    {  50, {'c', 0x00,0x00,0x00}},  // off
  };
  int script1_len = 6;  // number of script lines above
  
  BlinkM_writeScript( 0x09, 0, script1_len, 0, script1_lines);
  /*    
    BlinkMScript script = new BlinkMScript();
    script.add( new BlinkMScriptLine(  1, 'f',   10,   0,   0) );
    script.add( new BlinkMScriptLine(100, 'c', 0xff,0xff,0xff) );
    script.add( new BlinkMScriptLine( 50, 'c', 0xff,0x00,0x00) );
    script.add( new BlinkMScriptLine( 50, 'c', 0x00,0xff,0x00) );
    script.add( new BlinkMScriptLine( 50, 'c', 0x00,0x00,0xff) );
    script.add( new BlinkMScriptLine( 50, 'c', 0x00,0x00,0x00) );
    for( int i=0; i< 49-6; i++ ) {  // FIXME:  make this length correct
      script.add( new BlinkMScriptLine( 0, 'c', 0,0,0 ) );
    }

    writeScript( addr, script);
  */
  
}

