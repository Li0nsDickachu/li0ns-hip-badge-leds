// Li0n, 2023

// todo: -add more palettes
//       -make a separate version of this program that detects how far ahead or behind it is and edits the delay time to catch up. optionally merge that version later.
//       -make the ESPs use short range bluetooth as backup sync method

// to modify the code to work on any arduino IDE compatible board with any FastLED compatible board, check out all the comments that start with <<< and edit those lines to match your setup

#include <FastLED.h> // load the fastled library
 
#define NUM_LEDS 40 // <<< how many leds in your strip?
#define DATA_PIN 14 // <<< the pin that sends rgb data to the led strip
// #define IR_RX_PIN 3 // <<< IR = infrared, RX = receiver
// #define IR_TX_PIN 7 // <<< TX = transmitter
// #define BUTTON1_PIN 2 // <<<
// #define BUTTON2_PIN 8 // <<<

int x = 29; // <<< offset
int index_number = 160; // standard value is 160, which is blue. edit to change default blink color.
int DELAY = (1008/NUM_LEDS); // standard value is 1008. edit DELAY and DELAY2 values if your board is not running in sync with another. desync can be caused by hardware differences, differnce in board shape/size, or timer calibration.
int DELAY2 = (928/NUM_LEDS); // standard value is 928. section 3 and 4 have 1 extra dot in the sequence, so it needs to move faster to keep up.
int DELAY3 = (1750/NUM_LEDS);

volatile int RESET = 0; // volatile has to be specified because of the ISR
volatile int ButtonPress1 = 0;
volatile int ButtonPress2 = 0;
int BRIGHTNESS = 255;
int rainbow_mode = 0;
int palette_index = 0;
int RANDOM1;
int RANDOM2;
int cycle;

//IR_TX functions
// unsigned long previous_time = 0;
// const int blink_length = 25; // value in millis
// const int blink_period = 13; // the correct value would be 13.1578947368. for a frequency of 38KhZ, the led needs to turn on and off every 26.315789473684 microseconds so it needs to switch states twice in that time.


CRGB leds[NUM_LEDS]; // Define the array of leds
CRGBPalette16 current_palette = RainbowColors_p;
TBlendType    currentBlending = NOBLEND;

void BUTTONFUNC(){
    if (ButtonPress1 == 1){
        if (ButtonPress2 == 1){
            if (BRIGHTNESS == 20){  // adjust brightness
                BRIGHTNESS = 255;
            }
            else {
                BRIGHTNESS = 20;
            }
            // Serial.println(BRIGHTNESS);
            FastLED.setBrightness(BRIGHTNESS);
            ButtonPress2 = 0;
        }
        else {
            if (rainbow_mode == 0) {
                rainbow_mode = 1;
            }
            else {
                rainbow_mode = 0;
                PALETTEFUNC();  // change current palette
            }
        }
        ButtonPress1 = 0;
    }
    if (ButtonPress2 == 1) {
        if (rainbow_mode == 0) {
            index_number = ((index_number + 16) % 256);  // cycle through the colors of the pallete, once per button press
            // Serial.println(index_number);
            ButtonPress2 = 0;
        }
        else {
            rainbow_mode = rainbow_mode + (rainbow_mode % 2);
            if (rainbow_mode == 1) {
              currentBlending = NOBLEND;
            }
            if (rainbow_mode == 2) {
              currentBlending = LINEARBLEND;
            }
        }
    }
    if (rainbow_mode == 1) {
        index_number = ((index_number + 16) % 256); // cycle through the palette, once per dot loop
        // Serial.println(rainbow_mode);
    }
    if (rainbow_mode == 2) {
        index_number = ((index_number + 1) % 256); // cycle through the palette, once per dot loop
        // Serial.println(rainbow_mode);
    }
}

void PALETTEFUNC(){
    index_number = 0;
    palette_index = ((palette_index + 1) % 5);
    Serial.println(palette_index);
    if (palette_index == 0) {
        index_number = 160;
        current_palette = RainbowColors_p;
    }
    if (palette_index == 1) {
        SetupPinkandBluePalette();
    }
    if (palette_index == 2) {
        current_palette = ForestColors_p;
    }
    if (palette_index == 3) {
        current_palette = CloudColors_p;
    }
    if (palette_index == 4) {
        current_palette = OceanColors_p;
    }
}

void SetupPinkandBluePalette()
{
    CRGB lightblue = CRGB::Cyan;
    CRGB pink  = CRGB::Magenta;
    CRGB white  = CRGB::White;
    
    current_palette = CRGBPalette16(
        lightblue,  pink,  white,  pink,
        lightblue,  pink,  white,  pink,
        lightblue,  pink,  white,  pink,
        lightblue,  pink,  white,  pink
    );
}

void setup() { 
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS); // <<< GRB is not the conventional order, had to manually edit this. look at the FastLED example sketch "Blink.ino" and "RGBCalibrate" to see what to put here if you're using different LEDS or you're seeing unexpected colors.
    FastLED.setBrightness(BRIGHTNESS);
    // pinMode(IR_TX_PIN, OUTPUT); // initialize the infrared transmitter pin as output
    randomSeed(1337); // for the sparkles

    // ISR setup below:
    // pinMode(IR_RX_PIN, INPUT); // initialize the infrared receiver trigger pin as an input
    // Serial.begin(115200); //start serial connection
    // attachInterrupt(digitalPinToInterrupt(IR_RX_PIN), IR_TRIGGER, FALLING);
    // attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), BUTTON1, RISING);
    // attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), BUTTON2, RISING);
}

