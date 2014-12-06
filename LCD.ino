#ifdef I2CLCD
OLedI2C lcd;
//OLedI2C lcd(ADDRESS);
#else
LiquidCrystal595 lcd(DATAPIN,LCDLACHPIN,CLOCKPIN);     // datapin, latchpin, clockpin
#endif

boolean lcdOn = true;
String sSpace = " ";
String sColon = ":";
String sForwardSlash = "/";
String sTZ;
String sLine;

void setupDisplay()
{
  #ifdef DEBUG
    Serial.println(F("setupDisplay (setup LCD display)"));
  #endif

  lcd.begin(16, 2);
  lcd.noDisplay();
  lcd.clear();
  lcd.display();

}

void switchLCD(){
  if (lcdOn == true){
    lcd.noDisplay();
    #ifdef DEBUG
      Serial.println(F("switchLCD (LCD Off)"));
    #endif
    lcdOn = false;
  } else {
    lcd.clear();
    lcd.display();
    #ifdef DEBUG
      Serial.println(F("switchLCD (LCD On)"));
    #endif
    lcdOn = true;
  }
}

void errorLCD(String line1, String line2)
{
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(60000);
  lcd.setCursor(0, 0);
  lcd.print("               ");
  lcd.setCursor(0, 1);
  lcd.print("               ");
}

void updateLCDClock()
{
  utc = now();
  local = myTZ.toLocal(utc, &tcr);
  
  sTZ = tcr -> abbrev;

  time[0]=hour(local)/10;
  time[1]=hour(local)%10;
  time[2]=minute(local)/10;
  time[3]=minute(local)%10;
  time[4]=second(local)/10;
  time[5]=second(local)%10;
  date[0]=month()/10;
  date[1]=month()%10;
  date[2]=day()/10;
  date[3]=day()%10;
  
  lcd.setCursor(0, 0);
  sLine = utc + sSpace + sTZ;
  lcd.print(sLine);
  delay(1);
  lcd.setCursor(0, 1);
  sLine = time[0] + time[1] + sColon + time[2] + time[3];
  sLine += sSpace + year() + sForwardSlash + date[0];
  sLine += date[1] + sForwardSlash + date[2] + date[3];
  lcd.print(sLine);
}

