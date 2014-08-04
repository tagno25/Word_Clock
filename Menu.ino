boolean buttonsPressed(byte button){
  
  //check if "button" is pressed from analog read value
  // if it is return true, else return false
  byte PressedButton = bitwiseButtonsPressed(button);
  byte CheckedButton = B0000000;
  
  //set CheckedButton based upon button
  switch (button){
    case 1:
      CheckedButton = B0000001;
      break;
    case 2:
      CheckedButton = B0000010;
      break;
    case 3:
      CheckedButton = B0000100;    
  }

  //do a bitwise AND between CheckedButton and PressedButton
  //then return true for what you are checking
  switch (CheckedButton & PressedButton){
    case B0000001:
      return(true);
      break;
    case B0000010:
      return(true);
      break;
    case B0000100:
      return(true);
      break;
    default:
      return(false);
  }
}

byte bitwiseButtonsPressed(byte button){
  
  //return buttons that are pressed with bitwise OR 
  //B0000001=Button1(set/next)
  //B0000010=Button2(increment)
  //B0000100=Button3(decrement)
  byte pressed=0;
  if (BUTTON1 == HIGH){
    pressed=pressed | (1<<0);
  }
  if (BUTTON2 == HIGH){
    pressed=pressed | (1<<1);
  }
  if (BUTTON3 == HIGH){
    pressed=pressed | (1<<2);
  }
  return(pressed);
}

