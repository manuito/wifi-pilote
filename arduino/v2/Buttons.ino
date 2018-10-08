
void handleButtons(){
  Wire.requestFrom(0x10, 1);
  char val = Wire.read();
  butUpActive = bitRead(val,1) == 1;
  butLeftActive = bitRead(val,3) == 1;
  butRightActive = bitRead(val,2) == 1;
  butDownActive = bitRead(val,0) == 1;
  butBlueActive = bitRead(val,5) == 1;
  butRedActive = bitRead(val,4) == 1;
  butGreenActive = bitRead(val,6) == 1;
  butYellowActive = bitRead(val,7) == 1;
}

void showButton(){
  if(butUpActive) { drawUpArrow(); robotDrive(); }
  else if(butLeftActive) { drawLeftArrow(); robotLeft(); }
  else if(butRightActive) { drawRightArrow(); robotRight(); }
  else if(butDownActive) { drawDownArrow();  robotBack(); }
  else if(butBlueActive) { 
    displayValue(robotNextLightName()); 
    robotLight(); 
  }
  else if(butRedActive) { 
    displayValue(robotNextActionName());  
    robotAction();
  }
  else if(butGreenActive) { displayValue("green"); }
  else if(butYellowActive) { displayValue("yellow"); }
  else { prepareDisplay(); robotDoNothing(); }
}

