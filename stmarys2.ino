#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

boolean hasPressed = false;
boolean previous[8] = {false};
int count = 1;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(2, INPUT);   
}

void loop() {
  int sensorValue = analogRead(0);
  int red = constrain(map(sensorValue, 0, 512, 255, 0), 0, 255); 
  int green = constrain(map(sensorValue, 0, 512, 0, 255), 0, 255)-constrain(map(sensorValue, 512, 1023, 0, 255), 0, 255);
  int blue = constrain(map(sensorValue, 0, 512, 0, 255), 0, 255);
  
  if(red < 25) red = 5;
  if(green < 25) green = 5;
  if(blue < 25) blue = 5;
  
  // Some example procedures showing how to display to the pixels:
  /*
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127,   0,   0), 50); // Red
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
  */
  
  Serial.println(String(digitalRead(2)) + ", " + String(hasPressed) + ", " + String(count) + ", " + String(sensorValue) + ", " + String(red) + ", " + String(green) + ", " + String(blue));

  /*
  red = red/1.25;
  green = green/1.25;
  blue = blue/1.25;
  */
  if (digitalRead(2) == HIGH){     
    hasPressed = true;
  } 
  
  else if(hasPressed){
    count++;
    hasPressed = false;
  }
  
  if(count==9) count=1;
 
  switch(count){
    case 1: //if(!previous[0]){
      setColor(red, green, blue);
      setPrevious(0);
    //}
    break;
    
    case 2: //if(!previous[1]){
      setRed(sensorValue, red);
      setPrevious(1);
    //}
    break;
    
    case 3: //if(!previous[2]){
      setOrange(sensorValue, red);
      setPrevious(2);
    //}
    break;
    
    case 4: //if(!previous[3]){
      setYellow(sensorValue, red);
      setPrevious(3);
    //}
    break;
    
    case 5:  //if(!previous[4]){
      setGreen(sensorValue, green);
      setPrevious(4);
    //}
    break;
    
    case 6: //if(!previous[5]){
      setBlue(sensorValue, blue);
      setPrevious(5);
    //}
    break;
    
    case 7: //if(!previous[6]){
      setPurple(sensorValue, red);
      setPrevious(6);
    //}
    break;
    
    case 8: //if(!previous[7]){
      setPink(sensorValue, red);
      setPrevious(7);
    //}
    break;
    
    default: setColor(red, green, blue);
    
  }
  
  //setColor(0, 0, 255);
  //colorWipe(strip.Color(red, green, blue), 2);
  //handWipe(sensorValue, blue);
  
  //setBlue(sensorValue, blue);
  
  //setGreen(sensorValue, green);
   
  //setRed(sensorValue, red);
  
  //setPurple(sensorValue, red);
  
  //setWhite(sensorValue, red);
  
  //setYellow(sensorValue, red);
  
  //setOrange(sensorValue, red);
  
  //setPink(sensorValue, red);
}

/*
void setColor(byte red, byte green, byte blue){
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, red, green, blue);
    strip.show();
    delay(100);
  }
  //delay(300);
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
    delay(100);
  }
  //delay(300);
}
*/
/*
void setValues(){ 
  sensorValue = analogRead(0);
  red = constrain(map(sensorValue, 0, 512, 255, 0), 0, 255); 
  green = constrain(map(sensorValue, 0, 512, 0, 255), 0, 255)-constrain(map(sensorValue, 512, 1023, 0, 255), 0, 255);
  blue = constrain(map(sensorValue, 0, 512, 0, 255), 0, 255);
}
*/
void setPrevious(int index){
  previous[index] = true;
  for(int i = 0; i < 8; i++){
    if(i!=index) previous[i] = false;
  }
}

void setColor(byte red, byte green, byte blue){
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, red, green, blue);
    strip.show();
  }
}

void setPink(int sensorValue, byte red){
  int green = red;
  int blue = red;
  int sv = map(sensorValue, 0, 512, 0, strip.numPixels());
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, red, green/3, blue/3);
    strip.show();
  }
}

void setYellow(int sensorValue, byte red){
  int green = red;
  int sv = map(sensorValue, 0, 512, 0, strip.numPixels());
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, red, green, 0);
    strip.show();
  }
}

void setOrange(int sensorValue, byte red){
  int green = red;
  int sv = map(sensorValue, 0, 512, 0, strip.numPixels());
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, red, green/3, 0);
    strip.show();
  }
}

void setWhite(int sensorValue, byte red){
  int blue = red;
  int green = red;
  int sv = map(sensorValue, 0, 512, 0, strip.numPixels());
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, red, green, blue);
    strip.show();
  }
}

void setPurple(int sensorValue, byte red){
  int blue = red;
  int sv = map(sensorValue, 0, 512, 0, strip.numPixels());
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, red, 0, blue);
    strip.show();
  }
}

void setBlue(int sensorValue, byte blue){
  int sv = map(sensorValue, 0, 512, 0, strip.numPixels());
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, 0, 0, blue);
    strip.show();
  }
}

void setGreen(int sensorValue, byte green){
  int sv = map(sensorValue, 0, 512, 0, strip.numPixels());
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, 0, green, 0);
    strip.show();
  }
}

void setRed(int sensorValue, byte red){
  int sv = map(sensorValue, 0, 512, 0, strip.numPixels());
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, red, 0, 0);
    strip.show();
  }
}

void handWipe(int sensorValue, byte blue){
  int sv = map(sensorValue, 0, 512, 0, strip.numPixels());
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, blue, 0, 0);
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
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

