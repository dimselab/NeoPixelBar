#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {  
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // add your method here!
  stars(20);
  runningColor(strip.Color(255,0,0), 80);
  // Some example procedures showing how to display to the pixels:

  /*
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  
  //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127, 0, 0), 50); // Red
  theaterChase(strip.Color(0, 0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
  */
  ChristmasLights(150);
  colorFireworks(10);
  midWalker(20);
  
}

/*

  Invent a routine for the LED and implement it in at method here!

*/

// @Ebbe Vang
void runningColor(uint32_t color, int speed)
{
  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, color);
    strip.setPixelColor(i-1, strip.Color(0,0,0));
    delay(100-speed);
    strip.show();
  }
}

// @Ebbe Vang
void stars(int amount)
{
  int stars[amount];

  //set random pixels as stars
  for (int i=0; i<amount; i++)
  {
    stars[i] = random(strip.numPixels());
  }
  
  for (int i=100; i>=0; i--)
  {
    int brightness = 255 / 100*i;
    for (int j=0; j<amount; j++)
    { 
      strip.setPixelColor(stars[j], strip.Color(brightness, brightness, brightness));
    }
    delay(15);
    strip.show();
  }
    
}
  

  


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Group: dailybot (Rasmus & Mathias)
// Should send lights from both ends towards the other end.
void midWalker(uint8_t wait){
 int q = strip.numPixels();
 for (int j=0; j<4; j++){ // does 4 cycles
   for (int i=0; i < strip.numPixels(); i++){
     q = q -1;
      if(i<(strip.numPixels()/2)){
       
      strip.setPixelColor(i, 0, 255, 0);
                     
    }else if(i>= (strip.numPixels()/2)){
     
      strip.setPixelColor(i, 0, 255, 0);
                     
     }
    if(q<= (strip.numPixels()/2)){
     
      strip.setPixelColor(q, 0, 0, 255);
     
     }else if(q>= (strip.numPixels()/2)){
       
       strip.setPixelColor(q, 0, 0, 255);
     }
     
   
   strip.show();

   delay(wait);
   }
 }
}
// Group: Niklas & Daniel
void ChristmasLights(uint8_t wait)
{
  uint32_t colors[7] ;
  colors[0] = strip.Color(255,0,0);
  colors[1] = strip.Color(75,0,50);
  colors[2] = strip.Color(0,0,255);
  colors[3] = strip.Color(0,255,100);
  colors[4] = strip.Color(0,255,0);
  colors[5] = strip.Color(255,90,0);
  colors[6] = strip.Color(255,50,0);
  int counter =0;
  for (int j = 0; j < 5; j++) {
   for(int q=0;q<14;q++){
      for(uint16_t i=0; i<strip.numPixels();i++) {
          strip.setPixelColor(i+q, colors[counter]);
          counter++;
          if (counter == 7){
            counter = 0;
          }
         }
      strip.show();

      delay(wait);
      for(uint16_t i=0; i<strip.numPixels();i++) {
            strip.setPixelColor(i+q, colors[counter]);
          counter++;
          if (counter == 7){
            counter = 0;
          }
      }
    }
  }
}

//Group: Nicki, Ricco, Fabian and Tom
//Color Fireworks
int fireworksj = 0;
void colorFireworks(uint8_t wait) {
  // colors
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t yellow = strip.Color(255,90,0);
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t purple = strip.Color(75,0,50);
  uint32_t orange = strip.Color(255,50,0);
  uint32_t green = strip.Color(0, 255, 0);
  // arrays
  uint32_t istart[3] = {red, blue, yellow};
  uint32_t xstart[3] = {yellow, red, blue};
  uint32_t combine[3]= {orange, purple, green};
  // ..........
  int x = strip.numPixels();
  
  for(int i=0; i<strip.numPixels(); i++){  
    strip.clear();
    if(i<strip.numPixels()/2) {
      strip.setPixelColor(i, istart[fireworksj]);
      strip.setPixelColor(i-1, istart[fireworksj]);
      strip.setPixelColor(i-2, istart[fireworksj]);
      strip.setPixelColor(i-3, istart[fireworksj]);
      strip.setPixelColor(i-4, istart[fireworksj]);
      strip.setPixelColor(x, xstart[fireworksj]);
      strip.setPixelColor(x+1, xstart[fireworksj]);
      strip.setPixelColor(x+2, xstart[fireworksj]);
      strip.setPixelColor(x+3, xstart[fireworksj]);
      strip.setPixelColor(x+4, xstart[fireworksj]);
    }
    else if(i>strip.numPixels()/2)
    {
      strip.setPixelColor(i, combine[fireworksj]);
      strip.setPixelColor(i+1, combine[fireworksj]);
      strip.setPixelColor(i+2, combine[fireworksj]);
      strip.setPixelColor(i+3, combine[fireworksj]);
      strip.setPixelColor(i+4, combine[fireworksj]);
      strip.setPixelColor(x, combine[fireworksj]);
      strip.setPixelColor(x-1, combine[fireworksj]);
      strip.setPixelColor(x-2, combine[fireworksj]);
      strip.setPixelColor(x-3, combine[fireworksj]);
      strip.setPixelColor(x-4, combine[fireworksj]);
    }
    x--;
    strip.show();
    delay(wait);
  }
  fireworksj++;
  if(fireworksj>2){
    fireworksj = 0;
  }
  strip.clear(); 
}
