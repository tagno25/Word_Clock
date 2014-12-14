/*
#define CONFIG	Display[2] |= (1<<5)
#define TIME	Display[2] |= (1<<6)
#define TENS	Display[2] |= (1<<7)

#define TWELVE	Display[1] |= (1<<0)
#define ONE	Display[1] |= (1<<1)
#define TWO	Display[1] |= (1<<2)
#define THREE	Display[1] |= (1<<3)
#define FOUR	Display[1] |= (1<<4)
#define HFIVE	Display[1] |= (1<<5)
#define SIX	Display[1] |= (1<<6)
#define SEVEN	Display[1] |= (1<<7)
#define EIGHT	Display[2] |= (1<<0)
#define NINE	Display[2] |= (1<<1)
#define HTEN	Display[2] |= (1<<2)
#define ELEVEN	Display[2] |= (1<<3)
#define OCLOCK	Display[2] |= (1<<4)
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
      if(currentMillis - menuMillis1 > 3000) {
        //reset menu timer to current millis when more than 3000 different
        menuMillis1 = currentMillis;
      } else if(currentMillis - menuMillis1 > 250) {
        //change menu when timer is more than 500 different from current
        while (digitalRead(BUTTON1)==LOW){}//don't change menus until button is released
        
        menuMillis1 = currentMillis;
        saveOption(menu, option);//save current option
        menu=menu+1;
        option=loadOption(menu);//load previously set option
        #ifdef DEBUG
        Serial.print("New option: ");
        Serial.println(option);
        #endif
      }
    }

    if (digitalRead(BUTTON2)==LOW){
      if(currentMillis - menuMillis2 > 3000) {
        //reset timer to current millis when more than 3000 different
        menuMillis2 = currentMillis;
      } else if(currentMillis - menuMillis2 > 150) {
        //change option + when timer is more than 200 different from current
        menuMillis2 = currentMillis;
        option=option+1;
        option=boundOption(menu,option);//check option boundry and rollover
      }
    }

    if (digitalRead(BUTTON3)==LOW){
      if(currentMillis - menuMillis3 > 3000) {
        //reset menu timer to current millis more than 3000 different
        menuMillis3 = currentMillis;
      } else if(currentMillis - menuMillis1 > 150) {
        //change option - when timer is more than 200 different from current
        menuMillis3 = currentMillis;
        option=option-1;
        option=boundOption(menu,option);//check option boundry and rollover
      }
    }

    
    Display[0] &= ~(1<<0);
    Display[1]=0;
    for (byte n=0; n<5; ++n) {
      Display[2] &= ~(1<<n);
    }
    CONFIG;

    if(menu==1||menu>=7){
      switch (option){
        case 12:
          if(menu==7){
            OCLOCK;
          } else {
            TWELVE;
          }
        case 0:
          TWELVE;
          break;
        case 13:
          OCLOCK;
        case 1:
          ONE;
          break;
        case 14:
          OCLOCK;
        case 2:
          TWO;
          break;
        case 15:
          OCLOCK;
        case 3:
          THREE;
          break;
        case 16:
          OCLOCK;
        case 4:
          FOUR;
          break;
        case 17:
          OCLOCK;
        case 5:
          HFIVE;
          break;
        case 18:
          OCLOCK;
        case 6:
          SIX;
          break;
        case 19:
          OCLOCK;
        case 7:
          SEVEN;
          break;
        case 20:
          OCLOCK;
        case 8:
          EIGHT;
          break;
        case 21:
          OCLOCK;
        case 9:
          NINE;
          break;
        case 22:
          OCLOCK;
        case 10:
          HTEN;
          break;
        case 23:
          OCLOCK;
        case 11:
          ELEVEN;
          break;
        default:
          break;
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
/*        
        Display[2] |= (1<<5);//Menu LED on
*/        
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
        } else {
          Display[1]=255;

          BlinkM_setRGB(0x09, (option*8)-1, EEPROM.read(12), EEPROM.read(13));
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
        } else {
          Display[1]=255;
          

          BlinkM_setRGB(0x09, EEPROM.read(11), (option*8)-1, EEPROM.read(13));
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
        } else {
          Display[1]=255;

          BlinkM_setRGB(0x09, EEPROM.read(11), EEPROM.read(12), (option*8)-1);
        }
        break;
        case 5:
        //Brightness Day
        // Brightness up on Button2 press
        // Brightness down on Button3 press 
        #ifdef DEBUG
        Serial.println(F("Menu 5"));
        #endif
/*        
        if(currentMillis - previousMillis > 500) {
          previousMillis = currentMillis;
          Display[2] ^= (1<<5); //Menu LED toggle
        }
*/        
        
        Display[1]=255;
        break;
      case 6:
        //Brightness Night
        // Brightness up on Button2 press
        // Brightness down on Button3 press 
        #ifdef DEBUG
        Serial.println(F("Menu 6"));
        #endif
