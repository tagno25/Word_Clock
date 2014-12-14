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
      BlinkM_fadeToRGB(0x09, 0xFF, 0xFF, 0xFF);
      break;
    case 2: //Valentines Day
      //Red
      BlinkM_fadeToRGB(0x09, 0xB6, 0x00, 0x00);
      break;
    case 3: //St Patrick's Day
      //Green
      BlinkM_fadeToRGB(0x09, 0x00, 0x8A, 0x05);
      break;
    case 4: //Easter
      switch (random(2)){
        case 1://Yellow
          BlinkM_fadeToRGB(0x09, 0xFF, 0xF2, 0x28);
          break;
        case 2://Pink
          BlinkM_fadeToRGB(0x09, 0xFB, 0x61, 0xFF);
        default://Purple
          BlinkM_fadeToRGB(0x09, 0xB8, 0x28, 0xFF);
          break;
      }
      break;
    case 5: //May
      //Green
      BlinkM_fadeToRGB(0x09, 0x00, 0xFF, 0x00);
      break;
    case 6: //June
      //Yellow?
    case 7: //Independence Day
      switch (random(2)){
        case 2://Red
          BlinkM_fadeToRGB(0x09, 0xFF, 0x00, 0x00);
          break;
        case 1://White
          BlinkM_fadeToRGB(0x09, 0xFF, 0xFF, 0xFF);
          break;
        default://Blue
          BlinkM_fadeToRGB(0x09, 0x00, 0x00, 0xFF);
          break;
      }
      break;
    case 8: // August
      //Red Orange (sunburn color)
    case 9: // Stptember
      //dark red, dark orange, brown
//    random(2);
    case 10:
      // Orange
    case 11: //Thanksgiving
      //dark red, dark orange, brown
//    random(2);
    case 12://Christmas
      switch (random(2)){
        case 2://Red
          BlinkM_fadeToRGB(0x09, 0xFF, 0x00, 0x00);
          break;
        case 1://Green
          BlinkM_fadeToRGB(0x09, 0x00, 0xFF, 0x00);
          break;
        default://White
          BlinkM_fadeToRGB(0x09, 0xFF, 0xFF, 0xFF);
          break;
      }
      break;
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
