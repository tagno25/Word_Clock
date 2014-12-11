/*
#define CONFIG	Display[2] |= (1<<5)
#define TIME	Display[2] |= (1<<6)
#define TENS	Display[2] |= (1<<7)
*/

void configMenu(){
  #ifdef DEBUG
  Serial.println(F("Entered Menu"));
  #endif
  
  byte menu=0x01;
  
  wordsoff();
  updateShiftRegister();
  long menuMillis2 = 0;
  long menuMillis3 = 0;

  while (menu != 0x00){
    #ifdef DEBUG
    Serial.println(F("Menu Loop"));
    #endif
    currentMillis = millis();
    if (digitalRead(BUTTON1)==LOW){
      if(currentMillis - menuMillis1 > 4000) {//reset menu timer ot current millis when more than 6000 different
        menuMillis1 = currentMillis;
      } else if(currentMillis - menuMillis1 > 2000) {//enter menu when timer is more than 4000 different from current
        menuMillis1 = currentMillis;
        menu=menu+1;
      }
    }


    switch (menu) {
      case 0x01:
        #ifdef DEBUG
        Serial.println(F("Menu 1"));
        #endif
        Display[2] |= (1<<5);
        updateShiftRegister();
        break;
      case 0x02:
        #ifdef DEBUG
        Serial.println(F("Menu 2"));
        #endif
        if(currentMillis - previousMillis > 500) {
          previousMillis = currentMillis;
          Display[2] ^= (1<<5);
          updateShiftRegister();
        }
        break;
      case 0x03:
        #ifdef DEBUG
        Serial.println(F("Menu 3"));
        #endif
        Display[2] |= (1<<6);
        updateShiftRegister();
        break;
      case 0x04:
        #ifdef DEBUG
        Serial.println(F("Menu 4"));
        #endif
        if(currentMillis - previousMillis > 500) {
          previousMillis = currentMillis;
          Display[2] ^= (1<<6);
          updateShiftRegister();
        }
        break;
      case 0x05:
      default:
        menu = 0x00;
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

