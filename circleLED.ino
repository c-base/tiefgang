#include "FastLED.h"
#define NUM_LEDS 20
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2801>(leds, NUM_LEDS);
}

void loop() {

  int repeat = 1;
  int delayDuration = 50;

  showCase(delayDuration, repeat);
}

void snakesOnARow(const CRGB &color1, int hue, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    snake(CRGB::Red, rep, hue, delayDuration, repeat);
  }
}

void snake(const CRGB &color1, int tail, int hue, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {

    int half = (NUM_LEDS / 2);
    int leFirstDot = 0;
    int leSecondDot = half;

    for (int dot = 0; dot <= half; dot++) {

      leFirstDot = (dot);
      leSecondDot = (half + dot);

      for (int t = 0; t < tail; t++) {
        leds[wrap(leFirstDot + t)] = CHSV(color1, 255, pow(t / 10, hue) * hue);
        leds[wrap(leFirstDot + t)].setHue(hue - t * 20);
        leds[wrap(leSecondDot + t)] = CHSV(color1, 255, pow(t / 10, hue) * hue);
        leds[wrap(leSecondDot + t)].setHue(hue - t * 20);
      }

      FastLED.show();
      delay(delayDuration);
      allOut();
    }

  }
}

void fire(const CRGB &color1, int hue, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {

    int half = (NUM_LEDS / 2);
    int leFirstDot = 0;
    int leSecondDot = half;

    for (int dot = 0; dot < NUM_LEDS; dot++) {

      if (dot <= half) {
        leFirstDot = (dot);

        leSecondDot = (NUM_LEDS - dot);
      }

      leds[leFirstDot] = color1;
      leds[leFirstDot].setHue(hue);

      leds[leSecondDot] = color1;
      leds[leSecondDot].setHue(hue);
      FastLED.show();

      delay(delayDuration);
    }
    allOut();
  }
}


void showCase(int delayDuration, int repeat)
{
  hueHueHue(CRGB::Red, 5, 3, delayDuration, repeat, 0, -5, 33, 255);
  hueHueHue(CRGB::White, 5, 3, delayDuration, repeat, 0, -50, 0, 255);
  hueHueHue(CRGB::White, 5, 3, delayDuration, repeat, 0, -50, -50, 255);
  hueHueHue(CRGB::White, 5, 3, delayDuration, repeat, -100, 10, -1, 55);

  ripple(0.8, 2, 700, repeat);
  ripple(0.9, 8, 200, repeat); // <-
  ripple(1, 4, 200, repeat);
  ripple(0.3, 4, 200, repeat);
  ripple(0.8, 9, 200, repeat);

  snake(CRGB::Red, 1, 2500, delayDuration, repeat);
  snake(CRGB::Red, 2, 2500, delayDuration, repeat);
  snake(CRGB::Red, 3, 2500, delayDuration, repeat);
  snake(CRGB::Red, 4, 2500, delayDuration, repeat);
  snake(CRGB::Red, 5, 2500, delayDuration, repeat);
  snake(CRGB::Red, 6, 2500, delayDuration, repeat);

  tickTock(CRGB::Green, CRGB::Blue, 40, repeat);
  tickTock(CRGB::Blue, CRGB::Purple, 5, repeat);
  tickTock(CRGB::Crimson, CRGB::Amethyst, delayDuration, repeat);

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

  justOnExclamationMarkEleven(200);
  singleColor(CRGB::Aqua, 10);


  //beat(CRGB::Aqua, 8 * 5, 10, 20, delayDuration);
  //rainbowBeat(CRGB::Blue, 30, 10, 255);
  //heartBeat(CRGB::Aqua, 300);
}

void hueHueHue(const CRGB &color1, uint16_t gHue, uint8_t  gHueDelta, int delayDuration, int repeat, int r, int b, int g, int mod)
{
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = color1;
  }
  for (int rep = 0; rep < repeat; rep++) {
    gHue += gHueDelta; // compute new hue
    for (int dot = 0; dot < NUM_LEDS; dot++) {

      leds[dot].r = (leds[dot].r + r) % mod;
      leds[dot].g = (leds[dot].g + g) % mod;
      leds[dot].b = (leds[dot].b + b) % mod;
      FastLED.show();
      delay(delayDuration);
    }
  }
}

void justOnExclamationMarkEleven(int delayDuration) {
  singleColor(CRGB::White, delayDuration);
}

void singleColor(const CRGB &color1, int delayDuration) {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = color1;
  }
  FastLED.show();
  delay(delayDuration);
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
  for (int dot = 0; dot < repeat; dot++) {
    for (int dot2 = 0; dot2 < NUM_LEDS; dot2++) {

      int leFirstDot = (dot2) % NUM_LEDS;
      int leSecondDot = (dot) % NUM_LEDS;
      int leThirdDot = (dot + 1) % NUM_LEDS;

      if (leFirstDot != leSecondDot) {
        leds[leSecondDot] = color2;
      }
      if (leFirstDot != leThirdDot) {
        leds[leThirdDot] = color2;
      }

      leds[leFirstDot] = color1;

      FastLED.show();
      allOut();

      delay(delayDuration);
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

      int leFirstDot = (dot + 1) % NUM_LEDS;
      int leSecondDot = (NUM_LEDS - dot) % NUM_LEDS;

      leds[leFirstDot] = color1;
      leds[leSecondDot] = color2;

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

// Ripple
//
// Converted (but not optimized) from the Neopixel version https://gist.github.com/suhajdab/9716635
//
// Conversion by Andrew Tuline
//
void ripple(float fadeRate, int maxSteps, int delayDuration, int repeat) {

  int color;
  int center;

  for (int rep = 0; rep < repeat; rep++) {
    center = wrap(random(NUM_LEDS));
    color = random(256);

    for (int step = 0; step < maxSteps; step++) {

      if (step == 0) {
        leds[center] = CHSV(color, 255, 255);
      }
      if (step < maxSteps) {
        leds[wrap(center + step)] = CHSV(color, 255, pow(fadeRate, step) * 255);
        leds[wrap(center - step)] = CHSV(color, 255, pow(fadeRate, step) * 255);

        if (step > 3) {
          leds[wrap(center + step - 3)] = CHSV(color, 255, pow(fadeRate, step - 2) * 255);
          leds[wrap(center - step + 3)] = CHSV(color, 255, pow(fadeRate, step - 2) * 255);
        }
      }

      LEDS.show();
      delay(delayDuration);

    }
  }
}

void allOut() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Black;
  }
}


int wrap(int step) {
  return step % NUM_LEDS;
}


