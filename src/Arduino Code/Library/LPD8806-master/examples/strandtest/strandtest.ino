#include <SoftwareSerial.h>

#include <LPD8806.h>
#include "SPI.h" // Comment out this line if using Trinket or Gemma

#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif

// Example to control LPD8806-based RGB LED Modules in a strip

/*****************************************************************************/

// Number of RGB LEDs in strand:
int nLEDs = 60;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 4;
int clockPin = 2;

// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

// You can optionally use hardware SPI for faster writes, just leave out
// the data and clock pin parameters.  But this does limit use to very
// specific pins on the Arduino.  For "classic" Arduinos (Uno, Duemilanove,
// etc.), data = pin 11, clock = pin 13.  For Arduino Mega, data = pin 51,
// clock = pin 52.  For 32u4 Breakout Board+ and Teensy, data = pin B2,
// clock = pin B1.  For Leonardo, this can ONLY be done on the ICSP pins.
//LPD8806 strip = LPD8806(nLEDs);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  // Start up the LED strip
 Serial.begin(9600);
   // Serial.println("Start Serial here");
  strip.begin();
  //Serial.println("come here");

  // Update the strip, to start they are all 'off'
  strip.show();
    //Serial.println("reach here");

}


void loop() {
char data_1 = '1';
char data_2 = '0';
//colorChase(strip.Color(127, 127, 127), 50); 
 // colorChase(strip.Color(127,   0,   0), 50); // Red
Serial.println("end here");
while (data_1 == '1'){
  data_2=rainbow(10);
  if (data_2=='2'){
    break;
  }
  
}
data_1='0';
while (data_2=='2'){
  int a=millis()%256;
  Serial.println(a);
  randomSeed(a);
  
  data_1=colorWipe(strip.Color(random(127), random(127), random(127)), 10); // White
  if (data_1=='1'){
    break;
  }
  /*colorChase(strip.Color(127,   0,   0), 50); // Red
  colorChase(strip.Color(127, 127,   0), 50); // Yellow
  colorChase(strip.Color(  0, 127,   0), 50); // Green
  colorChase(strip.Color(  0, 127, 127), 50); // Cyan
  colorChase(strip.Color(  0,   0, 127), 50); // Blue
  colorChase(strip.Color(127,   0, 127), 50); // Violet*/
  /*data_1 = Serial.read();
  Serial.println(data_1);
  if (data_1=='1'){
    break;
  }*/
}
data_2 == 0;
  // Send a simple pixel chase in...
 /* colorChase(strip.Color(127, 127, 127), 50); // White
  colorChase(strip.Color(127,   0,   0), 50); // Red
  colorChase(strip.Color(127, 127,   0), 50); // Yellow
  colorChase(strip.Color(  0, 127,   0), 50); // Green
  colorChase(strip.Color(  0, 127, 127), 50); // Cyan
  colorChase(strip.Color(  0,   0, 127), 50); // Blue
  colorChase(strip.Color(127,   0, 127), 50); // Violet*/

  // Send a theater pixel chase in...
 /* theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127,   0,   0), 50); // Red
  theaterChase(strip.Color(127, 127,   0), 50); // Yellow
  theaterChase(strip.Color(  0, 127,   0), 50); // Green
  theaterChase(strip.Color(  0, 127, 127), 50); // Cyan
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue
  theaterChase(strip.Color(127,   0, 127), 50); // Violet*/

  // Fill the entire strip with...
  //colorWipe(strip.Color(127,   0,   0), 50);  // Red
  //colorWipe(strip.Color(  0, 127,   0), 50);  // Green
  //colorWipe(strip.Color(  0,   0, 127), 50);  // Blue

  //rainbow(10);*/
 // rainbowCycle(0);  // make it go through the cycle fairly fast
   // Serial.println("end here");

  //theaterChaseRainbow(50);
}

char rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 384; j++) {     // 3 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 384));
      char data= Serial.read();
  //Serial.println(data);
  if (data=='2'){
    return '2';
  }
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
  return '1';
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  
  for (j=0; j < 384 * 5; j++) {     // 5 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      
      strip.setPixelColor(i, Wheel( ((i * 384 / strip.numPixels()) + j) % 384) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Fill the dots progressively along the strip.
char colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
      char data_1 = Serial.read();
      //Serial.println(data_1);
      if (data_1=='1'){
      return '1';
  }
  }
  return '0';
}

// Chase one dot down the full strip.
void colorChase(uint32_t c, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
  Serial.println(strip.numPixels());

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    //Serial.println("get here");
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(wait);
    //Serial.println("display pixel");
  }
//Serial.println("get here");
  strip.show(); // Refresh to turn off last pixel
 // Serial.println("get there");
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 384; j++) {     // cycle all 384 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 384));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}

