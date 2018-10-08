int curFaceEyes;
int curFaceMouth;
int faceCount;

void nextFace(){

  if(faceCount == 5){
    curFaceEyes = 0;
    faceCount = 0;
  } 
  
  else {
    
    if(curFaceEyes >= 4){
      curFaceEyes = 1;
    } else {
      curFaceEyes++;
    }
  
    if(curFaceMouth >= 2){
      curFaceMouth = 0;
    } else {
      curFaceMouth++;
    }
    faceCount++;
  }
}

void setupOledDisplay()   {  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)  
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
  delay(500);
  drawBackground();
  Serial.println("Screen started");
}

void drawUpArrow() {
  display.fillTriangle(24, 10, 31, 3, 38,10, WHITE);
  display.fillRect(28, 11, 7, 6, WHITE);
  display.display();
  delay(1);
}

void drawDownArrow() {
  display.fillTriangle(24, 9, 31, 15, 38, 9, WHITE);
  display.fillRect(28, 3, 7, 6, WHITE);
  display.display();
  delay(1);
}

void drawRightArrow() {
  display.fillTriangle(32, 3, 39, 10, 32, 16, WHITE);
  display.fillRect(26, 7, 6, 7, WHITE);
  display.display();
  delay(1);
}

void drawLeftArrow() {
  display.fillTriangle(22, 10, 29, 3, 29, 17, WHITE);
  display.fillRect(30, 7, 6, 7, WHITE);
  display.display();
  delay(1);
}

