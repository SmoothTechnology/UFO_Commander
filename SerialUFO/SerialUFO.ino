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
  while(f < 300){
      for(int i = 0; i < totalLEDs; i++){
        if ((i + f)/s % s < s/2){
          leds[i] = CRGB(255,255,0);
        }
        else
        leds[i] = CRGB(0,0,255);
      }

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
    mapping = &backward;
  }
  else if(value == 2)
  {
    mapping = &snake;
  }
  else if(value == 3)
  {
    mapping = &intoSpace;
  }
  else if(value == 4)
  {
    mapping = &shortSnake;
  }
  else if(value == 5)
  {
    mapping = &longSnake;
  }
  else if(value == 6)
  {
    mapping = &dekonstruktor;
  }
  else if(value > 7)
  {
    mapping = &deskonstruktorIntoSpace;
  }
  //else if(value == 7)
  //{
  //  mapping = &dekonstruktorRando;
  //}
}

String inputString;
#define MYADDR 1
#define MYSETADDR 6
#define GLOBALADDR 0

#define LEDINPUTSERIAL Serial1

void read() {
  
  if(Serial.available())
  {
    while(Serial.available())
      Serial.read();
    r1 = 255;setColors();
    Serial.println("SET");
  }

  while (LEDINPUTSERIAL.available()) {

    char c = (char)LEDINPUTSERIAL.read();
    // Serial.println(c, DEC);
    inputString += c;
    if (c == 128) {

      Serial.println(inputString);

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
#define DATA_PIN 6

void setup() {

  pinMode(13, OUTPUT);
  //Serial.begin(115200);
  LEDINPUTSERIAL.begin(9600);

  LEDS.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS).setCorrection( 0x9FFAF0 );;
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

  rate = 122;
  // pattern = &pulseOnce;
  pattern = &gradient;
  mapping = &intoSpace;

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

  if (light)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);

  light = !light;

}

