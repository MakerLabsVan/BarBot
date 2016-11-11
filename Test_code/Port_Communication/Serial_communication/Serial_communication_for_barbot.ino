#include <SoftwareSerial.h>
#include <LPD8806.h>
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif

// Number of RGB LEDs in strand:
int nLEDs = 60;
int mark=-3;
// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 4;
int clockPin = 2;
const int buttonPin = 10; 
int buttonState = 0;   

// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);


void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif
 pinMode(buttonPin, INPUT);
  // Start up the serial port
 Serial.begin(9600);
  // Start up the LED strip
  strip.begin();
  // Update the strip, to start they are all 'off'
  strip.show();

}


void loop() {
char data_1 = '1';//set the initial value of data_1
char data_2 = '0';//set the initial value of data_2
//The reason for initialize two data value here is that sometimes the LED strip will send 
//some random data to the serial port. If using only one data value, it may be polluted by
//this random value and the program will go wrong

while (data_1 == '1'){
  data_2=rainbow(10);//the LED pattern when the machine is standby
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    delay(100);
    if (buttonState == HIGH) {
      digitalWrite(ledPin, HIGH);
      Serial.println("E");
      delay(1000);
    }
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  if (data_2=='2'){
    break;//when machine is running, break the loop and change the pattern
  }
  
}
data_1='0';// Change the value of data_1
while (data_2=='2'){
  int a=millis();
  randomSeed(a);//set the random seed using current time in ms.
  
  data_1=colorWipe(strip.Color(random(127), random(127), random(127)), 10, mark); // fill the strip with the random color
  if (data_1=='1'){
    break;//when machine finishes the job, break the loop and change the pattern
    }
    if (data_1=='5'){
      mark = 10;
    }
    if (data_1=='6'){
      mark = 11;
    }
    if (data_1=='7'){
      mark = 12;
    }
    if (data_1=='8'){
      mark = 13;
      }
      if (data_1 == '9'){
        mark =-3;
      }
    

  }
}

char rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 384; j++) {     // 3 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 384));
      char data= Serial.read();
  if (data=='2'){//check the serial port everytime writing the pixel.
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
char colorWipe(uint32_t c, uint8_t wait,int LED_mark) {
  int i;
  Serial.print("LED MARK is");
  Serial.println(LED_mark);
  for (i=0; i < strip.numPixels(); i++) {
    if (i==LED_mark){
      strip.setPixelColor(i,strip.Color(127,0,0));
      strip.show();
      delay(wait);
      Serial.println("Success!");
    }else{
      //Serial.println(strip.numPixels());
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
      char data_1 = Serial.read();
      if (data_1=='1'){//check the serial port everytime writing the pixel.
      mark=-3;
      return '1';
      }
      if (data_1=='5'){
        return '5';
      }
      if (data_1=='6'){
        return '6';
      }
      if (data_1=='7'){
        return '7';
      }
      if (data_1=='8'){
        return '8';
      }
      if (data_1=='9'){
        return '9';
      }
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

