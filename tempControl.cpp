#include <OneWire.h>
#include <DallasTemperature.h>
#include "sensors.h"
#include "Arduino.h"
 
#define RELAY_PIN   A5 

const int TEMP_THRESHOLD_UPPER = 23; // upper threshold of temperature, change to your desire value
const int TEMP_THRESHOLD_LOWER = 20; // lower threshold of temperature, change to your desire value

void setupTemp() {  
  pinMode(RELAY_PIN, OUTPUT); // initialize digital pin as an output
}

void checkTemp(){
  if(getSensorTemp() > TEMP_THRESHOLD_UPPER) {
    Serial.println("The heating element is turned off");
    digitalWrite(RELAY_PIN, LOW); // turn off
  } else if(getSensorTemp() < TEMP_THRESHOLD_LOWER){
    Serial.println("The heating element is turned on");
    digitalWrite(RELAY_PIN, HIGH); // turn on
  }
}