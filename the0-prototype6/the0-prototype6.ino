// Li0n, 2023

#include <FastLED.h>
 
#define NUM_LEDS 16 // How many leds in your strip?
#define DATA_PIN 10

int DELAY = 65;
const String comma = ", ";

CRGB leds[NUM_LEDS]; // Define the array of leds
 

#define IR_PIN 3
int buttonState = 0;  // variable for reading the pushbutton status

void setup() { 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB is not the conventional order, had to manually edit this
  FastLED.setBrightness(20);
  pinMode(IR_PIN, INPUT); // initialize the pushbutton pin as an input
  Serial.begin(9600); //start serial connection
  attachInterrupt(digitalPinToInterrupt(IR_PIN), IR_TRIGGER, FALLING);
}

void loop() {
    // 1
    for(int dot = 0; dot < NUM_LEDS*4 - 1; dot++) {   // 1 travelling dot circling anti-clockwise
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Blue;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Black;
        buttonState = digitalRead(IR_PIN);
        Serial.print(buttonState);
        delay(DELAY);
    }
}

void IR_TRIGGER(){
  Serial.println("reset");
}