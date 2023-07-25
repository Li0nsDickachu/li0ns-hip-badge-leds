// Li0n, 2023

#include <FastLED.h>
 
#define NUM_LEDS 16 // How many leds in your strip?
#define DATA_PIN 10

int DELAY = 65;
const String comma = ", ";

CRGB leds[NUM_LEDS]; // Define the array of leds
 
void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB is not the conventional order, had to manually edit this
    FastLED.setBrightness(20);
}

void loop() {
    // 1
    for(int dot = 0; dot < NUM_LEDS*4 - 1; dot++) {   // 1 travelling dot circling anti-clockwise
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

    //2
    for(int dot = 0; dot < NUM_LEDS*4 - 1; dot++) {   // 2 travelling dots circling anti-clockwise
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Blue;
        leds[NUM_LEDS - (((dot + 8) % NUM_LEDS) + 1)] = CRGB::Blue;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Black;
        leds[NUM_LEDS - (((dot + 8) % NUM_LEDS) + 1)] = CRGB::Black;
        delay(DELAY);
    }
    for(int dot = 0; dot < NUM_LEDS*4 + 2; dot++) {   // 2 travelling dots circling clockwise
        leds[dot % NUM_LEDS] = CRGB::Blue;
        leds[(dot + 8) % NUM_LEDS] = CRGB::Blue;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot % NUM_LEDS] = CRGB::Black;
        leds[(dot + 8) % NUM_LEDS] = CRGB::Black;
        delay(DELAY);       
    }

    //3
    for(int dot = 0; dot < NUM_LEDS*4; dot++) {   // 2 travelling dots down
        leds[dot % (NUM_LEDS/2)] = CRGB::Blue;
        leds[NUM_LEDS - ((dot % (NUM_LEDS/2)) + 1)] = CRGB::Blue;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot % (NUM_LEDS/2)] = CRGB::Black;
        leds[NUM_LEDS - ((dot % (NUM_LEDS/2)) + 1)] = CRGB::Black;
        delay(DELAY);
    }

    //4 todo
    for(int dot = 0; dot < NUM_LEDS*4; dot++) {   // 2 travelling dots up
        leds[dot % (NUM_LEDS/2)] = CRGB::Blue;
        leds[NUM_LEDS - ((dot % (NUM_LEDS/2)) + 1)] = CRGB::Blue;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot % (NUM_LEDS/2)] = CRGB::Black;
        leds[NUM_LEDS - ((dot % (NUM_LEDS/2)) + 1)] = CRGB::Black;
        delay(DELAY);
    }

    //5
    for(int dot = 0; dot < NUM_LEDS*4; dot++) {   // 2 travelling up and down
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Blue;
        leds[(dot + 1) % NUM_LEDS] = CRGB::Blue;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Black;
        leds[(dot + 1) % NUM_LEDS] = CRGB::Black;
        delay(DELAY);
    }

    //6
    for(int dot = 0; dot < NUM_LEDS*8 - 4; dot++) {   // 1 travelling dot circling clockwise
        leds[dot*3 % NUM_LEDS] = CRGB::Blue;
        leds[(dot*3 + 8) % NUM_LEDS] = CRGB::Blue;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot*3 % NUM_LEDS] = CRGB::Black;
        leds[(dot*3 + 8) % NUM_LEDS] = CRGB::Black;
        delay(DELAY);
    }

// note: 5 is too long, 6 is shortened to compensate. fix later

}
