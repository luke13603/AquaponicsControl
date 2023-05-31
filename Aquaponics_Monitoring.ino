#include "Sensors.h"
#include "Display.h"
#include "DisplayPHInfo.h"
#include "PumpCode.h"
#include "tempControl.h"
#include "Adafruit_ILI9341.h"
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
// wait 5 seconds before reading pH again
const int sensorReadInterval = 5000;

extern const int WATER_PUMP_PIN;
extern int motor;
extern const int doseDuration;
extern const float phToleration;
extern const float phTarget;
extern bool isDosing;
extern bool firstPage;
extern Adafruit_STMPE610 ts;

void setup(void){
// start serial port so we can see the data
Serial.begin(9600);

startTempSensor();
setupDisplay();
setupPump();
setupTemp();
}

void loop(void){
while(firstPage != true){
  setSensorValues((getSensorTemp() * 1.8 ) + 32, getPH(), getPotassium()); //Farhenheit conversion because celsius sucks
  updateValues();
  Serial.print("Temperature: ");
  Serial.print(getSensorTemp());
  Serial.println();
  Serial.print("PH: "); 
  Serial.print(getPH());
  Serial.println();
  Serial.print("Potassium: ");
  Serial.print(getPotassium());
  Serial.println();
  delay(1000);
  checkTemp();
  phCheck();
  //buttonSwitchMain();
  //doButtonThingsMain();
}

while(firstPage){
  PrintPHText();
  PHStatsUI();
  buttonSwitch();
  doButtonThings();
  }

}