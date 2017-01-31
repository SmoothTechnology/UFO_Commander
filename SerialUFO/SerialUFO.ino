#include<FastLED.h>
#include "CommonVariables.h"
#include "mappings.h"
#include "utils.h"
#include "patterns.h"

/* Helper functions */

//Input a rateue 0 to 384 to get a color rateue.
//The colours are a transition r - g -b - back to r
void setColors()
{
  color1 = myColor(r1, g1, b1);
  color2 = myColor(r2, g2, b2);
}

void hideAll() {
  for (int i = 0; i < totalLEDs; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
}

void showAll() {
  LEDS.show();
}


void ledCheck(){
  int f = 0;
  int s = 6;
  int curColorVal = 255;
  while(f < 25){
      for(int i = 0; i < totalLEDs; i++){

        leds[i] = CRGB(curColorVal, curColorVal, curColorVal);
      }

      curColorVal = curColorVal - 10;
      LEDS.show();
      f++;
      delay(20);
  }

}

void SetNewMapping(int value)
{
  if(value == 0)
  {
    mapping = &forward;
  }
  else if(value == 1)
  {
    mapping = &peak;
  }
  else if(value == 2)
  {
    mapping = &valley;
  }
  else if(value == 3)
  {
    mapping = &dither;
  }
  else if(value == 4)
  {
    mapping = &dekonstruktor;
  }

  //Horizontal Mapping
  else if(value == 5)
  {
    mapping = &H_forward;
  }
  else if(value == 6)
  {
    mapping = &H_peak;
  }
  else if(value == 7)
  {
    mapping = &H_valley;
  }
  else if(value == 8)
  {
    mapping = &H_dither;
  }
  else if(value == 9)
  {
    mapping = &H_dekonstruktor;
  }

  //Vertical Mapping
  else if(value == 10)
  {
    mapping = &V_forward;
  }
  else if(value == 11)
  {
    mapping = &V_peak;
  }
  else if(value == 12)
  {
    mapping = &V_valley;
  }
  else if(value == 13)
  {
    mapping = &V_dither;
  }
  else if(value == 14)
  {
    mapping = &V_dekonstruktor;
  }

}

String inputString;
#define MYADDR 4
#define MYSETADDR 6
#define GLOBALADDR 0

#define DEBUG_PORT  Serial
#define LEDINPUTSERIAL Serial2

void read() {

  while (LEDINPUTSERIAL.available()) {

    DEBUG_PORT.println(inputString);

    char c = (char)LEDINPUTSERIAL.read();
    // Serial.println(c, DEC);
    inputString += c;
    if (c == 'z') {

      DEBUG_PORT.println(inputString);

      if (inputString.charAt(0) == -127) {

        // Heartbeat.

        // Big fat hack to turn a String into an int.
        String sub = inputString.substring(1, inputString.length()-1);
        char c[sub.length()];
        for (int i = 0; i < sub.length(); i++) {
          c[i] = sub.charAt(i);
        }

      } else { 

        unsigned char addr = (unsigned char)inputString.charAt(0);

        // Pattern.
        if (addr == MYADDR || addr == MYSETADDR || addr == GLOBALADDR) {
          
          rate = (unsigned char)inputString.charAt(1) + 1;
          patternByte = (unsigned char)inputString.charAt(2);

          r1 = (unsigned char)inputString.charAt(3);
          g1 = (unsigned char)inputString.charAt(4);
          b1 = (unsigned char)inputString.charAt(5);
          r2 = (unsigned char)inputString.charAt(6);
          g2 = (unsigned char)inputString.charAt(7);
          b2 = (unsigned char)inputString.charAt(8);
          r3 = (unsigned char)inputString.charAt(9);
          g3 = (unsigned char)inputString.charAt(10);
          b3 = (unsigned char)inputString.charAt(11);

          mIndBrightness = ((unsigned char)inputString.charAt(12))/127.0;

          mappingByte = (unsigned char)inputString.charAt(13);

          setColors();

          SetNewMapping(mappingByte);
          
          if (patternByte == OFF_PATTERN) {
            hideAll();
            showAll();
            isOff = true;
          } 
          else if (patternByte != NULL_PATTERN && patterns[patternByte] != NULL) {
            isOff = false;
            pattern = patterns[patternByte];
            pattern(-2, 0); // On select initialization
            if(patternByte != lastPattern)
            {
              lastPattern = patternByte;
              frame = 1000000;
            }
          }

        }

      }

      inputString = "";

    }

  }

}


//enum controlEnum{setBrightness = 0, setRed1 = 1, setGreen1 = 2, setBlue1 = 3, setPattern = 4, 
//                 setRate = 5, setMapping = 6, setRed2 = 7, setGreen2 = 8, setBlue2 = 9};
//void OnControlChange(byte channel, byte control, byte value) {
//  
//  boolean colorChanged = false;
//
//  if(control == setBrightness)
//  {
//    mIndBrightness = ((float)value) / 127.0;
//  }
//  else if(control == setRed1)
//  {
//    r1 = map(value, 0, 127, 0, 255);
//    colorChanged = true;
//  }
//  else if(control == setGreen1)
//  {
//    g1 = map(value, 0, 127, 0, 255);
//    colorChanged = true;
//  }
//  else if(control == setBlue1)
//  {
//    b1 = map(value, 0, 127, 0 ,255);
//    colorChanged = true;
//  }
//  else if(control == setPattern)
//  {
//
//    #ifdef USE_VDMX
//      patternByte = mPattern_to_patternByte(DecodeVDMXPattern(value));
//    #else
//      patternByte = mPattern_to_patternByte(value);
//    #endif
//
//    if (patternByte != NULL_PATTERN && patterns[patternByte] != NULL) {
//      isOff = false;
//      pattern = patterns[patternByte];
//      pattern(-2, 0); // On select initialization
//    }
//    // Reset frame if pattern change
//    if(patternByte != lastPattern)
//    {
//      lastPattern = patternByte;
//      frame = 1000000;
//    }
//
//  }
//  else if(control == setRate)
// {
//   rate = map(value, 0, 127, 0, 255);
// }
// else if(control == setMapping)
// {
//   SetNewMapping(value);
// }
// else if(control == setRed2)
// {
//   r2 = map(value, 0, 127, 0, 255);
//   colorChanged = true;
// }
// else if(control == setGreen2)
// {
//   g2 = map(value, 0, 127, 0, 255);
//   colorChanged = true;
// }
// else if(control == setBlue2)
// {
//   b2 = map(value, 0, 127, 0, 255);
//   colorChanged = true;
// }

// if(colorChanged)
// {
//   setColors();
// }

//

byte currentCommandBuf [READBUFFERSIZE];
#define DATA_PIN 8

void setup() {
  pinMode(13, OUTPUT);
  //Serial.begin(115200);
  LEDINPUTSERIAL.begin(9600);
  DEBUG_PORT.begin(9600);

  LEDS.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  LEDS.setBrightness(255);

  ledCheck();

  setColors();

  hideAll();
  showAll();

  patterns[1] = &flickerStrobeTwo;
  patterns[2] = &flickerStrobeFour;
  patterns[3] = &totesRandom;
  patterns[4] = &rainbowCycle;
  patterns[5] = &rainbow;
  // 67 = pause
  // 68 = off
  patterns[6] = &solidColor;
  patterns[7] = &gradient;
  patterns[8] = &pulseSine;
  patterns[9] = &pulseSaw;
  patterns[10] = &bounce;
  patterns[11] = &colorWipe;
  patterns[12] = &colorAlternator;
  patterns[13] = &stripe;
  patterns[14] = &colorChase;
  patterns[15] = &colorWipeMeter;
  patterns[16] = &colorWipeMeterGradient;
  patterns[17] = &pulseOnce;

  // pattern = &pulseOnce;
  pattern = &pulseOnce;
  mapping = &forward;

  mIndBrightness = 255;
  
  rate = mRate + 1;

  inputString.reserve(200);
}

void loop() {

  read();

  int usedRate = 128-rate;
  mCurrentFrameCount += abs(usedRate);
  
  if(mCurrentFrameCount >= NUM_STEPS_PER_FRAME)
  {
    int framesToMove = mCurrentFrameCount/NUM_STEPS_PER_FRAME;
    mCurrentFrameCount = mCurrentFrameCount - framesToMove*NUM_STEPS_PER_FRAME;
    
    frame += usedRate < 0 ? -1*framesToMove : framesToMove;  
  }

  if (frame != lastFrame)
    pattern(-1, 0); // Per frame initialization

  lastFrame = frame;

  for (int i = 0; i < totalLEDs; i++) {

    int j = mapping(frame, i);
    uint32_t color = pattern(frame, j);

    uint8_t r = ((color & 0xFF0000) >> 16);
    uint8_t g = ((color & 0x00FF00) >> 8);
    uint8_t b = ((color & 0x0000FF));

    //TODO change setbrightness only on change
    if (mIndBrightness < 1.0) {
      r *= mIndBrightness;
      g *= mIndBrightness;
      b *= mIndBrightness;
    }

    float whiteDimmer = 0.7;

    if (r == g && g == b) {
      r *= whiteDimmer;
      g *= whiteDimmer;
      b *= whiteDimmer;
    }

    leds[i] = CRGB(r, g, b); 
  }

  if (isOff) {
    hideAll();
  }

  showAll();

  if (frame >= MAX_FRAME) {
    frame = 0;
  }

  // Do Not light pin 13
  //if (light)
  //  digitalWrite(13, HIGH);
  //else
  //  digitalWrite(13, LOW);

  //light = !light;

}