void drawBackground(){
  display.drawPixel(28,33,WHITE);
  display.drawPixel(29,33,WHITE);
  display.drawPixel(30,33,WHITE);
  display.drawPixel(36,33,WHITE);
  display.drawPixel(37,33,WHITE);
  display.drawPixel(38,33,WHITE);
  display.drawPixel(29,34,WHITE);
  display.drawPixel(37,34,WHITE);
  display.drawPixel(29,35,WHITE);
  display.drawPixel(37,35,WHITE);
  display.drawPixel(56,35,WHITE);
  display.drawPixel(62,35,WHITE);
  display.drawPixel(27,36,WHITE);
  display.drawPixel(28,36,WHITE);
  display.drawPixel(29,36,WHITE);
  display.drawPixel(30,36,WHITE);
  display.drawPixel(31,36,WHITE);
  display.drawPixel(32,36,WHITE);
  display.drawPixel(33,36,WHITE);
  display.drawPixel(34,36,WHITE);
  display.drawPixel(35,36,WHITE);
  display.drawPixel(36,36,WHITE);
  display.drawPixel(37,36,WHITE);
  display.drawPixel(38,36,WHITE);
  display.drawPixel(39,36,WHITE);
  display.drawPixel(51,36,WHITE);
  display.drawPixel(53,36,WHITE);
  display.drawPixel(58,36,WHITE);
  display.drawPixel(59,36,WHITE);
  display.drawPixel(26,37,WHITE);
  display.drawPixel(40,37,WHITE);
  display.drawPixel(50,37,WHITE);
  display.drawPixel(52,37,WHITE);
  display.drawPixel(54,37,WHITE);
  display.drawPixel(56,37,WHITE);
  display.drawPixel(58,37,WHITE);
  display.drawPixel(60,37,WHITE);
  display.drawPixel(62,37,WHITE);
  display.drawPixel(25,38,WHITE);
  display.drawPixel(41,38,WHITE);
  display.drawPixel(50,38,WHITE);
  display.drawPixel(54,38,WHITE);
  display.drawPixel(56,38,WHITE);
  display.drawPixel(58,38,WHITE);
  display.drawPixel(60,38,WHITE);
  display.drawPixel(62,38,WHITE);
  display.drawPixel(25,39,WHITE);
  display.drawPixel(41,39,WHITE);
  display.drawPixel(0,40,WHITE);
  display.drawPixel(1,40,WHITE);
  display.drawPixel(2,40,WHITE);
  display.drawPixel(3,40,WHITE);
  display.drawPixel(4,40,WHITE);
  display.drawPixel(5,40,WHITE);
  display.drawPixel(6,40,WHITE);
  display.drawPixel(7,40,WHITE);
  display.drawPixel(8,40,WHITE);
  display.drawPixel(9,40,WHITE);
  display.drawPixel(10,40,WHITE);
  display.drawPixel(11,40,WHITE);
  display.drawPixel(12,40,WHITE);
  display.drawPixel(13,40,WHITE);
  display.drawPixel(14,40,WHITE);
  display.drawPixel(15,40,WHITE);
  display.drawPixel(16,40,WHITE);
  display.drawPixel(17,40,WHITE);
  display.drawPixel(18,40,WHITE);
  display.drawPixel(19,40,WHITE);
  display.drawPixel(20,40,WHITE);
  display.drawPixel(21,40,WHITE);
  display.drawPixel(22,40,WHITE);
  display.drawPixel(23,40,WHITE);
  display.drawPixel(25,40,WHITE);
  display.drawPixel(41,40,WHITE);
  display.drawPixel(43,40,WHITE);
  display.drawPixel(44,40,WHITE);
  display.drawPixel(45,40,WHITE);
  display.drawPixel(46,40,WHITE);
  display.drawPixel(47,40,WHITE);
  display.drawPixel(48,40,WHITE);
  display.drawPixel(49,40,WHITE);
  display.drawPixel(50,40,WHITE);
  display.drawPixel(51,40,WHITE);
  display.drawPixel(52,40,WHITE);
  display.drawPixel(53,40,WHITE);
  display.drawPixel(54,40,WHITE);
  display.drawPixel(55,40,WHITE);
  display.drawPixel(56,40,WHITE);
  display.drawPixel(57,40,WHITE);
  display.drawPixel(58,40,WHITE);
  display.drawPixel(59,40,WHITE);
  display.drawPixel(60,40,WHITE);
  display.drawPixel(61,40,WHITE);
  display.drawPixel(62,40,WHITE);
  display.drawPixel(63,40,WHITE);
  display.drawPixel(25,41,WHITE);
  display.drawPixel(41,41,WHITE);
  display.drawPixel(26,42,WHITE);
  display.drawPixel(27,42,WHITE);
  display.drawPixel(39,42,WHITE);
  display.drawPixel(40,42,WHITE);
  display.drawPixel(45,42,WHITE);
  display.drawPixel(46,42,WHITE);
  display.drawPixel(50,42,WHITE);
  display.drawPixel(53,42,WHITE);
  display.drawPixel(54,42,WHITE);
  display.drawPixel(58,42,WHITE);
  display.drawPixel(61,42,WHITE);
  display.drawPixel(62,42,WHITE);
  display.drawPixel(63,42,WHITE);
  display.drawPixel(27,43,WHITE);
  display.drawPixel(28,43,WHITE);
  display.drawPixel(29,43,WHITE);
  display.drawPixel(30,43,WHITE);
  display.drawPixel(31,43,WHITE);
  display.drawPixel(32,43,WHITE);
  display.drawPixel(33,43,WHITE);
  display.drawPixel(34,43,WHITE);
  display.drawPixel(35,43,WHITE);
  display.drawPixel(36,43,WHITE);
  display.drawPixel(37,43,WHITE);
  display.drawPixel(38,43,WHITE);
  display.drawPixel(39,43,WHITE);
  display.drawPixel(45,43,WHITE);
  display.drawPixel(47,43,WHITE);
  display.drawPixel(49,43,WHITE);
  display.drawPixel(51,43,WHITE);
  display.drawPixel(53,43,WHITE);
  display.drawPixel(55,43,WHITE);
  display.drawPixel(57,43,WHITE);
  display.drawPixel(59,43,WHITE);
  display.drawPixel(62,43,WHITE);
  display.drawPixel(45,44,WHITE);
  display.drawPixel(46,44,WHITE);
  display.drawPixel(49,44,WHITE);
  display.drawPixel(51,44,WHITE);
  display.drawPixel(53,44,WHITE);
  display.drawPixel(54,44,WHITE);
  display.drawPixel(57,44,WHITE);
  display.drawPixel(59,44,WHITE);
  display.drawPixel(62,44,WHITE);
  display.drawPixel(45,45,WHITE);
  display.drawPixel(47,45,WHITE);
  display.drawPixel(49,45,WHITE);
  display.drawPixel(51,45,WHITE);
  display.drawPixel(53,45,WHITE);
  display.drawPixel(55,45,WHITE);
  display.drawPixel(57,45,WHITE);
  display.drawPixel(59,45,WHITE);
  display.drawPixel(62,45,WHITE);
  display.drawPixel(45,46,WHITE);
  display.drawPixel(47,46,WHITE);
  display.drawPixel(50,46,WHITE);
  display.drawPixel(53,46,WHITE);
  display.drawPixel(54,46,WHITE);
  display.drawPixel(58,46,WHITE);
  display.drawPixel(62,46,WHITE);
  display.display();
  delay(1);
}

