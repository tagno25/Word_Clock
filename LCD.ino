#ifdef I2CLCD
OLedI2C lcd;
//OLedI2C lcd(ADDRESS);
#else
LiquidCrystal595 lcd(DATAPIN,LCDLACHPIN,CLOCKPIN);     // datapin, latchpin, clockpin
#endif

boolean lcdOn = true;

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
  
  time[0]=hour(local)/10;
  time[1]=hour(local)%10;
  time[2]=minute(local)/10;
  time[3]=minute(local)%10;
  time[4]=second(local)/10;
  time[5]=second(local)%10;
  date[0]=month(local)/10;
  date[1]=month(local)%10;
  date[2]=day(local)/10;
  date[3]=day(local)%10;
  
  lcd.setCursor(0, 0);
  lcd.print(now());
  lcd.print(" ");
  lcd.print(tcr -> abbrev);
  lcd.setCursor(0, 1);
  lcd.print(time[0]);
  lcd.print(time[1]);
  lcd.print(":");
  lcd.print(time[2]);
  lcd.print(time[3]);
  lcd.print(" ");
  lcd.print(year());
  lcd.print("/");
  lcd.print(date[0]);
  lcd.print(date[1]);
  lcd.print("/");
  lcd.print(date[2]);
  lcd.print(date[3]);
}

