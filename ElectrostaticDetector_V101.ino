/*
Electrostatic Detector V1.01
Slider2732_ July 2026
*/


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(128,64,&Wire,-1);


// Sensor values
int reading = 0;
long baseline = 0;
int fieldStrength = 0;
int displayValue= 0;
int peakField = 0;

// HIGH indicator timer
bool highDisplay = false;
unsigned long highTimer = 0;

// Peak decay
unsigned long lastDecay = 0;


void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC,0x3C);

    reading = analogRead(A0);

    // Startup calibration
    unsigned long startTime = millis();

    long total = 0;
    int samples = 0;


    while(millis() - startTime < 3000)
    {
        reading = (reading * 7 + analogRead(A0)) / 8;
        total += reading;
        samples++;


        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(1);
        display.setCursor(18,10);
        display.print("ELECTRIC FIELD");

        display.setCursor(18,27);
        display.print("Calibrating...");

        display.setCursor(18,56);
        display.print("Version 1.01");




        int bar = map(millis()-startTime,0,3000,0,124);

        display.drawRect(2,40,124,10,SSD1306_WHITE);
        display.fillRect(3,41,bar,8,SSD1306_WHITE);
        display.display();
        delay(20);
    }


    baseline = total / samples;
    peakField = 0;
}



void loop()
{
    // Smooth sensor reading
    reading = (reading * 7 + analogRead(A0)) /8;


   // Bipolar field value
displayValue = baseline - reading;

// Positive-only value used for HIGH detection
fieldStrength = displayValue;

if(fieldStrength < 0)
    fieldStrength = 0;

    // Peak event memory
    if(fieldStrength > peakField)
    {
        peakField = fieldStrength;
    }


    // Slow return of peak value
    if(millis() - lastDecay > 100)
    {
        if(peakField > fieldStrength)
            peakField--;

        lastDecay = millis();
    }



    // Trigger HIGH event - original was 50, now is 100
    if(fieldStrength > 100)
    {
        highDisplay = true;
        highTimer = millis();
    }


    // Clear 'HIGH' being displayed after 3 seconds
    if(highDisplay && millis() - highTimer > 3000)
    {
        highDisplay = false;
    }



    // DISPLAY
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("ELECTRIC FIELD");

    // ----- Bipolar bar graph -----
    const int zeroX = 12;
    display.drawRect(0,30,128,14,SSD1306_WHITE);

    // Zero marker
    display.drawLine(zeroX,30,zeroX,43,SSD1306_WHITE);

    // Labels
    display.setCursor(2,21);
    display.print("-");

    display.setCursor(120,21);
    display.print("+");

    if(displayValue >= 0)
      {
       int width = map(displayValue,0,200,0,114);
       width = constrain(width,0,114);

       display.fillRect(zeroX+1,31,width,12,SSD1306_WHITE);
      }
else
      {
       int width = map(-displayValue,0,25,0,11);
       width = constrain(width,0,11);

       display.fillRect(zeroX-width,31,width,12,SSD1306_WHITE);
      }
      
       // Values
       display.setCursor(0,52);
       display.print("Field:");

       if(displayValue > 0)
         display.print("+");
         display.print(displayValue);

         display.setCursor(78,52);
         display.print("Peak:");
         display.print(peakField);


       if(highDisplay)
         {
          display.setTextSize(2);
          display.setCursor(70,12);
          display.print("HIGH");
          display.setTextSize(1);
         }


    display.display();
}