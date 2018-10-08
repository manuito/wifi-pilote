
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

// Various delay
#define ACTION_DELAY       500

// And loop control
long actionMillis = 0;
long nextActionMillis = 0;

const char *ssid = "xxxxx";
const char *password = "xxxxx";

ESP8266WebServer server(80);

// Buttons
bool butUpActive = false ;
bool butLeftActive = false ;
bool butRightActive = false ;
bool butDownActive = false ;
bool butBlueActive = false ;
bool butRedActive = false ;
bool butGreenActive = false ;
bool butYellowActive = false ;

void setup(void) {
  Wire.begin();
  setupOledDisplay();
  Serial.begin(115200);
  startWifi();
  startServer();
  nextActionMillis = millis() + ACTION_DELAY;
}

void loop(void) {
  
  server.handleClient();
  handleButtons();
  showButton();
  
  if(millis() >= nextActionMillis){
    nextActionMillis = millis() + ACTION_DELAY;
    nextFace();
  }
}


