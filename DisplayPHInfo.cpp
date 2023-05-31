#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include "DisplayPHInfo.h"
#include "display.h"
#include <stdint.h>
#include "TouchScreen.h" 
extern Adafruit_ILI9341 lcd;

#define YP A3  // must be an analog pin, use "An" notation!
#define XN A4  // must be an analog pin, use "An" notation!
#define YN 8   // can be a digital pin
#define XP 9
TouchScreen ts = TouchScreen(XP, YP, XN, YN, 300);

// This is calibration data for the raw touch data to the screen coordinates
//numbers for ph edit readings
#define ORIGIN_X 20
#define ORIGIN_Y 40

//numbers for touchscreen box
#define PHT_MinX 15
#define PHT_MinY 80
#define PHT_H 40
#define PHT_W 50

//copy pasted numbers for back button
#define PHT_MinXB 15
#define PHT_MinYB 80
#define PHT_HB 40
#define PHT_WB 50

//setup stuff for phstat screen
#define NUMBERS_ORIGIN_X 200
#define TEXT_HEIGHT 50
#define BLACK   0x0000
#define CYAN    0x07FF
#define WHITE   0xFFFF
#define LABEL_COLOR WHITE
#define NUMBER_COLOR CYAN

//stuff for the back button
#define PHT_MinYB 80
#define PHT_MaxXB 70
#define PHT_MaxYB 190
#define PHT_HB 40
#define PHT_WB 50

bool firstPage = false;

const int ButtonSeq = 2;
const int ButtonL = 4;
int buttonStateSeq = 0;
int buttonStateL = 0;

int selector = 0;
boolean isPressed = false;
int buttonP;

//button settings to go to ph stats page
#define PHButtonX PHT_MinX
#define PHButtonY PHT_MinY
#define PHButtonH PHT_H
#define PHButtonW PHT_W

double PHBase = 0.0;
double PHChange = PHBase;

void drawFrame()
{
  pinMode(ButtonSeq, INPUT);
  pinMode(ButtonL, INPUT);
  lcd.drawRect(PHT_MinX, PHT_MinY, PHT_W, PHT_H, ILI9341_WHITE);
  buttonStateSeq = digitalRead(ButtonSeq);
  buttonStateL = digitalRead(ButtonL);
}
//TODO: fix this, it's okay for now
void PHStatsUI(){
  lcd.fillScreen(BLACK);
  lcd.setTextColor(NUMBER_COLOR, BLACK);
  lcd.setTextSize(3);
  lcd.setCursor(NUMBERS_ORIGIN_X, ORIGIN_Y + TEXT_HEIGHT *1.5);
  lcd.print(PHChange);
}

void PrintPHText(){
  lcd.setCursor(ORIGIN_X, ORIGIN_Y);
  lcd.setTextColor(LABEL_COLOR);
  lcd.setTextSize(3);
  
  lcd.print("raise ph (+.25)");
  lcd.setCursor(ORIGIN_X, ORIGIN_Y + TEXT_HEIGHT*.75);
  lcd.print("lower ph (-.25)");
  lcd.setCursor(ORIGIN_X, ORIGIN_Y + TEXT_HEIGHT*1.5);
  lcd.print("PH set at:");
  lcd.setCursor(ORIGIN_X, ORIGIN_Y + TEXT_HEIGHT*2.25);
  lcd.print("Back");
}
//never do this, this is a bad way of cycling the button
//touchscreen would be better but I don't have the time to read the library
void buttonSwitch() {
  if (digitalRead(ButtonSeq) == LOW && isPressed == false ) //button is pressed AND this is the first digitalRead() that the button is pressed
  {
    isPressed = true;  //set to true, so this code will not run again until button released
    buttonP++; // this is done after the doSwitchStatement(), so case 0 will be executed on the first button press 
    if (buttonP > 2) {
      buttonP = 0;
    }
  } 
  else if (digitalRead(ButtonSeq) == HIGH){
    isPressed = false; //button is released, variable reset
  }
  else{
    Serial.println("no");
  }
}

void doButtonThings() {
  if(buttonP = 0 && digitalRead(ButtonL) == LOW){
    PHChange = PHBase + 0.25;
  }
  else if(buttonP = 1 && digitalRead(ButtonL) == LOW){
    PHChange = PHBase - 0.25;
  }
  else if(buttonP = 2 && digitalRead(ButtonL) == LOW){
    firstPage = false;
    lcd.fillScreen(BLACK);
    drawFrame();
  }
  else{
    Serial.println("no");
  }
}

//why would I put the main display button code in the ph display code?
//Its the easiest way to do it; I dont care if it would look cleaner another way
void buttonSwitchMain() {
  if (digitalRead(ButtonSeq) == LOW && isPressed == false ) //button is pressed AND this is the first digitalRead() that the button is pressed
  {
    isPressed = true;  //set to true, so this code will not run again until button released
    buttonP++; // this is done after the doSwitchStatement(), so case 0 will be executed on the first button press 
    if (buttonP > 1) {
      buttonP = 0;
    }
    // selector = (selector+1) % 4;  // does the same, without if-statement
  } 
  else if (digitalRead(ButtonSeq) == HIGH){
    isPressed = false; //button is released, variable reset
  }
  else{
    Serial.println("no");
  }
}

void doButtonThingsMain() {
  if(buttonP = 0 && digitalRead(ButtonL) == LOW){

  }
  else if(buttonP = 1 && digitalRead(ButtonL) == LOW){
    firstPage = true;
    lcd.fillScreen(BLACK);
    drawFrame();
  }
  else{
     Serial.println("no");
  }
}

//I have rewritten the UI code from scratch, THREE DIFFERENT TIMES