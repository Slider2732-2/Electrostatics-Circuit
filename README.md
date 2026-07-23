An ongoing DIY project to research and develop a DIY lightning/general electrostatics detection circuit. <br>
The project uses an Arduino Nano, SSD1306 screen and a simple detector circuit.<br><br> 

The full circuit diagram is to follow, but the base circuit has been uploaded. <br>
See the Slider2732_ YouTube channel for more information and videos about this project. <br>
This project uses the Arduino IDE for code development. <br>
Current version is ElectrostaticDetector_V101.ino, which is Version 1.01
<br><br>
Note <br>
The grey wire running down the middle of the board is from the transistor Collector to Arduino A0 and is shielded (this one was from an ESP32 antenna extension). I tried unshielded and it did not work anywhere near as well as the shielded wire. Shield to circuit ground, core to transistor and A0.
<br>
![Picture](./Pictures/ESVsmall.jpg)
<br>
<br>
The required project parts: <br>
--- Processing section <br>
Arduino Nano <br>
SSD1306 128x64 I2C<br>
10K variable potentiometer <br>
22K resistor <br>
<br>
--- Sensor section <br> 
100uf 16V electrolytic capacitor <br>
0.1uF ceramic capacitor <br>
68 ohms resistor <br>
C945 transistor <br>
5mm red LED
Elecret microphone (with metal can removed)