/*        
        Display[2] |= (1<<6);//Time LED on
*/        
        
        Display[1]=255;
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
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print(":");
  Serial.println(year());
  #endif
  
  //Save time to RTC
  RTC.set(now());
  
  //reset shift register data then display time
  wordsoff();
  setColor();
  ledDisplayTime();
  setBrightness();
  updateShiftRegister();
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
      return(EEPROM.write(11, (optionValue*8)-1));
      break;
    case 3:
      //Color (Green)
      return(EEPROM.write(12, (optionValue*8)-1));
      break;
    case 4:
      //Color (Blue)
      return(EEPROM.write(13, (optionValue*8)-1));
      break;
    case 5:
      //Brightness Day
      return(EEPROM.write(14, (optionValue*8)-1));
      break;
    case 6:
      //Brightness Night
      return(EEPROM.write(15, (optionValue*8)-1));
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
      // Day (Tens place)
      #ifdef DEBUG
      Serial.println((optionValue*10)+loadOption(12));
      #endif
      setTime(hour(), minute(), second(), (optionValue*10)+loadOption(12), month(), year());
      break;
    case 12:
      //Date setup
      // Day (Ones place)
      #ifdef DEBUG
      Serial.println(loadOption(11)+optionValue);
      #endif
      setTime(hour(), minute(), second(), (loadOption(11)*10)+optionValue, month(), year());
      break;
    case 13:
      //Date setup
      // Year (Tens place)
      #ifdef DEBUG
      Serial.println(2000+(int(optionValue)*10)+(year(local)%10));
      #endif
      setTime(hour(), minute(), second(), day(), month(), int(loadOption(14)+(optionValue*10))+2000);
      break;
    case 14:
      //Date setup
      // Year (Ones place)
      #ifdef DEBUG
      Serial.println(int(loadOption(13)+optionValue)+2000);
      #endif
      setTime(hour(), minute(), second(), day(), month(), int((loadOption(13)*10)+optionValue)+2000);
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
      return((EEPROM.read(11)-1)/8);
      break;
    case 3:
      //Color (Green)
      return((EEPROM.read(12)-1)/8);
      break;
    case 4:
      //Color (Blue)
      return((EEPROM.read(13)-1)/8);
      break;
    case 5:
      //Brightness Day
      return((EEPROM.read(14)-1)/8);
      break;
    case 6:
      //Brightness Night
      return((EEPROM.read(15)-1)/8);
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

byte boundOption(byte menuNumber, byte optionValue){
  switch (menuNumber) {
    case 2:
      //Color (Red)
      BlinkM_setRGB(0x09, optionValue*8, EEPROM.read(12), EEPROM.read(13));
      menuNumber=6;
      break;
    case 3:
      //Color (Green)
      BlinkM_setRGB(0x09, EEPROM.read(11), optionValue*8, EEPROM.read(13));
      menuNumber=6;
      break;
    case 4:
      //Color (Blue)
      BlinkM_setRGB(0x09, EEPROM.read(11), EEPROM.read(12), optionValue*8);
      menuNumber=6;
      break;
    }
  switch (menuNumber) {
    case 1:
    //Color
      if(optionValue>200||optionValue==0){
        return (3);
      } else if(optionValue>3){
        return (1);
      } else {
        return(optionValue);
      }
    break;
    case 5:
      //Brightness Day
    case 6:
      //Brightness Night
      if(optionValue>200){
        analogWrite(LEDOUTPUTENABLEPIN, 0);
        return (32);
      } else if(optionValue>32){
        analogWrite(LEDOUTPUTENABLEPIN, 255);
        return (0);
      } else {
        analogWrite(LEDOUTPUTENABLEPIN, (255-(optionValue*8)));
        return(optionValue);
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
      // Day (Tens place)
      if(optionValue>200){
        return (3);
      } else if(optionValue>3){
        return (0);
      } else {
        return(optionValue);
      }
      break;
    case 12:
      //Date setup
      // Day (Ones place)
      if(optionValue>200 && (day(local)/10)==3){
        return (1); //wrap to 1 if greater than 200 and a 3X day
      } else if(optionValue>200||(optionValue==0 && (day(local)/10)==0)){
        return (9); //wrap to 9 if greater than 200 or (equal to 0 and a 0X day) 
      } else if(optionValue>9 && (day(local)/10)==0){
        return (1); //wrap to 1 if greater than 9 and a 0X day
      } else if(optionValue>9||(optionValue>1 && (day(local)/10)==3)){
        return (0); //wrap to 0 if greater than 9 or (grearter than 1 and a 3X day)
      } else {
        return(optionValue);
      }
      break;
    case 13:
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
    case 14:
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
