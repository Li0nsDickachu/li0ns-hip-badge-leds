#include <FastLED.h>
 
// How many leds in your strip?
#define NUM_LEDS 16

#define DATA_PIN 10
 
// Define the array of leds
CRGB leds[NUM_LEDS];
 
void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical. lion's note: grb ordering is assumed, but the hip-badge seems to take rgb ordering. waht I mean is, when I typed red, the led turned green.
}
 
void loop() { 
  // Turn the LED on, then pause
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}
