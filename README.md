An ongoing DIY project to research and develop a DIY lightning/general electrostatics detection circuit. <br>
It was created to explore measurable environmental changes using inexpensive electronics. The device does not identify causes of detected changes; it provides repeatable readings that can be compared across locations and conditions. <br>
The project uses an Arduino Nano, SSD1306 screen and a simple detector circuit. Optionally, you can also use a small speaker for sound output and/or add an LED levels display. <br><br> 

The full circuit diagram is included above. <br>
New is the addition of the circuit diagram including the speaker output and LED's. <br>
See the Slider2732_ YouTube channel for more information and development videos. <br>
This project uses the Arduino IDE for code development. <br>
Current version is ElectrostaticDetector_V124.ino, which is Version 1.24
<br>
<br>
This device reports the change in the Arduino analogue reading from the calibrated baseline. The displayed values are not calibrated electrostatic field strength (e.g. V/m), but relative measurements that allow repeatable comparisons between locations and conditions.
<br><br>
Notes: <br>
The grey wire running down the middle of the board is from the transistor Collector to Arduino A0 and is shielded (this one was from an ESP32 antenna extension). I tried non shielded and it did not work anywhere near as well as the shielded wire. Shield to circuit ground, core to transistor and A0.
<br>
Also, depending on your USB supply you may need a 'Keep Alive' circuit between the source and the circuit. The circuit may not draw enough power for some powerbanks. 
<br><br>
![Picture](./Pictures/ES_Vero_Full_small.JPG)
<br>
<br>
Here is the optional LED's section -

<br>
![Picture](./Pictures/Optional_LED's_small.jpg)
<br>
The required project parts: <br>
--- Processing section <br>
Arduino Nano <br>
SSD1306 128x64 I2C<br>
10K variable potentiometer <br>
22K resistor <br>
<br>
Optional:
<br>
Small headphone type speaker <br>
1K variable potentiometer for sound volume
<br><br>
--- Sensor section <br> 
100uf 16V electrolytic capacitor <br>
0.1uF ceramic capacitor <br>
68 ohms resistor <br>
C945 transistor <br>
5mm red LED
Elecret microphone (with metal can removed)
