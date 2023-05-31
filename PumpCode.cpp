//this code is to be used with 2 peristaltic pumps
//each pump supplies a different chemical compound; one to raise ph and one to lower
//each peristaltic pump will need a relay to be able to run on an arduino; maybe

#include "Arduino.h"
#include "sensors.h"
#include "DisplayPHInfo.h"
//this code was painful to integrate.
extern double PHChange;

const int WATER_PUMP_PIN_R = 5;
const int WATER_PUMP_PIN_L = 4;
int motorR = 5;
int motorL = 4;
const int doseDuration = 2000;
const float phToleration = 0.25;
const float phTarget = 7 + PHChange;
bool isDosingH = false;
bool isDosingL = false;

//probably need 2 of theses
void setupPump() {
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);
  analogWrite(motorR, 5);
  analogWrite(motorL, 4);
}

//no comment
void waterPumpRaise() {
  analogWrite(motorR, 255);
  analogWrite(motorL, 0);
}

void waterPumpLower() {
  analogWrite(motorR,0);
  analogWrite(motorL, 255);
}

void waterPumpsOff(){
  analogWrite(motorR, 0);
  analogWrite(motorL, 0);
}

//this shit will probably crash the program or just continue to raise the PH level with no qualms about whether or not its killing things.

//needlessly complicated but Its a prototype
void phCheck(){
  if (getPH() < phTarget || getPH() > phTarget) {
    if (getPH() < phTarget - phToleration) {
      // start to raise the pH
      Serial.println("pH lower than target, beginning to raise acidity");
      isDosingH = true;
    }
    if (isDosingH) {
      //raises acid
      waterPumpRaise();
      delay(2000);
      waterPumpsOff();
    }
    if(getPH() > phTarget + phToleration){
      Serial.println("pH higher than target, beginning to lower acidity");
      isDosingL = true;
    }
    if(isDosingL){
      waterPumpLower();
      delay(2000);
      waterPumpsOff();
    }
  } 
  else {
    isDosingH = false;
    isDosingL = false;
  }
}