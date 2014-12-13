/*
#define CONFIG	Display[2] |= (1<<5)
#define TIME	Display[2] |= (1<<6)
#define TENS	Display[2] |= (1<<7)
*/

void configMenu(){
  #ifdef DEBUG
  Serial.println(F("Entered Menu"));
  #endif
  
  byte menu=1;
  
  wordsoff();
  updateShiftRegister();
  long menuMillis2 = 0;
  long menuMillis3 = 0;
  byte option = 1;

  menuMillis1 = currentMillis;

  while (menu != 0){
    #ifdef DEBUG
    Serial.println(F("Menu Loop"));
    #endif

    currentMillis = millis();
    

    if(currentMillis - menuMillis1 > 60000 && currentMillis - menuMillis2 > 60000 && currentMillis - menuMillis3 > 60000) {
      //exit config if more than 60 seconds from any button press
      menu = 0;
    }
    
    if (digitalRead(BUTTON1)==LOW){
      if(currentMillis - menuMillis1 > 3000) {
        //reset menu timer to current millis when more than 3000 different
        menuMillis1 = currentMillis;
      } else if(currentMillis - menuMillis1 > 500) {
        //change menu when timer is more than 500 different from current
        menuMillis1 = currentMillis;
        saveOption(menu, option);//save current option
        menu=menu+1;
        option=loadOption(menu);//load previously set option 
      }
    }

    if (digitalRead(BUTTON2)==LOW){
      if(currentMillis - menuMillis2 > 3000) {
        //reset timer to current millis when more than 3000 different
        menuMillis2 = currentMillis;
      } else if(currentMillis - menuMillis2 > 200) {
        //change option + when timer is more than 200 different from current
        menuMillis2 = currentMillis;
        option=option+1;
      }
    }

    if (digitalRead(BUTTON3)==LOW){
      if(currentMillis - menuMillis3 > 3000) {
        //reset menu timer to current millis more than 3000 different
        menuMillis3 = currentMillis;
      } else if(currentMillis - menuMillis1 > 200) {
        //change option - when timer is more than 200 different from current
        menuMillis3 = currentMillis;
        option=option-1;
      }
    }

    boundOption(menu);//check option boundry and rollover

    switch (menu) {
      case 1:
        //Color
        // show what would be the curent color
        // use 1-12 LED to show pre-configured
        // #1 Custom (saved to EEPROM)
        // #2 Random Color (changes every hour) (change every 30 seconds in config mode)
        // #3 Holiday Color
        // #4 Birthstone Color
        #ifdef DEBUG
        Serial.println(F("Menu 1"));
        #endif
        Display[2] |= (1<<5);//Menu LED on
        updateShiftRegister();
        break;
      case 2:
        //Color
        // Red (if preselected #1)
        #ifdef DEBUG
        Serial.println(F("Menu 2"));
        #endif
        if (loadOption(1)!=1) {
          //skip to Brightness
          menu = 5;
        }
        break;
      case 3:
        //Color
        // Green (if preselected #1)
        #ifdef DEBUG
        Serial.println(F("Menu 3"));
        #endif
        if (loadOption(1)!=1) {
          //skip to Brightness
          menu = 5;
        }
        break;
      case 4:
        //Color
        // Blue (if preselected #1)
        #ifdef DEBUG
        Serial.println(F("Menu 4"));
        #endif
        if (loadOption(1)!=1) {
          //skip to Brightness
          menu = 5;
        }
        break;
        case 5:
        //Brightness Day
        // Brightness up on Button2 press
        // Brightness down on Button3 press 
        #ifdef DEBUG
        Serial.println(F("Menu 5"));
        #endif
        if(currentMillis - previousMillis > 500) {
          previousMillis = currentMillis;
          Display[2] ^= (1<<5); //Menu LED toggle
          updateShiftRegister();
        }
        break;
      case 6:
        //Brightness Night
        // Brightness up on Button2 press
        // Brightness down on Button3 press 
        #ifdef DEBUG
        Serial.println(F("Menu 6"));
        #endif
        Display[2] |= (1<<6);//Time LED on
        updateShiftRegister();
        break;
      case 7:
        //Time setup
        // Hour
        // blink number for PM
        #ifdef DEBUG
        Serial.println(F("Menu 7"));
        #endif
        if(currentMillis - previousMillis > 500) {
          previousMillis = currentMillis;
          Display[2] ^= (1<<6);//Time LED toggle
          updateShiftRegister();
        }
        break;
      case 8:
        //Time setup
        // Minutes (Tens place)
        #ifdef DEBUG
        Serial.println(F("Menu 8"));
        #endif
        break;
      case 9:
        //Time setup
        // Minutes (Ones place)
        #ifdef DEBUG
        Serial.println(F("Menu 9"));
        #endif
        break;
      case 10:
        //Date setup
        // Month
        #ifdef DEBUG
        Serial.println(F("Menu 10"));
        #endif
        break;
      case 11:
        //Date setup
        // Day (Tens place)
        #ifdef DEBUG
        Serial.println(F("Menu 11"));
        #endif
        break;
      case 12:
        //Date setup
        // Day (Ones place)
        #ifdef DEBUG
        Serial.println(F("Menu 12"));
        #endif
        break;
      case 13:
        //Date setup
        // Year (Tens place)
        #ifdef DEBUG
        Serial.println(F("Menu 13"));
        #endif
        break;
      case 14:
        //Date setup
        // Year (Ones place)
        #ifdef DEBUG
        Serial.println(F("Menu 14"));
        #endif
        break;
      default:
        menu = 0;
        #ifdef DEBUG
        Serial.println(F("Menu exit"));
        #endif
        break;
    }
    
    #ifdef DEBUG
    Serial.print(F("Option: "));
    Serial.println(option);
    delay(500);
    #endif
  }
  
  #ifdef DEBUG
  Serial.println(F("Close Menu"));
  #endif
  
  //reset shift register data then display time
  wordsoff();
  ledDisplayTime();
  updateShiftRegister();
}

