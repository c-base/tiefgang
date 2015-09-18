#include "FastLED.h"
//#define NUM_LEDS 20
#define NUM_LEDS_PER_UNIT 20
#define NUM_UNITS 2
#define NUM_LEDS NUM_LEDS_PER_UNIT * NUM_UNITS


CRGB leds[NUM_LEDS_PER_UNIT * NUM_UNITS];
int loopcounter[NUM_UNITS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2801>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_UNITS; i++) {
    loopcounter[i] = 0;
  }

}

void loop() {

  int repeat = 20;
  int delayDuration = 100;

  showCaseMulti(delayDuration, repeat);
  //showCase(delayDuration, repeat);

}

void showCaseMulti(int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    showCaseMultiOne(delayDuration);

  }

  for (int rep = 0; rep < repeat; rep++) {
    showCaseMultiTwo(delayDuration);
  }

  //
  //unit = 1;
  //quartettRotateMulti(unit, CRGB::Blue, CRGB::Red);
  //FastLED.show();
  //delay(delayDuration);

}
void showCaseMultiOne(int delayDuration) {
  singleColorMulti(1, CRGB::Blue);
  quartettRotateMulti(0, CRGB::Blue, CRGB::Red);
  FastLED.show();
  delay(delayDuration);
}


void showCaseMultiTwo(int delayDuration) {
  quartettRotateMulti(0, CRGB::Blue, CRGB::Red);
  againstMulti(1, CRGB::Red, CRGB::Aqua, 50);
  FastLED.show();
  delay(delayDuration);
}

void loopcrement(int unit) {
  loopcounter[unit]++;
  if (loopcounter[unit] == NUM_LEDS_PER_UNIT) {
    loopcounter[unit] = 0;
  }
}

void singleColorMulti(int unit, const CRGB &color1) {

  int dot = loopcounter[unit] + (unit * NUM_LEDS_PER_UNIT);
  leds[dot] = color1;

  loopcrement(unit);
}

void lichtabsaugungMulti(int unit) {
  int maximum = NUM_LEDS_PER_UNIT * (unit + 1);
  int offset = NUM_LEDS_PER_UNIT * unit;
  for (int dot = offset; dot < maximum; dot++) {
    leds[dot] = CRGB::Black;
  }
}

void quartettRotateMulti(int unit, const CRGB &color1, const CRGB &color2)
{
  lichtabsaugungMulti(unit);

  int dot = loopcounter[unit];
  int offset = (unit * NUM_LEDS_PER_UNIT);

  int leFirstDot = (dot + (NUM_LEDS_PER_UNIT / 4 * 1)) % NUM_LEDS_PER_UNIT + offset;
  int leSecondDot = (dot + (NUM_LEDS_PER_UNIT / 4 * 2)) % NUM_LEDS_PER_UNIT + offset;
  int leThirdDot = (dot + (NUM_LEDS_PER_UNIT / 4 * 3)) % NUM_LEDS_PER_UNIT + offset;
  int leFortthDot = (dot + (NUM_LEDS_PER_UNIT / 4 * 4)) % NUM_LEDS_PER_UNIT + offset;

  leds[leFirstDot] = color1;
  leds[leSecondDot] = color2;
  leds[leThirdDot] = color1;
  leds[leFortthDot] = color2;

  loopcrement(unit);
}

void showCase(int delayDuration, int repeat)
{
  hueHueHue(CRGB::Red,   5, 3, 10, 20, 0, -5, 33, 255);
  hueHueHue(CRGB::White, 5, 3, 10, 20, 0, -50, 0, 255);
  hueHueHue(CRGB::White, 5, 3, 10, 20, 0, -50, -50, 255);
  hueHueHue(CRGB::White, 5, 3, 10, 20, -100, 10, -1, 55);
  hueHueHue(CRGB::Blue, 5, 39, 10, 20, -100, 10, -1, 105);

  ripple(0.9, 4, 100, 50);

  snakes(CRGB::Red, 2500, 100, 1);
  snakes(CRGB::Red, 2500, 50, 1);
  snakes(CRGB::Red, 2500, 10, 1);
  snakes(CRGB::Red, 2500, 10, 1);
  snakes(CRGB::Red, 2500, 10, 1);


  fire(CRGB::Red, 10, 10, 1);
  fire(CRGB::Red, 20, 50, 1);
  fire(CRGB::Blue, 30, 100, 1);
  fire(CRGB::Green, 40, 120, 1);

  tickTock(CRGB::Green, CRGB::Blue, 60, 5);
  tickTock(CRGB::Blue, CRGB::Purple, 60, 5);
  tickTock(CRGB::Crimson, CRGB::Amethyst, delayDuration, 5);

  oneLight(CRGB::Purple, 25, 5);
  oneLight(CRGB::Blue, 50, 5);

  rotate(CRGB::Aqua, CRGB::Blue, 1, 10);
  rotate(CRGB::Red, CRGB::Blue, 3, 10);
  rotate(CRGB::Aqua, CRGB::Orange, 5, 10);

  quartettRotate(CRGB::Blue, CRGB::Purple, 3, repeat);
  quartettRotate(CRGB::Green, CRGB::Purple, 1, repeat);
  quartettRotate(CRGB::Green, CRGB::Purple, 1, repeat);

  against(CRGB::Red, CRGB::Aqua, 50, repeat);
  against(CRGB::Red, CRGB::Blue, 30, repeat);

  followMe(CRGB::Green, CRGB::Yellow, 50, repeat);
  followMe(CRGB::Red, CRGB::Orange, 50, repeat);
  followMe(CRGB::Purple, CRGB::Green, 50, repeat);

  justOnExclamationMarkEleven(200);
  singleColor(CRGB::Aqua, 2000);


  //beat(CRGB::Aqua, 8 * 5, 10, 20, delayDuration);
  //rainbowBeat(CRGB::Blue, 30, 10, 255);
  //heartBeat(CRGB::Aqua, 300);
}

