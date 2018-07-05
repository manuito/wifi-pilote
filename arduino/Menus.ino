int curPage = 0;
int curSelection = 0;
bool changed = true;
String miniRobot = "192.168.0.19";

void processPages(){
   switch (curPage) {
    case 0:
      processHomePage();
      break;
    case 1:
      processMenuPage();
      break;
    case 2:
      processInfoPage();
      break;
    case 3:
      processHelpPage();
      break;
    case 4:
      processServerPage();
      break;
    case 5:
      processBigRobotPage();
      break;
    case 6:
      processSmallRobotPage();
      break;
    case 7:
      processConfigPage();
      break;
    case 8:
      processBigRobotMenuPage();
      break;
    case 9:
      processSmallRobotMenuPage();
      break;
  }
}

void goToPage(int num){
  changed = true;
  curPage = num;
}

// For each page : one process / one display

// PAGE 0 : home
void processHomePage(){
  if(changed){
    displayHomePage();
    changed = false;
    delay(30);
  } else { 
    if(butMenuActive){
      goToPage(1); // Menu
    } else if(butLeftActive){
      goToPage(2); // Info
    }else if(butRightActive){
      goToPage(3); // Help
    }
  }
}

void displayHomePage(){
  printHeader("          PILOTE");
  printLine(2, "Welcome to wifi pilote");
  printLine(3, "#########################");
  printBottom("menu             info   ?");
}

// PAGE 1 : MENU
void processMenuPage(){
  if(changed){
    curSelection = 0;
    displayMenuPage();
    changed = false;
    delay(30);
  } else {
    if(butMenuActive){
      goToPage(0); // Home
    } else if(butLeftActive){
      if(curSelection < 4){
        goToPage(4 + curSelection);
      } else {
        goToPage(6 + curSelection);        
      }
    }else if(butRightActive){
      if(curSelection >= 5){
        curSelection = 0;
      } else {
        curSelection++;
      }
      displayMenuSelect();
      delay(200);
    }
  }
}

void displayMenuPage(){
  printHeader("           MENU");
  displayMenuSelect();
  printBottom("home             sel next");
}

void displayMenuSelect(){
  if(curSelection == 0 || curSelection == 1){ printSelectLine(2, "1. Enable Wifi server", curSelection == 0);}
  if(curSelection == 0 || curSelection == 1 || curSelection == 2){ printSelectLine(3, "2. Pilote big robot", curSelection == 1);}
  if(curSelection == 0 || curSelection == 2 || curSelection == 3){ printSelectLine(4, "3. Pilote little robot", curSelection == 2);}
  if(curSelection == 0 || curSelection == 3 || curSelection == 4){ printSelectLine(5, "4. System config", curSelection == 3);}
  if(curSelection == 0 || curSelection == 4 || curSelection == 5){ printSelectLine(6, "5. Navigate files", curSelection == 4);}
  if(curSelection == 5 || curSelection == 0){ printSelectLine(7, "6. Extensions", curSelection == 5);}
}


// PAGE 2 : INFO
void processInfoPage(){
  if(changed){
    displayInfoPage();
    changed = false;
    delay(30);
  } else { 
    if(butMenuActive){
      goToPage(0); // Home
    }
  }
}

void displayInfoPage(){
  printHeader("           INFO");
  printLine(2, "Wifi is ON.");
  printLine(3, "IP Address :", localIp.toString());
  printLine(4, "Pilote Version 1.0.0");
  
  printBottom("home");
}


// PAGE 3 : HELP
void processHelpPage(){
  if(changed){
    displayHelpPage();
    changed = false;
    delay(30);
  } else {
    if(butMenuActive){
      goToPage(0); // Home
    }
  }
}

void displayHelpPage(){
  printHeader("           HELP");
  printLine(2, "De l'aide !!!");
  printLine(3, "Ceci est une page d'aide");
  printLine(4, "Blablabla blabla blabla");
  printLine(5, "Bla blabla blablabla");
  
  printBottom("home");
}


// PAGE 4 : WIFI SERVER
void processServerPage(){
  if(changed){
    displayServerPage();
    changed = false;
    delay(30);
  } else {
    if(butMenuActive){
      goToPage(0); // Home
    }
  }
}

void displayServerPage(){
  printHeader("        WIFI SERVER");
  printLine(2, "Go to http://", localIp.toString(), "/");
  
  printBottom("home");
}


// PAGE 5 : BIG ROBOT
void processBigRobotPage(){
  if(changed){
    displayBigRobotPage();
    changed = false;
    delay(30);
  } else {
    if(butLeftActive && butRightActive){
      goToPage(8); // BigRobotMenu
    } else {
      if(butMenuActive){
        Serial.println("GO");
      } else if(butLeftActive){
        Serial.println("LEFT");
      } else if(butRightActive){
        Serial.println("RIGHT");
      }
    }
  }
}

void displayBigRobotPage(){
  printHeader("         BIG ROBOT");
  printLine(2, "Press <- and -> for menu");
  printLine(4, "Running ...");
  
  printBottom(" GO               <-   ->");
}

// PAGE 6 : SMALL ROBOT
void processSmallRobotPage(){
  if(changed){
    displaySmallRobotPage();
    changed = false;
    delay(30);
  } else {
    if(butLeftActive && butRightActive){
      callClient(miniRobot, "G=0");
      goToPage(9); // SmallRobotMenu
    } else {
      if(butMenuActive){
        callClient(miniRobot, "G=1");
      } else if(prevButMenuActive) {
        callClient(miniRobot, "G=0");
      }
      
      if(butLeftActive){
        callClient(miniRobot, "TL=1");
      } else if(prevButLeftActive) {
        callClient(miniRobot, "TL=0");
      }
      
      if(butRightActive){
        callClient(miniRobot, "TR=1");
      } else if(prevButRightActive) {
        callClient(miniRobot, "TR=0");
      }
    }
  }
}

