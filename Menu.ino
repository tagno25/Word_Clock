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

  while (menu != 0){
    #ifdef DEBUG
    Serial.println(F("Menu Loop"));
    #endif
    currentMillis = millis();
    if (digitalRead(BUTTON1)==LOW){
      if(currentMillis - menuMillis1 > 3000) {//reset menu timer ot current millis when more than 6000 different
        menuMillis1 = currentMillis;
      } else if(currentMillis - menuMillis1 > 500) {//enter menu when timer is more than 4000 different from current
        menuMillis1 = currentMillis;
        menu=menu+1;
      }
    }


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
        menu = 5;
      case 3:
        //Color
        // Green (if preselected #1)
        menu = 5;
      case 4:
        //Color
        // Blue (if preselected #1)
        menu = 5;
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
      case 9:
        //Time setup
        // Minutes (Ones place)
      case 10:
        //Date setup
        // Month
      case 11:
        //Date setup
        // Day (Tens place)
      case 12:
        //Date setup
        // Day (Ones place)
      case 13:
        //Date setup
        // Year (Tens place)
      case 14:
        //Date setup
        // Year (Ones place)
      default:
        menu = 0;
        #ifdef DEBUG
        Serial.println(F("Menu exit"));
        #endif
        break;
    }
    
    #ifdef DEBUG
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