void prepareDisplay() {
  display.clearDisplay();
  displayFace(curFaceEyes, curFaceMouth);
  drawBackground();
}


void displayValue(String val) {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(val);
    display.display();
    delay(1);
    
    Serial.print("Displayed : ");
    Serial.println(val);
}

void displayFace(int eyes, int mouth){

  if(eyes == 0){
    // Eyes closed
    display.drawPixel(28,39,WHITE);
    display.drawPixel(29,39,WHITE);
    display.drawPixel(30,39,WHITE);
    display.drawPixel(31,39,WHITE);
    display.drawPixel(32,39,WHITE);
    display.drawPixel(34,39,WHITE);
    display.drawPixel(35,39,WHITE);
    display.drawPixel(36,39,WHITE);
    display.drawPixel(37,39,WHITE);
    display.drawPixel(38,39,WHITE);
    display.drawPixel(32,40,WHITE);
    display.drawPixel(38,40,WHITE);
  } else {  
    // Eyes Open
    display.drawPixel(29,38,WHITE);
    display.drawPixel(30,38,WHITE);
    display.drawPixel(31,38,WHITE);
    display.drawPixel(35,38,WHITE);
    display.drawPixel(36,38,WHITE);
    display.drawPixel(37,38,WHITE);
    display.drawPixel(28,39,WHITE);
    display.drawPixel(32,39,WHITE);
    display.drawPixel(34,39,WHITE);
    display.drawPixel(38,39,WHITE);
    display.drawPixel(28,40,WHITE);
    display.drawPixel(32,40,WHITE);
    display.drawPixel(34,40,WHITE);
    display.drawPixel(38,40,WHITE);
    display.drawPixel(29,41,WHITE);
    display.drawPixel(30,41,WHITE);
    display.drawPixel(31,41,WHITE);
    display.drawPixel(35,41,WHITE);
    display.drawPixel(36,41,WHITE);
    display.drawPixel(37,41,WHITE);
    if(eyes == 1){
      // Eyes top
      display.drawPixel(30,39,WHITE); //
      display.drawPixel(36,39,WHITE); // 
    } else if (eyes == 2){
      // Eyes right
      display.drawPixel(31,40,WHITE); // 
      display.drawPixel(37,40,WHITE); //
    } else if (eyes == 3) {
      // Eyes left
      display.drawPixel(29,40,WHITE); // 
      display.drawPixel(35,40,WHITE); //
    } else {
      // Pupils bottom
      display.drawPixel(30,40,WHITE); // 
      display.drawPixel(36,40,WHITE); //
    }
  }

  if(mouth == 0) {
    // Mouth closed
    display.drawPixel(31,44,WHITE);
    display.drawPixel(32,44,WHITE);
    display.drawPixel(33,44,WHITE);
    display.drawPixel(34,44,WHITE);
    display.drawPixel(35,44,WHITE);

  } else if(mouth == 1){
    // Middle mouth
    display.drawPixel(31,44,WHITE);
    display.drawPixel(35,44,WHITE);
    display.drawPixel(32,45,WHITE);
    display.drawPixel(33,45,WHITE);
    display.drawPixel(34,45,WHITE);
  } else {    
    // Mouth big
    display.drawPixel(30,44,WHITE);
    display.drawPixel(31,44,WHITE);
    display.drawPixel(35,44,WHITE);
    display.drawPixel(36,44,WHITE);
    display.drawPixel(32,45,WHITE);
    display.drawPixel(33,45,WHITE);
    display.drawPixel(34,45,WHITE);
  }
}

