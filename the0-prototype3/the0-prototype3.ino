// Li0n, 2023

#include <FastLED.h>
 
#define NUM_LEDS 16 // How many leds in your strip?
#define DATA_PIN 10
#define DELAY 250

CRGB leds[NUM_LEDS]; // Define the array of leds
 
void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB is not the conventional order, had to manually edit this
    FastLED.setBrightness(20);
    Serial.begin(9600); //start serial connection
}

void loop() {
    for(int dot = 0; dot < NUM_LEDS*4; dot++) {   // 1 travelling dot circling anti-clockwise
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Blue;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Black;
        delay(DELAY);
    }

    for(int dot = 0; dot < NUM_LEDS*4 + 1; dot++) {   // 1 travelling dot circling clockwise
        leds[dot % NUM_LEDS] = CRGB::Blue;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot % NUM_LEDS] = CRGB::Black;
        delay(DELAY);
    }

}
