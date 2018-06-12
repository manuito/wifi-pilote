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
int BUTT_VALID_PIN = 16;
int BUTT_LEFT_PIN = 5;
int BUTT_RIGHT_PIN = 4;

// Screen init
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS_PIN, TFT_DC_PIN, TFT_RST_PIN);

// Wifi params
const char *ssid = "xxxxxx"; // Need to load it from a file in SD Card
const char *password = "xxxxxx"; // Need to load it from a file in SD Card

// Active Wifi IP
IPAddress localIp;

// Active button
int activeButton = 0;

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

  setupScreen();

  setupFiles();
  
  setupWifi();
}

void loop() {

  activeButton = 0;
    
  if (digitalRead(BUTT_RIGHT_PIN) == 1) {
    Serial.println("1!");
    digitalWrite(LED_PIN, HIGH); 
    printButton(1);
    activeButton = 1;
  }
  
  if (digitalRead(BUTT_LEFT_PIN) == 1) {
    Serial.println("2!");
    digitalWrite(LED_PIN, LOW); 
    printButton(2);
    activeButton = 2;
  }
  
  if (digitalRead(BUTT_VALID_PIN) == 1) {
    printButton(3);
    Serial.println("3!");
    activeButton = 3;
  }
  
  loopWifi();
}


