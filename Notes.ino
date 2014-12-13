/*
Logic PCB

Support standard pinout character LCD (dimming and contrast)
Support shift registers w/o "high" curent capability using transistors
Each output gets a +5,signal,GND connector all sitting next to eachother
Have footprint for chronodot over the RTC
have dipswitch/jumper to enable LCD specific menu
  digipot (and opamp?) for contrast?
  transistor for BL enable
  PWM for BL brightness? or digipot and opamp

----------------
write error to display for first 60 seconds if there is no RTC detected

----------------
Setup with no LCD
Color set by time of year/month/holiday

Dimming pot on A3
how to set time ?

Make small instruction sheet for back.

o'Clock is 0 in menu

config in EEPROM 10+
EEPROM 10: Color Palette
EEPROM 11: Red
EEPROM 12: Green
EEPROM 13: Blue
EEPROM 14: Day Brightness
EEPROM 15: Night Brightness


*/
