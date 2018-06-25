// For screen
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

// For Wifi
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// SPI used for screen connect
#include <SPI.h>

// SD Cart
#include <SD.h>

// Screen PINS
#define TFT_CS_PIN  15  // Chip select line for TFT display
#define TFT_RST_PIN  -1  // you can also connect this to the Arduino reset!
#define TFT_DC_PIN   0  // Data/command line for TFT

// SD Card PINS
#define SD_CS_PIN    2  // Chip select line for SD card

// LED PINS
int LED_PIN = 10;

// BUTTON PINS
int BUTT_VALID_PIN = 4;
int BUTT_LEFT_PIN = 5;
int BUTT_RIGHT_PIN = 16;

// Screen init
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS_PIN, TFT_DC_PIN, TFT_RST_PIN);

// Wifi params
const char *ssid = "XXXXX";
const char *password = "xxxxx";

// Active Wifi IP
IPAddress localIp;

// States for the 3 buttons
bool butMenuActive = false;
bool butLeftActive = false;
bool butRightActive = false;

void setup(void) {
  Serial.begin(9600);

  while (!Serial) {
    delay(10);  // wait for serial console
  }  
 
  pinMode(LED_PIN, OUTPUT);
  
  pinMode(BUTT_VALID_PIN, INPUT);  
  pinMode(BUTT_LEFT_PIN, INPUT);  
  pinMode(BUTT_RIGHT_PIN, INPUT);  
  
  pinMode(TFT_CS_PIN, OUTPUT);
  digitalWrite(TFT_CS_PIN, HIGH);
  delay(10);
  
  pinMode(SD_CS_PIN, OUTPUT);
  digitalWrite(SD_CS_PIN, HIGH);
  delay(10);

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);
  
  setupFiles();
  setupWifi();
  setupScreen();
}

void loop() {
  controlButtons();
  loopWifi();
  processPages();
}

void controlButtons(){ 
  if (digitalRead(BUTT_RIGHT_PIN) == 1) {
    Serial.println("1!");
    butRightActive = true;
  } else {
    butRightActive = false;
  }
  
  if (digitalRead(BUTT_LEFT_PIN) == 1) {
    Serial.println("2!");
    butLeftActive = true;
  } else {
    butLeftActive = false;
  }
  
  if (digitalRead(BUTT_VALID_PIN) == 1) {
    Serial.println("3!");
    butMenuActive = true;
  } else {
    butMenuActive = false;
  }
}
