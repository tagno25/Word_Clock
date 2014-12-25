void configMenu(){
  #ifdef DEBUG
  Serial.println(F("Entered Menu"));
  #endif
  
  byte menu=1;
  
  wordsoff();
  updateShiftRegister();
  long menuMillis2 = 0;
  long menuMillis3 = 0;
  byte option = loadOption(menu);

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
      if(currentMillis - menuMillis1 > 1000) {
        //reset menu timer to current millis when more than 1000 different
        menuMillis1 = currentMillis;
      } else if(currentMillis - menuMillis1 > 500) {
        //change menu when timer is more than 500 different from current
        
        while (digitalRead(BUTTON1)==LOW){
          //don't change menus until button is released
          currentMillis = millis();
          if(currentMillis - previousMillis > BLINKLENGHT) {
            previousMillis = currentMillis;
            TOGGLEITIS; //Menu LED toggle
          }
          updateShiftRegister();
        }
        menuMillis1 = currentMillis;
        saveOption(menu, option);//save current option
        menu=menu+1;
        #ifdef DEBUG
        Serial.print(F("loadOption: "));
        Serial.println(loadOption(menu));
        #endif
        option=loadOption(menu);//load previously set option
      }
    }
    
    if (digitalRead(BUTTON2)==LOW && digitalRead(BUTTON3)==LOW && (menu==5 || menu==6)){
      analogWrite(LEDOUTPUTENABLEPIN, 255-option);
    }


    if (digitalRead(BUTTON2)==LOW){
      if(currentMillis - menuMillis2 > 1000) {
        //reset timer to current millis when more than 1000 different
        menuMillis2 = currentMillis;
      } else if(currentMillis - menuMillis2 > 300) {
        //change option + when timer is more than 300 different from current
        menuMillis2 = currentMillis;
        option=option+1;
        option=boundOption(menu,option,false);//check option boundry and rollover
        #ifdef DEBUG
        Serial.println(option);
        #endif
      }
    }

    if (digitalRead(BUTTON3)==LOW){
      if(currentMillis - menuMillis3 > 1000) {
        //reset menu timer to current millis more than 1000 different
        menuMillis3 = currentMillis;
      } else if(currentMillis - menuMillis3 > 300) {
        //change option - when timer is more than 300 different from current
        menuMillis3 = currentMillis;
        option=option-1;
        option=boundOption(menu,option,true);//check option boundry and rollover
        #ifdef DEBUG
        Serial.println(option);
        #endif
      }
    }

    
    BLANKITIS;
    BLANKHALF;
    BLANKMTEN;
    BLANKONE;
    BLANKTWO;
    BLANKTHREE;
    BLANKFOUR;
    BLANKHFIVE;
    BLANKSIX;
    BLANKSEVEN;
    BLANKEIGHT;
    BLANKNINE;
    BLANKHTEN;
    BLANKELEVEN;
    BLANKTWELVE;
    BLANKQUARTER;
    BLANKTWENTY;
    BLANKCONFIG;
    BLANKTIME;
    BLANKOCLOCK;
    CONFIG;

    if( menu==1 || (menu>=7 && menu!=11) ){
      if(menu==7 && option>=12){
        OCLOCK;
      } else if(option==12){
        TWELVE;
      }
      switch (option%12){
        case 0:
          TWELVE;
          break;
        case 1:
          ONE;
          break;
        case 2:
          TWO;
          break;
        case 3:
          THREE;
          break;
        case 4:
          FOUR;
          break;
        case 5:
          HFIVE;
          break;
        case 6:
          SIX;
          break;
        case 7:
          SEVEN;
          break;
        case 8:
          EIGHT;
          break;
        case 9:
          NINE;
          break;
        case 10:
          HTEN;
          break;
        case 11:
          ELEVEN;
          break;
        default:
          break;
      }
    }else if( menu==11 ){
      if (option/10==1){
        MTEN;
      } else if (option/10==2){
        TWENTY;
      } else if (option/10==3){
        MTEN;
        TWENTY;
      }
      switch (option%10){
        case 1:
          ONE;
          break;
        case 2:
          TWO;
          break;
        case 3:
          THREE;
          break;
        case 4:
          FOUR;
          break;
        case 5:
          HFIVE;
          break;
        case 6:
          SIX;
          break;
        case 7:
          SEVEN;
          break;
        case 8:
          EIGHT;
          break;
        case 9:
          NINE;
          break;
        default:
          break;
      }
    }

    if (menu == 5 || menu == 6){
     menu=7;
     option=loadOption(menu);
    } 

    switch (menu) {
      case 1:
        //Color
        // #1 Custom (saved to EEPROM)
        // #2 Random Color (changes every hour) (change every 30 seconds in config mode)
        // #3 Holiday Color
        #ifdef DEBUG
        Serial.println(F("Menu 1: Color Palette"));
        #endif
        TO;
        break;
      case 2:
        //Color
        // Red (if preselected #1)
        if (loadOption(1)!=1) {
          //skip to Brightness
          menu = 5;
        } else {
          #ifdef DEBUG
          Serial.println(F("Menu 2: Red"));
          #endif
          if(currentMillis - previousMillis > BLINKLENGHT) {
            previousMillis = currentMillis;
            TOGGLEDATE;//"To" LED blink
          }
          ONE;
          TWO;
          THREE;
          FOUR;
          HFIVE;
          SIX;
          SEVEN;
          EIGHT;
          NINE;
          HTEN;
          ELEVEN;
          TWELVE;
        }
        break;
      case 3:
        //Color
        // Green (if preselected #1)
        if (loadOption(1)!=1) {
          //skip to Brightness
          menu = 5;
        } else {
          #ifdef DEBUG
          Serial.println(F("Menu 3: Green"));
          #endif
          if(currentMillis - previousMillis > BLINKLENGHT) {
            previousMillis = currentMillis;
            TOGGLEDATE;//"To" LED blink
          }
          ONE;
          TWO;
          THREE;
          FOUR;
          HFIVE;
          SIX;
          SEVEN;
          EIGHT;
          NINE;
          HTEN;
          ELEVEN;
          TWELVE;
        }
        break;
      case 4:
        //Color
        // Blue (if preselected #1)
        if (loadOption(1)!=1) {
          //skip to Brightness
          menu = 5;
        } else {
          #ifdef DEBUG
          Serial.println(F("Menu 4: Blue"));
          #endif
          if(currentMillis - previousMillis > BLINKLENGHT) {
            previousMillis = currentMillis;
            TOGGLEDATE;//"To" LED blink
          }
          ONE;
          TWO;
          THREE;
          FOUR;
          HFIVE;
          SIX;
          SEVEN;
          EIGHT;
          NINE;
          HTEN;
          ELEVEN;
          TWELVE;
        }
        break;
        case 5:
        //Brightness Day
        // Brightness up on Button2 press
        // Brightness down on Button3 press 
        #ifdef DEBUG
        Serial.println(F("Menu 5: Day Brightness"));
        #endif
        BLANKDATE;
        PAST;
        ONE;
        TWO;
        THREE;
        FOUR;
        HFIVE;
        SIX;
        SEVEN;
        EIGHT;
        NINE;
        HTEN;
        ELEVEN;
        TWELVE;
        break;
      case 6:
        //Brightness Night
        // Brightness up on Button2 press
        // Brightness down on Button3 press 
        #ifdef DEBUG
        Serial.println(F("Menu 6: Night Brightness"));
        #endif
        if(currentMillis - previousMillis > BLINKLENGHT) {
          previousMillis = currentMillis;
          TOGGLEPAST; //"Past" LED Blink
        }
        ONE;
        TWO;
        THREE;
        FOUR;
        HFIVE;
        SIX;
        SEVEN;
        EIGHT;
        NINE;
        HTEN;
        ELEVEN;
        TWELVE;
        break;
      case 7:
        //Time setup
        // Hour
        #ifdef DEBUG
        Serial.println(F("Menu 7: Hour"));
        #endif
        BLANKPAST;
        BLANKTO;
        TIME;
        break;
      case 8:
        //Time setup
        // Minutes (Tens place)
        #ifdef DEBUG
        Serial.println(F("Menu 8: Minutes (Tens place)"));
        #endif
        TIME;
        QUARTER;
        break;
      case 9:
        //Time setup
        // Minutes (Ones place)
        #ifdef DEBUG
        Serial.println(F("Menu 9: Minutes (Ones place)"));
        #endif
        TIME;
        HALF;
        break;
      case 10:
        //Date setup
        // Month
        #ifdef DEBUG
        Serial.println(F("Menu 10: Month"));
        #endif
        DATE;
        break;
      case 11:
        //Date setup
        // Day
        #ifdef DEBUG
        Serial.println(F("Menu 11: Day"));
        #endif
        if(currentMillis - previousMillis > BLINKLENGHT) {
          previousMillis = currentMillis;
          TOGGLEDATE; //"Past" LED Blink
        }
        break;
      case 12:
        //Date setup
        // Year (Tens place)
        #ifdef DEBUG
        Serial.println(F("Menu 12: Year (Tens place)"));
        #endif
        DATE;
        QUARTER;
        break;
      case 13:
        //Date setup
        // Year (Ones place)
        #ifdef DEBUG
        Serial.println(F("Menu 13: Year (Ones place)"));
        #endif
        DATE;
        HALF;
        break;
      default:
        menu = 0;
        #ifdef DEBUG
        Serial.println(F("Menu exit"));
        #endif
        break;
    }
    
    setBrightness();
    updateShiftRegister();
    
    #ifdef DEBUG
    Serial.print(F("Option: "));
    Serial.println(option);
    delay(500);
    #endif
  }
  
  #ifdef DEBUG
  Serial.println(F("Close Menu"));
  #endif
  
  //Save time to RTC
  RTC.set(now());
  
  //reset shift register data then display time
  wordsoff();
  updateShiftRegister();
  setColor();
  setBrightness();
  ledDisplayTime();
}