void displaySmallRobotPage(){
  printHeader("         BIG ROBOT");
  printLine(2, "Press <- and -> for menu");
  printLine(4, "Running ...");
  
  printBottom(" GO               <-   ->");
}


// PAGE 7 : CONFIG
void processConfigPage(){
  if(changed){
    displayConfigPage();
    changed = false;
    delay(30);
  } else {
    if(butMenuActive){
      goToPage(0); // Home
    }
  }
}

void displayConfigPage(){
  printHeader("       CONFIGURATION");
  printLine(2, "Nothing ...");
  
  printBottom("home");
}


// PAGE 8 : BIG ROBOT MENU
void processBigRobotMenuPage(){
  if(changed){
    curSelection = 0;
    displayBigRobotMenuPage();
    changed = false;
    delay(30);
  } else {
    if(butMenuActive){
      goToPage(5); // BigRobot pilote
    } else if(butLeftActive){
      if(curSelection == 6){
        goToPage(0); // Home
      }
      Serial.print("Action ");
      Serial.println(curSelection);
    }else if(butRightActive){
      if(curSelection == 6){
        curSelection = 0;
      } else {
        curSelection++;
      }
      displayBigRobotMenuSelect();
      delay(200);
    }
  }
}

void displayBigRobotMenuPage(){
  printHeader("         BIG ROBOT");
  displayBigRobotMenuSelect();
  printBottom("pilote           sel next");
}

void displayBigRobotMenuSelect(){
  if(curSelection == 0 || curSelection == 1){ printSelectLine(2, "1. Honk", curSelection == 0);}
  if(curSelection == 0 || curSelection == 1 || curSelection == 2){ printSelectLine(3, "2. Light 1", curSelection == 1);}
  if(curSelection == 0 || curSelection == 2 || curSelection == 3){ printSelectLine(4, "3. Light 2", curSelection == 2);}
  if(curSelection == 0 || curSelection == 3 || curSelection == 4){ printSelectLine(5, "4. Face 1", curSelection == 3);}
  if(curSelection == 0 || curSelection == 4 || curSelection == 5){ printSelectLine(6, "5. Face 2", curSelection == 4);}
  if(curSelection == 0 || curSelection == 5 || curSelection == 6){ printSelectLine(7, "6. Robot Settings", curSelection == 5);}
  if(curSelection == 6 || curSelection == 0){ printSelectLine(8, "7. Quit", curSelection == 6);}
}


// PAGE 9 : SMALL ROBOT MENU
void processSmallRobotMenuPage(){
  if(changed){
    curSelection = 0;
    displaySmallRobotMenuPage();
    changed = false;
    delay(30);
  } else {
    if(butMenuActive){
      goToPage(6); // SmallRobot pilote
    } else if(butLeftActive){
      switch (curSelection) {
        case 0:
          callClient(miniRobot,"L=0");
          break;
        case 1:
          callClient(miniRobot,"L=1");
          break;
        case 2:
          callClient(miniRobot,"L=2");
          break;
        case 3:
          callClient(miniRobot,"L=3");
          break;
        case 4:
          callClient(miniRobot,"L=4");
          break;
        case 5:
          callClient(miniRobot,"L=5");
          break;
        case 6:
          callClient(miniRobot, "B=1");
          delay(2000);
          callClient(miniRobot, "B=0");
          break;
        case 7:
          callClient(miniRobot, "BR=1");
          break;
        case 8:
          goToPage(0); // Home
          break;
        default:
          break;
      }
      Serial.print("Action ");
      Serial.println(curSelection);
    }else if(butRightActive){
      if(curSelection == 8){
        curSelection = 0;
      } else {
        curSelection++;
      }
      displaySmallRobotMenuSelect();
      delay(200);
    }
  }
}

void displaySmallRobotMenuPage(){
  printHeader("        SMALL ROBOT");
  displaySmallRobotMenuSelect();
  printBottom("pilote           sel next");
}

void displaySmallRobotMenuSelect(){
  if(curSelection == 0 || curSelection == 1){ printSelectLine(2, "1. Stop Lights", curSelection == 0);}
  if(curSelection == 0 || curSelection == 1 || curSelection == 2){ printSelectLine(3, "2. Light 1 (Police)", curSelection == 1);}
  if(curSelection == 0 || curSelection == 2 || curSelection == 3){ printSelectLine(4, "3. Light 2 (K2000)", curSelection == 2);}
  if(curSelection == 0 || curSelection == 3 || curSelection == 4){ printSelectLine(5, "4. Light 3 (Headlight)", curSelection == 3);}
  if(curSelection == 0 || curSelection == 4 || curSelection == 5){ printSelectLine(6, "5. Light 4 (Christmas)", curSelection == 4);}
  if(curSelection == 0 || curSelection == 5 || curSelection == 6){ printSelectLine(7, "6. Light 5 (Fadding yellow)", curSelection == 5);}
  if(curSelection == 0 || curSelection == 6 || curSelection == 7){ printSelectLine(8, "7. Go back 2 seconds", curSelection == 6);}
  if(curSelection == 0 || curSelection == 7 || curSelection == 8){ printSelectLine(9, "8. Do a Barrel Roll", curSelection == 7);}
  if(curSelection == 8 || curSelection == 0){ printSelectLine(10, "9. Quit", curSelection == 8);}
}
