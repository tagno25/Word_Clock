void setColor() {
  //Color
  // #1 Custom (saved to EEPROM)
  // #2 Random Color (changes every hour) (change every 30 seconds in config mode)
  // #3 Holiday Color
  // #4 Birthstone Color
  switch (EEPROM.read(10)) {
    case 1:
      #ifdef DEBUG
      Serial.println(F("Custom Color"));
      #endif
      BlinkM_fadeToRGB(0x09, EEPROM.read(11), EEPROM.read(12), EEPROM.read(13));
      break;
    case 2:
      #ifdef DEBUG
      Serial.println(F("Random Color"));
      #endif
      BlinkM_fadeToRandomRGB(0x09, 255, 255, 255);
      break;
    case 3:
      #ifdef DEBUG
      Serial.println(F("Holiday Color"));
      #endif
      holidayColor();
      break;
    case 4:
      #ifdef DEBUG
      Serial.println(F("Birth Stone Color"));
      #endif
      birthStoneColor();
      break;
    default:
      break;
  }
}

void holidayColor() {
  switch (month()) {
    case 1: //Snow & New Years
    //White
    case 2: //Valentines Day
    //Red
    case 3: //St Patrick's Day
    //Green
    case 4: //Easter
    //Yellow & Purple
    case 5: //May
    //Green?
    case 6: //June
    //Yellow?
    case 7: //Independence Day
    //Red, White, Blue
    case 8: // August
    //Red Orange (sunburn color)
    case 9: // Stptember
    //dark red, dark orange, brown
    case 10:
    // Orange
    case 11: //Thanksgiving
    //dark red, dark orange, brown
    case 12://Ghristmas
    //Red & Green
    default:
      break;
  }
}

void birthStoneColor() {
  // http://bit.ly/1vrDKuX
  switch (month()) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    default:
      break;
  }
}