void saveOption(byte menuNumber, byte optionValue){
  utc = now();
  local = myTZ.toLocal(utc, &tcr);
      
  switch (menuNumber) {
    case 1:
      //Color Palette
      return(EEPROM.write(10, optionValue));
      setColor();
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
      #ifdef DEBUG
      Serial.println(optionValue);
      #endif
      if (myTZ.locIsDST(local)){
        optionValue=optionValue+5;
        setTime(optionValue, minute(), second(), day(), month(), year());
      } else {
        optionValue=optionValue+6;
        setTime(optionValue, minute(), second(), day(), month(), year());
      }
      break;
    case 8:
      //Time setup
      // Minutes (Tens place)
      #ifdef DEBUG
      Serial.println((optionValue*10)+loadOption(9));
      #endif
      setTime(hour(), (optionValue*10)+loadOption(9), second(), day(), month(), year());
      break;
    case 9:
      //Time setup
      // Minutes (Ones place)
      #ifdef DEBUG
      Serial.println(loadOption(8)+optionValue);
      #endif
      setTime(hour(), loadOption(8)+optionValue, second(), day(), month(), year());
      break;
    case 10:
      //Date setup
      // Month
      #ifdef DEBUG
      Serial.println(optionValue);
      #endif
      setTime(hour(), minute(), second(), day(), optionValue, year());
      break;
    case 11:
      //Date setup
      // Day
      #ifdef DEBUG
      Serial.println(optionValue);
      #endif
      setTime(hour(), minute(), second(), optionValue, month(), year());
      break;
    case 12:
      //Date setup
      // Year (Tens place)
      #ifdef DEBUG
      Serial.println(2000+(int(optionValue)*10)+(year(local)%10));
      #endif
      setTime(hour(), minute(), second(), day(), month(), int(loadOption(13)+(optionValue*10))+2000);
      break;
    case 13:
      //Date setup
      // Year (Ones place)
      #ifdef DEBUG
      Serial.println(int(loadOption(13)+optionValue)+2000);
      #endif
      setTime(hour(), minute(), second(), day(), month(), int((loadOption(12)*10)+optionValue)+2000);
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
      // Day
      return(day(local));
      break;
    case 12:
      //Date setup
      // Year (Tens place)
      return((year(local)/10)%10);
      break;
    case 13:
      //Date setup
      // Year (Ones place)
      return(year(local)%10);
      break;
    default:
      return(0);
      break;
  }
}

