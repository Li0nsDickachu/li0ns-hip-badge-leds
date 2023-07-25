// Li0n, 2023

// todo: -make it easy to change the color
//       -put this code and all previous iterations on git

#include <FastLED.h> //load the fastled library
 
#define NUM_LEDS 16 // how many leds in your strip?
#define DATA_PIN 10 // the pin that sends rgb data to the strip
#define IR_RX_PIN 3 // RX = receiver, IR = infrared
#define IR_TX_PIN 7 // TX = transmitter
#define BUTTON1_PIN 2
#define BUTTON2_PIN 8

#define COLOR Blue //set the color here

int DELAY = 63; // standard value is 63
int DELAY2 = 58; // section 3 and 4 have 1 extra dot in the sequence, so it needs to move faster to keep up.
volatile int RESET = 0; // volatile has to be specified because of the ISR
volatile int BRIGHTNESS = 20;
volatile int ButtonPress1 = 0;
volatile int ButtonPress2 = 0;
int RANDOM1;
int RANDOM2;
int HUE = 160;

CRGB leds[NUM_LEDS]; // Define the array of leds


void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB is not the conventional order, had to manually edit this
    FastLED.setBrightness(BRIGHTNESS);
    pinMode(IR_TX_PIN, OUTPUT); // initialize the infrared transmitter pin as output
    randomSeed(1337); // for the sparkles

    // ISR setup below:
    pinMode(IR_RX_PIN, INPUT); // initialize the infrared receiver trigger pin as an input
    Serial.begin(9600); //start serial connection
    attachInterrupt(digitalPinToInterrupt(IR_RX_PIN), IR_TRIGGER, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), BUTTON1, RISING);
    attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), BUTTON2, RISING);
}

void loop() {
    RESET = 0;

    // 1
    for(int dot = (NUM_LEDS - 1); dot < NUM_LEDS*5 - 1; dot++) {   // 1 travelling dot circling anti-clockwise
        // break; // don't forget to comment this out
        if (RESET == 1){
          break;}
        if (ButtonPress1 == 1){
          if (BRIGHTNESS == 20){
            BRIGHTNESS = 255;
            Serial.println(BRIGHTNESS);}
          else {
            BRIGHTNESS = 20;
            Serial.println(BRIGHTNESS);}
          FastLED.setBrightness(BRIGHTNESS);
          ButtonPress1 = 0;}
        if (ButtonPress2 == 1){
            HUE = ((HUE + 40) % 360);
            Serial.println(HUE);
            ButtonPress2 = 0;}
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CHSV(HUE, 255, 255);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Black;
        delay(DELAY);
    }
    for(int dot = 0; dot < NUM_LEDS*4 + 1; dot++) {   // 1 travelling dot circling clockwise
        if (RESET == 1)
          break;
        leds[dot % NUM_LEDS] = CHSV(HUE, 255, 255);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot % NUM_LEDS] = CRGB::Black;
        delay(DELAY);
    }

    //2
    for(int dot = (NUM_LEDS - 1); dot < NUM_LEDS*5 - 1; dot++) {   // 2 travelling dots circling anti-clockwise
        if (RESET == 1)
          break;
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CHSV(HUE, 255, 255);
        leds[NUM_LEDS - (((dot + 8) % NUM_LEDS) + 1)] = CHSV(HUE, 255, 255);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Black;
        leds[NUM_LEDS - (((dot + 8) % NUM_LEDS) + 1)] = CRGB::Black;
        delay(DELAY);
    }
    for(int dot = 0; dot < NUM_LEDS*4 + 2; dot++) {   // 2 travelling dots circling clockwise
        if (RESET == 1)
          break;
        leds[dot % NUM_LEDS] = CHSV(HUE, 255, 255);
        leds[(dot + 8) % NUM_LEDS] = CHSV(HUE, 255, 255);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot % NUM_LEDS] = CRGB::Black;
        leds[(dot + 8) % NUM_LEDS] = CRGB::Black;
        delay(DELAY);
    }

    //3
    for(int dot = 0; dot < 9*8 - 1; dot++) {   // 2 travelling dots down
        if (RESET == 1)
          break;
        leds[dot % 9] = CHSV(HUE, 255, 255);
        leds[(NUM_LEDS - (dot % 9)) % NUM_LEDS] = CHSV(HUE, 255, 255);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot % 9] = CRGB::Black;
        leds[(NUM_LEDS - (dot % 9)) % NUM_LEDS] = CRGB::Black;
        delay(DELAY2);
    }

    //4
    for(int dot = 9*8 - 1; dot >= 0; dot--) {   // 2 travelling dots up
        if (RESET == 1)
          break;
        leds[dot % 9] = CHSV(HUE, 255, 255);
        leds[(NUM_LEDS - (dot % 9)) % NUM_LEDS] = CHSV(HUE, 255, 255);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot % 9] = CRGB::Black;
        leds[(NUM_LEDS - (dot % 9)) % NUM_LEDS] = CRGB::Black;
        delay(DELAY2);
    }

    //5
    for(int dot = 0; dot < NUM_LEDS*4; dot++) {   // 2 travelling up and down
        if (RESET == 1)
          break;
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CHSV(HUE, 255, 255);
        leds[(dot + 1) % NUM_LEDS] = CHSV(HUE, 255, 255);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Black;
        leds[(dot + 1) % NUM_LEDS] = CRGB::Black;
        delay(DELAY);
    }

    //6
    for(int dot = 0; dot < NUM_LEDS*8 + 4; dot++) {   // sparkles
        if (RESET == 1)
          break;
        RANDOM1 = random(3);
        RANDOM2 = random(16,19); // I couldn't figure out how to get random() to output 2 different numbers in a row
        leds[(dot*3 + RANDOM1)% NUM_LEDS ] = CHSV(HUE, 255, 255);
        leds[(dot*3 + (NUM_LEDS/2)+ RANDOM2) % NUM_LEDS] = CHSV(HUE, 255, 255);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[(dot*3 + RANDOM1)% NUM_LEDS ] = CRGB::Black;
        leds[(dot*3 + (NUM_LEDS/2)+ RANDOM2) % NUM_LEDS] = CRGB::Black;
        delay(DELAY);
    }
    FastLED.show();
    //send IR pulse
    digitalWrite(IR_TX_PIN, HIGH);
    // Serial.println("sending IR pulse");
    delay(25);
    digitalWrite(IR_TX_PIN, LOW);
    // Serial.println("IR pulse sent");

}

void IR_TRIGGER(){
    RESET = 1;
    // Serial.println("reset");
}

void BUTTON1(){
    ButtonPress1 = 1;
}

void BUTTON2(){
    ButtonPress2 = 1;
}
