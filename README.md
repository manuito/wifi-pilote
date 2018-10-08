# WIFI-PILOTE - a wifi remote for managing various devices

This is a source repository for a basic ESP8266 based "remote" programmed for managing various Wifi compliant devices.

Here the things I can do with this remote :
* Driving my first arduino / raspberry based Robot, "robot-large" (WIP)
* Driving my first IoT appliances (TODO)
* Driving other robots (TODO)
* ????

I have created, for now, two versions of the remote, and will create others : 

* v1 : NodeMCU, big TFT screen, custom board, AA batteries
* v2 : D1 Mini Lite, small Wemos D1 Mini OLED Screen, using tindi / standard boards, Lipo battery, home made box
* (not yet done) v3 : Probably with a custom made PCB, ESP8266, Oled screen. 

On this project you will find details on the building process and code for each revisions

# Revision 1

## The device

The remote is based on **NodeMCU** (ESP8266). A very good NodeMCU clone is the one from RobotDyn (see). 

Associated to this NodeMCU, there is :
* A 1.33" SPI TFT screen + SD Card from Adafruit (see). A very very good module, but a bit expensive. Further versions of the remote will use cheaper chinese screens
* A Pololu 5V regulator (see). Once again a very good module, which can be replaced by any chinese built DC-DC up/down regulator. This one is able to handle any DC from 3V to 9V to produce a stable 5V. Works well with 3 AA NiCd or standard batteries, where voltage can go from 1.5V (new non rechargeable battery), 1.2V (fully charged NiCd) to less than 0.9V (Empty NiCd). You **must** put a regulator as the NodeMCU one is not able to manage so much diversity. But you can use a 3.3V regulator (use 3.3V PIN in NodeMCU) instead of 5V (with VIN from NodeMCU)
* 3 buttons, 1 Led, Wires, a battery holder (for 3xAA)

The idea is to build a device with a size adapted to children, with long battery life

### First prototype

I started with a "proto board only" prototype. The NodeMCU is **soldered** to the proto PCB, but the screen module and the regulator are not. I tested various design, and came with this final result. Not so beautifull, and with some mistakes (was expecting to put the buttons not agains the screen) but it works.

![Top view](docs/proto_1_top.png?raw=true "Top view")

I added a groove connector linked to UART (TX0 / RX0 + 5V/GND), as I though it would be a way to add "extensions" to the device. I need to try it (for example with a Serial Camera, but it needs also a level shifter)

The LED is not working (soldering error I guess) but everything else is OK. It was complicated to have everything working as the NodeMCU doesn't have a lot of available GPIO and here you have to handle : 
* SPI connection for Screen : SPI MISO / CS / CK + 1 A/D. Screen backlight is on 3.3V input so it cannot be powered off.
* SPI connection for SD Card : SPI MOSI + 1 software CS
* 3 Buttons (3 INPUTS). NodeMCU needs to add pull up resistors (so I added 3 10k resistors, but I suppose I could optimize this)
* 1 LED. No more available "Dx" io, so I used SDD3. Worked on breadboard (but ligth also a NodeMCU internal led)
* UART for extension

This prototype has the exact base size of the battery holder (45mm x 58mm) and total height with batteries in place is 43mm. 

Not well integrated ... It's a prototype :-)

![Side view 1](docs/proto_1_hand.png?raw=true "Side view 1")

Yes it works ...

![Side view 2](docs/proto_1_side.png?raw=true "Side view 2")


Battery life seems to be around 8h with fully charged NiCd batteries. Wifi and screen are always ON. Their is not ON/OFF button : need to remove batteries to stop it.

USB port is available (but the batteries must be removed first !!!) for programming / debugging.

### Second prototype

TODO. I want to put this time everything inside a box, and use a LiPo battery with charger. I will try to build it from a Wemos D1 mini this time, by using I2C connections for most of the features, and make it smaller. 

Screen and Wifi will not be always ON anymore for better battery life.

### Third prototype

TODO. Maybe I will try to build one with ESP32 instead of ESP8266. So with many more features as the ESP32 is much morre powerfull and add BLE support !

## The code (WIP)

I'm not a big fan of NodeMCU LUA, so I use only arduino programming. It's very easy to make NodeMCU available in Arduino (and as the RobotDyn NodeMCU is using a CP2102 for USB/UART connection, their is no need for a crappy driver like with CH340).

The program must be able to manage :
* 3 button states. Pressing multiple buttons in same time must be managed to
* Screen (using Adafruit gfx library). I will use a basic menu-style rendering of active features
* SD card (works with standard SD library) for ready some config files and whatever files I think it can be funny to manage
* State LED (Not working on prototype #1)
* Wifi connection
* Web server for internal states
* And the most important : a Web client to control other devices / robots

All features are splited in dedicated files. I use very basic arduino code style for now, but I will improve that later, as it is possible to build more advanced code with ESP8266 than with classical arduino AtMega MCUs. 

### Menus

Features are organized in menus. It's interesting to build an UX with a very low level plateform like a MCU when you are used to build webpages or rich client applications using OS / VM based frameworks. Here you have nothing, and you have to think on how to manage "common features" versus "specific features".

In screen functions I have added so basic routines to add a line of text, a page header or to display the meaning of the buttons. 

Here the navigation in menu pages with first proto (all items are working : the small robot can be controled with the remote)

Home page :

![Home page](docs/menu1.png?raw=true "Home page")

Top menu :

![Top menu](docs/menu2.png?raw=true "Top menu")

A robot driving screen (can go straigh, turn left or right. Press left + right for sub menu) :

![Pilote](docs/menu3.png?raw=true "Pilote")

Sub menu for small-robot features (see project [robot-small](https://github.com/manuito/robot-small)) :

![Sub menu](docs/menu4.png?raw=true "Sub menu")

### Using the SD card files for config

Some configuration files will be managed from the SD card :
* Details on wifi to connect with
* a file similar to /etc/hosts for name based specification of the devices to drive

In a futur version :
* Organization of piloted device features

### Included server

Created on demand ?

### Basic client

Creating the client at launch vs on demand ?

# Revision 2

The new revision is smaller, lighter, and more "children proof". I use only standard D1 mini boards + 1 board from Tindie. 
See My Hackaday page for more details

Component view :

![Inside view](docs/proto_2_inside.png?raw=true "Inside view")

Code is simpler than in 1st revision. As the screen is much smaller, I have replaced menus by more graphical stuff, including animation. And this time I have made a box (from a standard project box)

Boxed view :

![Boxed view](docs/proto_2_on.png?raw=true "Boxed view")


I will improve the code later. For now it can drive "mini robot" only.

Using it :

![Using view](docs/proto_2_using.png?raw=true "Using view")