byte boundOption(byte menuNumber, byte optionValue, boolean inc){
  byte monthLength=31;
  switch (menuNumber) {
    case 2:
      //Color (Red)
      BlinkM_setRGB(0x09, optionValue*4, EEPROM.read(12), EEPROM.read(13));
      menuNumber=6;
      break;
    case 3:
      //Color (Green)
      BlinkM_setRGB(0x09, EEPROM.read(11), optionValue*4, EEPROM.read(13));
      menuNumber=6;
      break;
    case 4:
      //Color (Blue)
      BlinkM_setRGB(0x09, EEPROM.read(11), EEPROM.read(12), optionValue*4);
      menuNumber=6;
      break;
    }
  switch (menuNumber) {
    case 1:
    //Color
      if(optionValue>200||optionValue==0){
        saveOption(1, 3);
        setColor();
        return (3);
      } else if(optionValue>3){
        saveOption(1, 1);
        setColor();
        return (1);
      } else {
        saveOption(1, optionValue);
        setColor();
        return(optionValue);
      }
    break;
    case 2:
      //Color (Red)
    case 3:
      //Color (Green)
    case 4:
      //Color (Blue)
    case 5:
      //Brightness Day
    case 6:
      //Brightness Night
      if (inc){
        return(optionValue+7);
      } else {
        return(optionValue-7);
      }
      break;
    case 7:
      //Time setup
      // Hour
      if(optionValue>200){
        return (23);
      } else if(optionValue>23){
        return (0);
      } else {
        return(optionValue);
      }
      break;
    case 8:
      //Time setup
      // Minutes (Tens place)
      if(optionValue>200){
        return (5);
      } else if(optionValue>5){
        return (0);
      } else {
        return(optionValue);
      }
      break;
    case 9:
      //Time setup
      // Minutes (Ones place)
      if(optionValue>200){
        return (9);
      } else if(optionValue>9){
        return (0);
      } else {
        return(optionValue);
      }
      break;
    case 10:
      //Date setup
      // Month
      if(optionValue>200||optionValue==0){
        return (12);
      } else if(optionValue>12){
        return (1);
      } else {
        return(optionValue);
      }
      break;
    case 11:
      //Date setup
      // Day
      if (month()==2) { // february
        if (year()%4 != 0 || (year()%100 == 0 && year()%400 != 0)) {
          monthLength=29; //is leap year
        } else {
          monthLength=28; //is not leap year
        }
      } else if(month()==4||month()==6||month()==9||month()==11) {
        monthLength=30;
      }
      if(optionValue>200||optionValue==0){
        return (monthLength);
      } else if(optionValue>monthLength){
        return (0);
      } else {
        return(optionValue);
      }
      break;
    case 12:
      //Date setup
      // Year (Tens place)
      if(optionValue>200){
        return (9);
      } else if(optionValue>9){
        return (0);
      } else {
        return(optionValue);
      }
      break;
    case 13:
      //Date setup
      // Year (Ones place)
      if(optionValue>200){
        return (9);
      } else if(optionValue>9){
        return (0);
      } else {
        return(optionValue);
      }
      break;
    default:
      return(1);
      break;
  }
}

