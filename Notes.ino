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

*/
