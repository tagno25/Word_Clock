// Display output pin assignments
#define ITIS	Display[0] |= (1<<0)
#define TWENTY 	Display[0] |= (1<<1)  
#define QUARTER	Display[0] |= (1<<2)
#define HALF	Display[0] |= (1<<3)
#define MTEN	Display[0] |= (1<<4)
#define MFIVE	Display[0] |= (1<<5)
#define PAST	Display[0] |= (1<<6)
#define TO	Display[0] |= (1<<7)
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
#define CONFIG	Display[2] |= (1<<5)
#define TIME	Display[2] |= (1<<6)
#define TENS	Display[2] |= (1<<7)

void ledDisplayTime(){
  
  utc = now();
  local = myTZ.toLocal(utc, &tcr);
  int iHour=hour(local);
  int iMinute=minute(local);

  // start by clearing the display to a known state
  wordsoff();

  // Now, turn on the "It is" leds
  ITIS;
  #ifdef DEBUG
  Serial.print(F("updateDisplay (It is "));
  #endif

  // now we display the appropriate minute counter
  switch (iMinute) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      OCLOCK;
      break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      MFIVE; 
      PAST;
      #ifdef DEBUG
      Serial.print(F("Five Past "));
      #endif
      break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
      MTEN;
      PAST;
      #ifdef DEBUG
      Serial.print(F("Ten Past "));
      #endif
      break;
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
      QUARTER;
      PAST;
      #ifdef DEBUG
      Serial.print(F("Quarter Past "));
      #endif
      break;
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
      TWENTY;
      PAST;
      #ifdef DEBUG
      Serial.print(F("Twenty Past "));
      #endif
      break;
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
      TWENTY; 
      MFIVE;
      PAST;
      #ifdef DEBUG
      Serial.print(F("Twenty Five Past "));
      #endif
      break;
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
      HALF;
      PAST;
      #ifdef DEBUG
      Serial.print(F("Half Past "));
      #endif
      break;
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
      TWENTY; 
      MFIVE;
      TO;
      iHour=iHour+1;
      #ifdef DEBUG
      Serial.print(F("Twenty Five To "));
      #endif
      break;
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
      TWENTY;
      TO;
      iHour=iHour+1;
      #ifdef DEBUG
      Serial.print(F("Twenty To "));
      #endif
      break;
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
      QUARTER; 
      TO;
      iHour=iHour+1;
      #ifdef DEBUG
      Serial.print(F("Quarter To "));
      #endif
      break;
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
      MTEN;
      TO;
      iHour=iHour+1;
      #ifdef DEBUG
      Serial.print(F("Ten To "));
      #endif
      break;
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
      MFIVE;
      TO;
      iHour=iHour+1;
      #ifdef DEBUG
      Serial.print(F("Five To "));
      #endif
      break;
    default:
      break;
  }
  
  switch (iHour) {
    case 1:
    case 13:
    case 25:
      ONE;
      #ifdef DEBUG
      Serial.print(F("One"));
      #endif
      break;
    case 2:
    case 14:
      TWO;
      #ifdef DEBUG
      Serial.print(F("Two"));
      #endif
      break;
    case 3:
    case 15:
      THREE;
      #ifdef DEBUG
      Serial.print(F("Three"));
      #endif
      break;
    case 4:
    case 16:
      FOUR;
      #ifdef DEBUG
      Serial.print(F("Four"));
      #endif
      break;
    case 5:
    case 17:
      HFIVE;
      #ifdef DEBUG
      Serial.print(F("Five"));
      #endif
      break;
    case 6:
    case 18:
      SIX;
      #ifdef DEBUG
      Serial.print(F("Six"));
      #endif
      break;
    case 7:
    case 19:
      SEVEN;
      #ifdef DEBUG
      Serial.print(F("Seven"));
      #endif
      break;
    case 8:
    case 20:
      EIGHT;
      #ifdef DEBUG
      Serial.print(F("Eight"));
      #endif
      break;
    case 9:
    case 21:
      NINE;
      #ifdef DEBUG
      Serial.print(F("Nine"));
      #endif
      break;
    case 10:
    case 22: 
      HTEN;
      #ifdef DEBUG
      Serial.print(F("Ten"));
      #endif
      break;
    case 11:
    case 23: 
      ELEVEN;
      #ifdef DEBUG
      Serial.print(F("Eleven"));
      #endif
      break;
    case 0:
    case 12:
    case 24:
      TWELVE;
      #ifdef DEBUG
      Serial.print(F("Twelve"));
      #endif
      break;
  }
  
  #ifdef DEBUG
  switch (iMinute) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
    Serial.print(F(" O'Clock"));
    break;
  }
  
  Serial.println(F(")"));
  #endif

  updateShiftRegister();
  wordsoff();
}

void wordsoff(void) {
  Display[0]=0;
  Display[1]=0;
  Display[2]=0;
}

void setupShiftRegister()
{
  #ifdef DEBUG
    Serial.println(F("setupShiftRegister (Setup Shift Registers)"));
  #endif
  
  //Setup Shift Registers
  pinMode(LEDLACHPIN, OUTPUT);
  pinMode(DATAPIN, OUTPUT);  
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(LEDOUTPUTENABLEPIN, OUTPUT);
}

void updateShiftRegister()
{  
  digitalWrite(LEDLACHPIN, LOW);
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, Display[2]);
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, Display[1]);
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, Display[0]);
  digitalWrite(LEDLACHPIN, HIGH);
}

void setBrightness()
{
  if (hour(local)<=7||hour(local)>=20){
    analogWrite(LEDOUTPUTENABLEPIN, EEPROM.read(15));
  } else {
    analogWrite(LEDOUTPUTENABLEPIN, EEPROM.read(14));
  }
}
