int nextLight = 1;
boolean drive = false;
int curSelection = 0;
bool changed = true;
bool doubleCheck = false;
String miniRobot = "192.168.0.19";

String appendS(String n, int value){
  n.concat(value);
  return n;
}

String robotNextLightName(){
  return appendS("light ", nextLight);
}

String robotNextActionName(){
  return "Barrel R";
}

void robotDoNothing(){
   if(drive) {
      callClient(miniRobot, "G=0");
   }
   drive = false;
   doubleCheck = true;
}

void robotDrive(){
   callClient(miniRobot, "G=1");
   drive = true;
   doubleCheck = true;
}

void robotBack(){
   callClient(miniRobot, "B=1");
   drive = true;
   doubleCheck = true;
}

void robotLeft(){
   callClient(miniRobot, "TL=1");
   drive = true;
   doubleCheck = true;
}

void robotRight(){
   callClient(miniRobot, "TR=1");
   drive = true;
   doubleCheck = true;
}

void robotLight(){

  if(doubleCheck){
    callClient(miniRobot,appendS("L=",nextLight));
    nextLight++;
    if(nextLight >= 6){
      nextLight = 0;
    }
    delay(250);
    doubleCheck = false;
  }
}

void robotAction(){
  callClient(miniRobot,"BR=1");
}