void loop() {
    Serial.println("lion-start");
    RESET = 0;

    //buttonless setup:
    rainbow_mode = 2;

    // 1
    for(int dot = NUM_LEDS - 1 - x; dot < NUM_LEDS*5 - 1 - x; dot++) {   // 1 travelling dot circling anti-clockwise
        // break; // don't forget to comment this out
        if (RESET == 1){
            break;}
        BUTTONFUNC();
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Black;
        delay(DELAY);
    }
    for(int dot = NUM_LEDS + x; dot < NUM_LEDS*5 + 1 + x; dot++) {   // 1 travelling dot circling clockwise
        // break; // don't forget to comment this out
        if (RESET == 1){
            break;}
        BUTTONFUNC();
        leds[dot % NUM_LEDS] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot % NUM_LEDS] = CRGB::Black;
        delay(DELAY);
    }

    //2
    for(int dot = NUM_LEDS - 1 - x; dot < NUM_LEDS*5 - 1 - x; dot++) {   // 2 travelling dots circling anti-clockwise
        // break; // don't forget to comment this out
        if (RESET == 1){
            break;}
        BUTTONFUNC();
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        leds[NUM_LEDS - (((dot + (NUM_LEDS/2)) % NUM_LEDS) + 1)] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[NUM_LEDS - ((dot % NUM_LEDS) + 1)] = CRGB::Black;
        leds[NUM_LEDS - (((dot + (NUM_LEDS/2)) % NUM_LEDS) + 1)] = CRGB::Black;
        delay(DELAY);
    }
    for(int dot = NUM_LEDS - x; dot < - x + NUM_LEDS*5 + 1; dot++) {   // 2 travelling dots circling clockwise
        // break; // don't forget to comment this out
        if (RESET == 1){
            break;}
        BUTTONFUNC();
        leds[dot % NUM_LEDS] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        leds[(dot + (NUM_LEDS/2)) % NUM_LEDS] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot % NUM_LEDS] = CRGB::Black;
        leds[(dot + (NUM_LEDS/2)) % NUM_LEDS] = CRGB::Black;
        delay(DELAY);
    }

    //3
    for(int dot = 0; dot < ((NUM_LEDS/2) + 1)*8 - 1; dot++) {   // 2 travelling dots down
        // break; // don't forget to comment this out
        if (RESET == 1){
            break;}
        BUTTONFUNC();
        leds[((dot % ((NUM_LEDS/2) + 1)) + x) % NUM_LEDS] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        leds[(NUM_LEDS + x - (dot % ((NUM_LEDS/2) + 1))) % NUM_LEDS] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[((dot % ((NUM_LEDS/2) + 1)) + x) % NUM_LEDS] = CRGB::Black;
        leds[(NUM_LEDS + x - (dot % ((NUM_LEDS/2) + 1))) % NUM_LEDS] = CRGB::Black;
        delay(DELAY2);
    }

    //4
    for(int dot = ((NUM_LEDS/2) + 1)*8 - 1; dot >= 0; dot--) {   // 2 travelling dots up
        // break; // don't forget to comment this out
        if (RESET == 1){
            break;}
        BUTTONFUNC();
        leds[((dot % ((NUM_LEDS/2) + 1)) + x) % NUM_LEDS] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        leds[(NUM_LEDS + x - (dot % ((NUM_LEDS/2) + 1))) % NUM_LEDS] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[((dot % ((NUM_LEDS/2) + 1)) + x) % NUM_LEDS] = CRGB::Black;
        leds[(NUM_LEDS + x - (dot % ((NUM_LEDS/2) + 1))) % NUM_LEDS] = CRGB::Black;
        delay(DELAY2);
    }

    //5
    for(int dot = 1; dot < NUM_LEDS*4 + 1; dot++) {   // 2 travelling dots up and down
        if (RESET == 1){
            break;}
        BUTTONFUNC();
        leds[((NUM_LEDS + x - (dot % NUM_LEDS)) % NUM_LEDS)] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        leds[(dot + x) % NUM_LEDS] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[((NUM_LEDS + x - (dot % NUM_LEDS)) % NUM_LEDS)] = CRGB::Black;
        leds[(dot + x) % NUM_LEDS] = CRGB::Black;
        delay(DELAY);
    }

    //6
    for(int dot = 0; dot < NUM_LEDS*6 + 4; dot++) {   // sparkles
        if (RESET == 1){
            break;}
        BUTTONFUNC();
        RANDOM1 = (random(19) + 29) % 40;
        RANDOM2 = (random(20, 39) + 29) % 40;
        leds[RANDOM1] = ColorFromPalette(current_palette, index_number, 255, currentBlending);
        leds[RANDOM2]= ColorFromPalette(current_palette, index_number, 255, currentBlending);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[RANDOM1] = CRGB::Black;
        leds[RANDOM2] = CRGB::Black;
        delay(DELAY3);
    }

    FastLED.show();
    if (cycle == 3) {
        PALETTEFUNC();
    }
    cycle = ((cycle + 1) % 4);
}

    //send IR pulse
/*    for (unsigned long start_blink = millis(); millis() < start_blink + blink_length;) {
        if (micros() > previous_time + blink_period) {
            previous_time = micros();
            if (digitalRead(IR_TX_PIN) == LOW) {
                digitalWrite(IR_TX_PIN, HIGH);
            }
            else {
                digitalWrite(IR_TX_PIN, LOW);
            }
        }
    }
    Serial.println("IR pulse sent");
}
*/

// ISRs below here:

// void IR_TRIGGER(){
//     RESET = 1;
//     Serial.println("reset");
// }

// void BUTTON1(){
//     ButtonPress1 = 1;
// }

// void BUTTON2(){
//     ButtonPress2 = 1;
// }
