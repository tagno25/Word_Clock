#ifdef DEBUG
void digitalClockDisplay(){
  if (timeStatus() == timeSet) {
    // digital clock display of the time
  
    utc = now();
    local = myTZ.toLocal(utc, &tcr);
  
    Serial.print(tcr -> abbrev);
    Serial.print(": ");
    Serial.print(hour(local));
    printDigits(minute(local));
    printDigits(second(local));
    Serial.print(" ");
    Serial.print(day(local));
    Serial.print("/");
    Serial.print(month(local));
    Serial.print("/");
    Serial.print(year(local)); 
    Serial.println(); 
   } else {
    Serial.println(F("The time has not been set.  Please run the Time"));
    Serial.println(F("TimeRTCSet example, or DS1307RTC SetTime example."));
    Serial.println();
    delay(4000);
  }
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

String pretDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  if(digits < 10)
    return String('0'+digits);
  return String(digits);
}
#endif

