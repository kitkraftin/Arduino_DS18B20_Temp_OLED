#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2
#define OLED_WIDTH 128 // OLED display width,  in pixels
#define OLED_HEIGHT 64 // OLED display height, in pixels

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);	

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void setup(void)
{
  sensors.begin();	// Start up the library
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 20);        // position to display
  oled.println("Temperature"); // text to display
  oled.println("Sensor"); // text to display
  oled.display();
  oled.clearDisplay(); // clear display
}

void loop(void)
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures(); 

  float T = sensors.getTempCByIndex(0);

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.print((char)176);//shows degrees character
  Serial.print("C  |  ");
  
  //print the temperature in Fahrenheit
  Serial.print((T * 9.0) / 5.0 + 32.0);
  Serial.print((char)176);//shows degrees character
  Serial.println("F");
  
  oled.clearDisplay(); // clear display
  oled.setTextSize(1); 
  oled.setCursor(0, 0);
  oled.println("Temperature: ");   // display temperature in deg Celsius
  oled.setTextSize(2); 
  oled.setCursor(0, 20);
  //Celcius
  oled.print(T);
  oled.print(" ");
  oled.cp437(true);    	// code page 437
  oled.write(167);     	// character 167 is degree
  oled.println("C");
  //Fahrenheit
  oled.print((T * 9.0) / 5.0 + 32.0);
  oled.print(" ");
  oled.cp437(true);    	// code page 437
  oled.write(167);     	// character 167 is degree
  oled.println("F");
  oled.display();		// for the changes to make effect

  delay(500);
}