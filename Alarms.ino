//file to consolidate reoccurring alarms

void alarmHourly(){
  saveDate();
  setBrightness();  //update the brightness
  setColor(); //Update the color
}

void alarm30sec(){
  ledDisplayTime(); //update LED display
  #ifdef DEBUG
  setColor();
  #endif
}

#ifdef DEBUG

void alarm20sec(){
  #ifdef LCD
  digitalClockDisplay(); //update LCD display
  #endif
}

void alarm60sec(){
  #ifdef LCD
  switchLCD(); //change LCD display State
  #endif
}

#endif
