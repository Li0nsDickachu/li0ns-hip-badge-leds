// Li0n, 2023

#include <FastLED.h>
 
#define NUM_LEDS 16 // How many leds in your strip?
#define DATA_PIN 10
#define DELAY 100

CRGB leds[NUM_LEDS]; // Define the array of leds
 
void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB is not the conventional order, had to manually edit this
    FastLED.setBrightness(20);
    Serial.begin(9600); //start serial connection
}
void loop() {
  for(int loopy = 0; loopy < 4; loopy++) {
    for(int dot = 1; dot <= NUM_LEDS; dot++) {   // 1 travelling dot circling anti-clockwise
        leds[NUM_LEDS - dot] = CRGB::Blue;
        FastLED.show();
          // clear this led for the next time around the loop
        leds[NUM_LEDS - dot] = CRGB::Black;
        delay(DELAY);
        }
  }
  for(int loopy = 0; loopy < 4; loopy++) {
    for(int dot = 0; dot < NUM_LEDS; dot++) {   // 1 travelling dot circling clockwise
        leds[dot] = CRGB::Blue;
        FastLED.show();
          // clear this led for the next time around the loop
        leds[dot] = CRGB::Black;
        delay(DELAY);
    }
  }
  leds[0] = CRGB::Blue;
  FastLED.show();
   // clear this led for the next time around the loop
  leds[0] = CRGB::Black;
  delay(DELAY);
}