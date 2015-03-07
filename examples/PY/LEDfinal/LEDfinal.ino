// Use if you want to force the software SPI subsystem to be used for some reason (generally, you don't)
// #define FORCE_SOFTWARE_SPI
// Use if you want to force non-accelerated pin access (hint: you really don't, it breaks lots of things)
// #define FORCE_SOFTWARE_PINS
#include "FastLED.h"

//color of the light
//Order is GRB, not RGB
//needs at least 02 for red
#define projectY 0xFF00FF
#define red 0x00FF00
#define green 0xFF0000
#define blue 0x0000FF
#define yellow 0xFFFF00
#define black 0x000000

///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 

// How many leds are in the strip?
#define NUM_LEDS 294

#define RIGHT_SIDE 94
#define LEFT_SIDE 100
#define UNDERCARRIAGE 100
//How many LEDs will be lit at the top?
#define TOP_LEDS 5

// Data pin that led data will be written out over
#define DATA_PIN 2

//Digital Input Pins
#define BLUE_ALLIANCE 3
#define OPEN 4
#define TOTE 5
#define DISABLED 6

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS], allianceColor, color;
boolean  openArms, tote, disabled, blueAlliance;
double robotHeight, LEDHeight;

// This function sets up the ledsand tells the controller about them
void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  pinMode(BLUE_ALLIANCE, INPUT);
  pinMode(OPEN, INPUT);
  pinMode(TOTE, INPUT);
  
  
  delay(2000);
  //         Serial.begin(9600); 

  // Uncomment one of the following lines for your leds arrangement.
  // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  for (int i=0;i<NUM_LEDS;i++){
    leds[i] = CRGB::Blue;
  }
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {

  

// test code comment this out before running on the robot  
  

//  blueAlliance = true;
//  openArms = false;
//  tote = false;
//  disabled = false;
  
//Read digital inputs
  blueAlliance = digitalRead(BLUE_ALLIANCE);
  if (blueAlliance) {
     allianceColor = blue; 
  }
  else {
      allianceColor = red; 
  }
  
  openArms = digitalRead(OPEN);
  tote = digitalRead(TOTE);
  if (openArms) {
     color = green; 
  }
  else if (tote) {
     color = yellow; 
  } 
  else {
     color = red; 
  }
  
  disabled = digitalRead(DISABLED);
  /*if (disabled) {
     color = projectY;
     allianceColor = projectY; 
  }*/
  
  //read analog;
  robotHeight=analogRead(0); //Height is a value between 0 and 1024
  LEDHeight=(NUM_LEDS-UNDERCARRIAGE)*robotHeight/1024/2; //LEDHeight is amount of LEDS to be lit on each side

   
  
  for (int i=0;i<=NUM_LEDS;i++){
    /*if (i < height) {
      leds[i]=color;       
    }  
    else if ((NUM_LEDS - i) < height) {
      leds[i]=color; 
    }
    else {
      leds[i]=CRGB::Black;  
    }
    leds[i]=green;*/
    if (i < LEFT_SIDE) { //Adressing LEFT_SIDE
      if (i < LEDHeight) {
        leds[i] = color; 
      }
      else if (i >= LEFT_SIDE - TOP_LEDS){
        leds[i] = color;        
      }
      else {
        leds[i] = black;
      }
    }
    else if (i < RIGHT_SIDE + LEFT_SIDE) { //Addressing RIGHT_SIDE
      if (i < LEFT_SIDE + TOP_LEDS) {
         leds[i] = color; 
      }
      else if (i > (RIGHT_SIDE + LEFT_SIDE) - LEDHeight) {
         leds[i] = color; 
      }
      else {
        leds[i] = black;
      }
    }
    else {//Addressing UNDERCARRIAGE
//      if (blueAlliance) {
        leds[i] = allianceColor;
/*      }
      else{
        leds[i] = allianceColor;
      }*/
    }  
  }
  
  if (disabled) {
     for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = projectY;
     } 
  }
  
  
  FastLED.show();  
  delay(100);
}






