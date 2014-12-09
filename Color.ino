
void holidayColor() {
  switch (month()) {
    case 1: //Snow & New Years
    //White
    case 2: //Valentines Day
    //Red
    case 3: //St Patrick's Day
    //Green
    case 4: //Easter
    //Yellow & Purple
    case 5: //May
    //Green?
    case 6: //June
    //Yellow?
    case 7: //Independence Day
    //Red, White, Blue
    case 8: // August
    //Red Orange (sunburn color)
    case 9: // Stptember
    //dark red, dark orange, brown
    case 10:
    // Orange
    case 11: //Thanksgiving
    //dark red, dark orange, brown
    case 12://Ghristmas
    //Red & Green
    default:
      break;
  }
}

void birthStoneColor() {
  // http://bit.ly/1vrDKuX
  switch (month()) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    default:
      break;
  }
}

void randomColor() {   
  Wire.beginTransmission(0x09);
  Wire.write('o');
  Wire.write('C');
  Wire.write(0xff);
  Wire.write(0xff);
  Wire.write(0xff);
  Wire.endTransmission();
}
