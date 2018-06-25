#define BUFFPIXEL 20

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

void setupScreen(){
  tft.fillScreen(ST77XX_RED);
  delay(100);
  tft.fillScreen(ST77XX_BLUE);
  delay(100);
  tft.setRotation(1);
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
}

void bmpDraw(char *filename, uint8_t x, uint16_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print(F("File not found"));
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.print(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.color565(r,g,b));
          } // end pixel
        } // end scanline
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}

void eraseLine(int lineNum){
  tft.fillRect(0, (lineNum * 10) + 2, SCREEN_WIDTH, 10, ST77XX_BLACK);
}

void printHr(int lineNum){
  eraseLine(lineNum);
  tft.drawLine(0, (lineNum * 10) + 6, SCREEN_WIDTH, (lineNum * 10) + 6, ST77XX_WHITE);
}

void printHeader(String text){
  tft.fillRect(0, 0, SCREEN_WIDTH, 13, ST77XX_WHITE);
  tft.setCursor(3, 3);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.println(text);
  // Erase also page
  tft.fillRect(0, 14, SCREEN_WIDTH, 120, ST77XX_BLACK);
}

void printBottom(String text){
  tft.fillRect(0, 114, SCREEN_WIDTH, 128, ST77XX_BLACK);
  tft.drawLine(0, 114, SCREEN_WIDTH, 114, ST77XX_WHITE);
  tft.setCursor(8, 117);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.println(text);
}

void printSelectLine(int lineNum, String text, bool select){
  if(select){
    int pos = lineNum * 10;
    tft.fillRect(0, pos + 2, SCREEN_WIDTH, 10, ST77XX_YELLOW);
    tft.setCursor(3, pos + 3);
    tft.setTextColor(ST77XX_BLACK);
    tft.setTextSize(1);
    tft.println(text);
  } else {
    printLine(lineNum, text);
  }
}

void printLine(int lineNum, String text){
  eraseLine(lineNum);
  tft.setCursor(3, (lineNum * 10) + 3);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.println(text);
}

void printLine(int lineNum, String text, String otherText){
  String line = text;
  line.concat(otherText);
  printLine(lineNum, line);
}

void printLine(int lineNum, String text, String otherText, String otherOtherText){
  String line = text;
  line.concat(otherText);
  line.concat(otherOtherText);
  printLine(lineNum, line);
}

void printLine(int lineNum, String text, String otherText, String otherOtherText, String otherOtherOtherText){
  String line = text;
  line.concat(otherText);
  line.concat(otherOtherText);
  line.concat(otherOtherOtherText);
  printLine(lineNum, line);
}