void saveOption(byte menuNumber, byte optionValue){
  utc = now();
  local = myTZ.toLocal(utc, &tcr);

  switch (menuNumber) {
    case 1:
      //Color Palette
      return(EEPROM.write(10, optionValue));
      break;
    case 2:
      //Color (Red)
      return(EEPROM.write(11, optionValue));
      break;
    case 3:
      //Color (Green)
      return(EEPROM.write(12, optionValue));
      break;
    case 4:
      //Color (Blue)
      return(EEPROM.write(13, optionValue));
      break;
    case 5:
      //Brightness Day
      return(EEPROM.write(14, optionValue));
      break;
    case 6:
      //Brightness Night
      return(EEPROM.write(15, optionValue));
      break;
    case 7:
      //Time setup
      // Hour
      break;
    case 8:
      //Time setup
      // Minutes (Tens place)
      break;
    case 9:
      //Time setup
      // Minutes (Ones place)
      break;
    case 10:
      //Date setup
      // Month
      break;
    case 11:
      //Date setup
      // Day (Tens place)
      break;
    case 12:
      //Date setup
      // Day (Ones place)
      break;
    case 13:
      //Date setup
      // Year (Tens place)
      break;
    case 14:
      //Date setup
      // Year (Ones place)
      break;
    default:
      break;
  }
}

byte loadOption(byte menuNumber){
  utc = now();
  local = myTZ.toLocal(utc, &tcr);

  switch (menuNumber) {
    case 1:
      //Color Palette
      return(EEPROM.read(10));
      break;
    case 2:
      //Color (Red)
      return(EEPROM.read(11));
      break;
    case 3:
      //Color (Green)
      return(EEPROM.read(12));
      break;
    case 4:
      //Color (Blue)
      return(EEPROM.read(13));
      break;
    case 5:
      //Brightness Day
      return(EEPROM.read(14));
      break;
    case 6:
      //Brightness Night
      return(EEPROM.read(15));
      break;
    case 7:
      //Time setup
      // Hour
      return(hour(local));
      break;
    case 8:
      //Time setup
      // Minutes (Tens place)
      return(minute(local)/10);
      break;
    case 9:
      //Time setup
      // Minutes (Ones place)
      return(minute(local)%10);
      break;
    case 10:
      //Date setup
      // Month
      return(month(local));
      break;
    case 11:
      //Date setup
      // Day (Tens place)
      return(day(local)/10);
      break;
    case 12:
      //Date setup
      // Day (Ones place)
      return(day(local)%10);
      break;
    case 13:
      //Date setup
      // Year (Tens place)
      return((year(local)/10)%10);
      break;
    case 14:
      //Date setup
      // Year (Ones place)
      return(year(local)%10);
      break;
    default:
      return(0);
      break;
  }
}

byte boundOption(byte menuNumber){
  switch (menuNumber) {
    case 1:
    //Color
    // show what would be the curent color
    // use 1-12 LED to show pre-configured
    // #1 Custom (saved to EEPROM)
    // #2 Random Color (changes every hour) (change every 30 seconds in config mode)
    // #3 Holiday Color
    // #4 Birthstone Color
    break;
    case 2:
      //Color
      // Red (if preselected #1)
      break;
    case 3:
      //Color
      // Green (if preselected #1)
      break;
    case 4:
      //Color
      // Blue (if preselected #1)
      break;
    case 5:
      //Brightness Day
      break;
    case 6:
      //Brightness Night
      break;
    case 7:
      //Time setup
      // Hour
      break;
    case 8:
      //Time setup
      // Minutes (Tens place)
      break;
    case 9:
      //Time setup
      // Minutes (Ones place)
      break;
    case 10:
      //Date setup
      // Month
      break;
    case 11:
      //Date setup
      // Day (Tens place)
      break;
    case 12:
      //Date setup
      // Day (Ones place)
      break;
    case 13:
      //Date setup
      // Year (Tens place)
      break;
    case 14:
      //Date setup
      // Year (Ones place)
      break;
    default:
      return(1);
      break;
  }
}
