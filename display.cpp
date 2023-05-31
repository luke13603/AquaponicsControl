#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "DisplayPHInfo.h"

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 lcd = Adafruit_ILI9341(10, 9);


//define some color values
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define LABEL_COLOR WHITE
#define NUMBER_COLOR CYAN

#define ORIGIN_X 20
#define ORIGIN_Y 40
#define NUMBERS_ORIGIN_X 200

#define TEXT_HEIGHT 50

double temp = 20.56;
double ph = 7.0;
double potassium = 1.0;
double ammonia = 2.0;

void setSensorValues(float temp_, float ph_, float potassium_){
  temp = temp_;
  ph = ph_;
  potassium = potassium_;
  // ammonia = ammonia_;
}

void printConstantText(){
  lcd.setCursor(ORIGIN_X, ORIGIN_Y);
  lcd.setTextColor(LABEL_COLOR);
  lcd.setTextSize(3);
  
  lcd.print("Temp:");
  lcd.setCursor(ORIGIN_X, ORIGIN_Y + TEXT_HEIGHT*1);
  lcd.print("PH:");
  lcd.setCursor(ORIGIN_X, ORIGIN_Y + TEXT_HEIGHT*2);
  lcd.print("Potassium:");

  lcd.setCursor(70, 210);
  lcd.setTextSize(1);
  lcd.print("Aquaponics Monitoring System V2");
}

// Configure the screen and place the constant text in setup
void setupDisplay(){
  Serial.begin(9600);
  lcd.begin();
  lcd.setRotation(1);
  lcd.fillScreen(BLACK);
  lcd.setTextWrap(false);
  printConstantText();
}

// Display all of the numbers
void updateValues(){
  lcd.setTextColor(NUMBER_COLOR, BLACK);
  lcd.setTextSize(3);
  lcd.setCursor(NUMBERS_ORIGIN_X, ORIGIN_Y);
  
  lcd.print(temp);
  lcd.setCursor(NUMBERS_ORIGIN_X, ORIGIN_Y + TEXT_HEIGHT *1);
  lcd.print(ph);
  lcd.setCursor(NUMBERS_ORIGIN_X, ORIGIN_Y + TEXT_HEIGHT *2);
  lcd.print(potassium);
}