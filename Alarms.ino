//file to consolidate reoccurring alarms

void alarmHourly(){
  saveDate();
}

void alarm30sec(){
  ledDisplayTime(); //update LED display
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