void greyGode(const CRGB &color1, int tail, int hue, int delayDuration, int repeat)
{
  // ....
}

void snakesOnARow(const CRGB &color1, int hue, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    snake(CRGB::Red, rep, hue, delayDuration, repeat);
  }
}

void snakes(const CRGB &color1, int hue, int delayDuration, int repeat)
{
  snake(CRGB::Red, 1, hue, delayDuration, repeat);
  snake(CRGB::Red, 2, hue, delayDuration, repeat);
  snake(CRGB::Red, 3, hue, delayDuration, repeat);
  snake(CRGB::Red, 4, hue, delayDuration, repeat);
  snake(CRGB::Red, 5, hue, delayDuration, repeat);
  snake(CRGB::Red, 6, hue, delayDuration, repeat);
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
      lichtabsaugung();
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
    lichtabsaugung();
  }
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
  lichtabsaugung();
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
      lichtabsaugung();

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
        lichtabsaugung();

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
      lichtabsaugung();

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
      lichtabsaugung();

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
      lichtabsaugung();
      delay(delayDuration);
    }
  }
}

void againstMulti(int unit, const CRGB &color1, const CRGB &color2, int delayDuration)
{
  lichtabsaugungMulti(unit);
  int dot = loopcounter[unit];
  int offset = NUM_LEDS_PER_UNIT * unit;


  int leFirstDot = (dot + 1) % NUM_LEDS_PER_UNIT + offset;
  int leSecondDot = (NUM_LEDS - dot) % NUM_LEDS_PER_UNIT + offset;

  leds[leFirstDot] = color1;
  leds[leSecondDot] = color2;

  loopcrement(unit);

}

void rotate(const CRGB &color1, const CRGB &color2, int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    for (int dot = 0; dot < NUM_LEDS; dot++) {

      leds[dot] = color1;
      leds[(dot + (NUM_LEDS / 2)) % NUM_LEDS] = color2;

      FastLED.show();
      lichtabsaugung();
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
void ripple(float fadeRate, int maxSteps, int delayDuration, int repeat)
{
  //  maxSteps = 10;
  //  delayDuration = 20;
  //  fadeRate = 0.9;
  //  repeat = 50;
  int color;
  int center;

  for (int rep = 0; rep < repeat; rep++) {
    center = wrap(random(NUM_LEDS));
    color = random(256);
    Serial.println(color);
    for (int step = 0; step < maxSteps; step++) {

      if (step == 0) {
        leds[center] = CHSV(color, 255, 255);
      }
      if (step > 0) {
        leds[wrap(center + step)] = CHSV(color, 255, pow(fadeRate, step) * 255);
        leds[wrap(center - step)] = CHSV(color, 255, pow(fadeRate, step) * 255);

        if (step % 2 == 0) {
          leds[wrap(center + step - 2)] = CHSV(color, 255, pow(fadeRate, step - 1) * 255);
          leds[wrap(center - step + 2)] = CHSV(color, 255, pow(fadeRate, step - 1) * 255);
        }
        if (step % 3 == 0) {
          leds[wrap(center + step - 3)] = CHSV(color, 255, pow(fadeRate, step - 2) * 255);
          leds[wrap(center - step + 3)] = CHSV(color, 255, pow(fadeRate, step - 2) * 255);
        }
      }
      LEDS.show();
      delay(delayDuration);
      //lichtabsaugung();
    }
  }
  lichtabsaugung();
  LEDS.show();
}

void lichtabsaugung() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Black;
  }
}


int wrap(int step) {
  return step % NUM_LEDS;
}


