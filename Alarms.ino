//file to consolidate reoccurring alarms

void alarmHourly(){
  saveDate();
}

void alarm30sec(){
  ledDisplayTime(); //update LED display
}

#ifdef DEBUG

void alarm20sec(){
  digitalClockDisplay(); //update LCD display
}

void alarm60sec(){
  switchLCD(); //change LCD display State
}

#endif
