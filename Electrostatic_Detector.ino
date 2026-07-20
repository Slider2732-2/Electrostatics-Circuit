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
    reading = (reading * 7 + analogRead(A0)) / 8;


    // Convert sensor behaviour into positive field strength
    fieldStrength = baseline - reading;


    // Ignore tiny negative movement
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



    // Trigger HIGH event - might be increased depending on testing
    if(fieldStrength > 50)
    {
        highDisplay = true;
        highTimer = millis();
    }


    // Clear HIGH after 10 seconds
    if(highDisplay && millis() - highTimer > 10000)
    {
        highDisplay = false;
    }



    // DISPLAY
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("ELECTRIC FIELD");

    // Bar graph
    int width = map(fieldStrength,0,200,0,126);
    width = constrain(width,0,126);
    display.drawRect(0,30,128,14,SSD1306_WHITE);
    display.fillRect(1,31,width,12,SSD1306_WHITE);

    // Values
    display.setCursor(0,52);
    display.print("Field:");
    display.print(fieldStrength);

    display.setCursor(64,52);
    display.print("Peak:");
    display.print(peakField);


    if(highDisplay)
    {
        display.setTextSize(2);
        display.setCursor(80,12);
        display.print("HIGH");
        display.setTextSize(1);
    }


    display.display();
}