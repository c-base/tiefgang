#include "FastLED.h"
#define NUM_LEDS 20
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2801>(leds, NUM_LEDS);
}

void loop() {

  showCase();
}

void showCase()
{
  int repeat = 10;

  tickTock(CRGB::Green, CRGB::Red, 20, repeat);
  tickTock(CRGB::Blue, CRGB::Purple, 5, repeat);

  oneLight(CRGB::Purple, 25, repeat);
  oneLight(CRGB::Blue, 50, repeat);

  rotate(CRGB::Aqua, CRGB::Blue, 1, repeat);
  rotate(CRGB::Red, CRGB::Blue, 3, repeat);
  rotate(CRGB::Aqua, CRGB::Orange, 5, repeat);

  quartettRotate(CRGB::Blue, CRGB::Purple, 3, repeat);
  quartettRotate(CRGB::Green, CRGB::Purple, 1, repeat);

  against(CRGB::Red, CRGB::Aqua, 50, repeat);
  against(CRGB::Red, CRGB::Blue, 30, repeat);

  followMe(CRGB::Green, CRGB::Yellow, 50, repeat);
  followMe(CRGB::Red, CRGB::Orange, 50, repeat);

  //rainbowBeat(CRGB::Blue, 30, 10, 255);
  //heartBeat(CRGB::Aqua, 300);
}

void heartBeat(const CRGB &color1, int delayDuration)
{
  beat(color1, 60, 0, 255, delayDuration);
}

void beat(const CRGB &color1, int bpm, int dimmest, int brightness, int delayDuration)
{
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = color1;
  }

  // set the brightness to a sine wave that moves with a beat
  uint8_t bright = beatsin8( bpm, dimmest, brightness);
  FastLED.setBrightness( bright );
  FastLED.show();
}

void rainbowBeat(const CRGB &color1, int bpm, int dimmest, int brightness)
{
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = color1;
  }

  // Put something visible on the LEDs
  static uint16_t hue16 = 0;
  hue16 += 9;
  fill_rainbow( leds, NUM_LEDS, hue16 / 256, 3);

  // set the brightness to a sine wave that moves with a beat
  uint8_t bright = beatsin8( bpm, dimmest, brightness);
  FastLED.setBrightness( bright );

  FastLED.show();

}

void oneLight(const CRGB &color1, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    for (int dot = 0; dot < NUM_LEDS; dot++) {

      int leFirstDot = ((dot)) % NUM_LEDS;

      leds[leFirstDot] = color1;

      FastLED.show();
      allOut();

      delay(delayDuration);
    }
  }
}

void quartettRotate(const CRGB &color1, const CRGB &color2, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    for (int dot = 0; dot < NUM_LEDS; dot++) {
      for (int dot2 = 0; dot2 < NUM_LEDS; dot2++) {

        int leFirstDot = (dot + (NUM_LEDS / 4 * 1)) % NUM_LEDS;
        int leSecondDot = (dot + (NUM_LEDS / 4 * 2)) % NUM_LEDS;
        int leThirdDot = (dot + (NUM_LEDS / 4 * 3)) % NUM_LEDS;
        int leFortthDot = (dot + (NUM_LEDS / 4 * 4)) % NUM_LEDS;


        leds[leFirstDot] = color1;
        leds[leSecondDot] = color2;
        leds[leThirdDot] = color1;
        leds[leFortthDot] = color2;

        FastLED.show();
        allOut();

        delay(delayDuration);
      }
    }
  }
}

void tickTock(const CRGB &color1, const CRGB &color2, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    for (int dot = 0; dot < NUM_LEDS; dot++) {
      for (int dot2 = 0; dot2 < NUM_LEDS; dot2++) {

        int leFirstDot = (dot2) % NUM_LEDS;
        int leSecondDot = (dot) % NUM_LEDS;
        int leThirdDot = (dot + 1) % NUM_LEDS;


        if (leFirstDot != leSecondDot) {
          leds[leSecondDot] = color2;
          leds[leThirdDot] = color2;
        }

        leds[leFirstDot] = color1;

        FastLED.show();
        allOut();

        delay(delayDuration);
      }
    }
  }
}

void followMe(const CRGB &color1, const CRGB &color2, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    for (int dot = 0; dot < NUM_LEDS; dot++) {

      int leFirstDot = ((dot * 2)) % NUM_LEDS;
      int leSecondDot = ((dot * 3)) % NUM_LEDS;


      leds[leFirstDot] = color1;
      leds[leSecondDot] = color2;
      FastLED.show();
      allOut();

      delay(delayDuration);
    }
  }
}

void against(const CRGB &color1, const CRGB &color2, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    for (int dot = 0; dot < NUM_LEDS; dot++) {

      leds[dot] = color1;
      leds[NUM_LEDS - dot] = color2;
      FastLED.show();
      allOut();
      delay(delayDuration);
    }
  }
}

void rotate(const CRGB &color1, const CRGB &color2, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    for (int dot = 0; dot < NUM_LEDS; dot++) {

      leds[dot] = color1;
      leds[(dot + (NUM_LEDS / 2)) % NUM_LEDS] = color2;

      FastLED.show();
      allOut();
      delay((dot ^ 2)*delayDuration);
    }
  }
}

void allOut() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Black;
  }
}


// Ripple
//
// Converted (but not optimized) from the Neopixel version https://gist.github.com/suhajdab/9716635
//
// Conversion by Andrew Tuline
//

void ripple() {

  int color;
  int center = 0;
  int step = -1; // need to be parameterized
  int maxSteps = 16;
  float fadeRate = 0.8;
  int diff;

  //background color
  uint32_t currentBg = random(256);
  uint32_t nextBg = currentBg;

  if (currentBg == nextBg) {
    nextBg = random(256);
  }
  else if (nextBg > currentBg) {
    currentBg++;
  } else {
    currentBg--;
  }
  for (uint16_t l = 0; l < NUM_LEDS; l++) {
    leds[l] = CHSV(currentBg, 255, 50);         // strip.setPixelColor(l, Wheel(currentBg, 0.1));
  }

  if (step == -1) {
    center = random(NUM_LEDS);
    color = random(256);
    step = 0;
  }

  if (step == 0) {
    leds[center] = CHSV(color, 255, 255);         // strip.setPixelColor(center, Wheel(color, 1));
    step ++;
  } else {
    if (step < maxSteps) {
      Serial.println(pow(fadeRate, step));

      leds[wrap(center + step)] = CHSV(color, 255, pow(fadeRate, step) * 255);
      leds[wrap(center - step)] = CHSV(color, 255, pow(fadeRate, step) * 255);
      if (step > 3) {
        leds[wrap(center + step - 3)] = CHSV(color, 255, pow(fadeRate, step - 2) * 255);
        leds[wrap(center - step + 3)] = CHSV(color, 255, pow(fadeRate, step - 2) * 255);
      }
      step ++;
    }
    else {
      step = -1;
    }
  }

  LEDS.show();
  delay(50);
}


int wrap(int step) {
  return step % NUM_LEDS;
}


void one_color_allHSV(int ahue, int abright) {                // SET ALL LEDS TO ONE COLOR (HSV)
  for (int i = 0 ; i < NUM_LEDS; i++ ) {
    leds[i] = CHSV(ahue, 255, abright);
  }
}

