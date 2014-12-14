void setColor() {
  //Color
  // #1 Custom (saved to EEPROM)
  // #2 Random Color (changes every hour) (change every 30 seconds in config mode)
  // #3 Holiday Color
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
  #ifdef DEBUG
  Serial.println(F("holidayColor Start"));
  Serial.println(month());
  #endif
  switch (month()) {
    case 1: //Snow & New Years
      //White
      #ifdef DEBUG
      Serial.println(F("White"));
      #endif
      BlinkM_fadeToRGB(0x09, 0xFF, 0xFF, 0xFF);
      break;
    case 2: //Valentines Day
      switch (random(2)){
        case 1://Red
          #ifdef DEBUG
          Serial.println(F("Red"));
          #endif
          BlinkM_fadeToRGB(0x09, 0xB6, 0x00, 0x00);
          break;
        case 2://Pink
          #ifdef DEBUG
          Serial.println(F("Pink"));
          #endif
          BlinkM_fadeToRGB(0x09, 0x79, 0x00, 0x08);
          break;
      }      //Red
      #ifdef DEBUG
    case 3: //St Patrick's Day
      //Green
      #ifdef DEBUG
      Serial.println(F("Green"));
      #endif
      BlinkM_fadeToRGB(0x09, 0x00, 0x8A, 0x05);
      break;
    case 4: //Easter
      switch (random(3)){
        case 1://Yellow
          #ifdef DEBUG
          Serial.println(F("Yellow"));
          #endif
          BlinkM_fadeToRGB(0x09, 0xFF, 0xF2, 0x28);
          break;
        case 2://Pink
          #ifdef DEBUG
          Serial.println(F("Pink"));
          #endif
          BlinkM_fadeToRGB(0x09, 0xFB, 0x61, 0xFF);
          break;
        default://Purple
          #ifdef DEBUG
          Serial.println(F("Purple"));
          #endif
          BlinkM_fadeToRGB(0x09, 0xB8, 0x28, 0xFF);
          break;
      }
      break;
    case 5: //May
      //Green
      #ifdef DEBUG
      Serial.println(F("Green"));
      #endif
      BlinkM_fadeToRGB(0x09, 0x00, 0xFF, 0x00);
      break;
    case 6: //June
      //Yellow
      #ifdef DEBUG
      Serial.println(F("Yellow"));
      #endif
      BlinkM_fadeToRGB(0x09, 0xDF, 0x34, 0x00);
      break;
    case 7: //Independence Day
      switch (random(3)){
        case 2://Red
          #ifdef DEBUG
          Serial.println(F("Red"));
          #endif
          BlinkM_fadeToRGB(0x09, 0xFF, 0x00, 0x00);
          break;
        case 1://White
          #ifdef DEBUG
          Serial.println(F("White"));
          #endif
          BlinkM_fadeToRGB(0x09, 0xFF, 0xFF, 0xFF);
          break;
        default://Blue
          #ifdef DEBUG
          Serial.println(F("Blue"));
          #endif
          BlinkM_fadeToRGB(0x09, 0x00, 0x00, 0xFF);
          break;
      }
      break;
    case 8: // August
      //Orange
      #ifdef DEBUG
      Serial.println(F("Orange"));
      #endif
      BlinkM_fadeToRGB(0x09, 0xFF, 0x34, 0x00);
      break;
    case 9: // Stptember
      //dark red, dark orange, brown
      switch (random(3)){
        case 2://Red
          #ifdef DEBUG
          Serial.println(F("Red"));
          #endif
          BlinkM_fadeToRGB(0x09, 0x66, 0x00, 0x00);
          break;
        case 1://Yellow
          #ifdef DEBUG
          Serial.println(F("Yellow"));
          #endif
          BlinkM_fadeToRGB(0x09, 0x66, 0x33, 0x00);
          break;
        default://Yellow2
          #ifdef DEBUG
          Serial.println(F("Yellow2"));
          #endif
          BlinkM_fadeToRGB(0x09, 0x66, 0x66, 0x00);
          break;
      }
      break;
    case 10:
      // Orange
      #ifdef DEBUG
      Serial.println(F("Orange"));
      #endif
      BlinkM_fadeToRGB(0x09, 0xBF, 0x4C, 0x00);
      break;
    case 11: //Thanksgiving
      switch (random(3)){
        case 2://Red Purple
          #ifdef DEBUG
          Serial.println(F("Red Purple"));
          #endif
          BlinkM_fadeToRGB(0x09, 0x97, 0x03, 0x11);
          break;
        case 1://Yellow green
          #ifdef DEBUG
          Serial.println(F("Yellow Green"));
          #endif
          BlinkM_fadeToRGB(0x09, 0x80, 0x80, 0x00);
          break;
        default://Red
          #ifdef DEBUG
          Serial.println(F("Red"));
          #endif
          BlinkM_fadeToRGB(0x09, 0x8B, 0x00, 0x00);
          break;
      }
      break;
    case 12://Christmas
      switch (random(3)){
        case 2://Red
          #ifdef DEBUG
          Serial.println(F("Red"));
          #endif
          BlinkM_fadeToRGB(0x09, 0xFF, 0x00, 0x00);
          break;
        case 1://Green
          #ifdef DEBUG
          Serial.println(F("Green"));
          #endif
          BlinkM_fadeToRGB(0x09, 0x00, 0xFF, 0x00);
          break;
        default://White
          #ifdef DEBUG
          Serial.println(F("White"));
          #endif
          BlinkM_fadeToRGB(0x09, 0xFF, 0xFF, 0xFF);
          break;
      }
      break;
    default:
      break;
  }
}

