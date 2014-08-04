void setupChrono()
{
  Wire.begin();
  
  // clear /EOSC bit
  // Sometimes necessary to ensure that the clock
  // keeps running on just battery power. Once set,
  // it shouldn't need to be reset but it's a good
  // idea to make sure.
  Wire.beginTransmission(0x68); // address DS3231
  Wire.write(0x0E); // select register
  Wire.write(0b00011100); // write register bitmap, bit 7 is /EOSC
  Wire.endTransmission();
}

char fullDigits(int digits){
  if(digits < 10)
    return('0'+digits);
  return(digits);
}  

void saveDate(){
  #ifdef DEBUG
    Serial.println(F("saveDate (save date to EEPROM)"));
  #endif

  //save date to EEPROM
  int iYear=year();
  int iMonth=month();
  int iDay=day();
  
  EEPROM.write(0,iYear);
  EEPROM.write(1,iMonth);
  EEPROM.write(2,iDay);
}

void saveHour(){
  #ifdef DEBUG
    Serial.println(F("saveHour (save Hour to EEPROM)"));
  #endif
  
  //save Hour to EEPROM
  int iHour=hour();
  EEPROM.write(3,iHour);
  #ifdef DEBUG
    Serial.print(F("saveHour set to retriger in "));
    Serial.print(60-minute());
    Serial.println(F(" minutes"));
  #endif
  Alarm.timerOnce((60-minute())*60+1, saveHour);
}

void eepromDateTime(){
  #ifdef DEBUG
    Serial.println(F("eepromDateTime (retreive time from EEPROM)"));
  #endif
  
  //retreive time from EEPROM
  byte years = EEPROM.read(0);
  //set falback date
  //if (years>14) { years = 14; }
  byte months = EEPROM.read(1);
  byte days = EEPROM.read(2);
  byte hours = EEPROM.read(3);
  byte minutes = 0;
  byte seconds = 0;
  setTime(hours, minutes, seconds, days, months, years);
}
