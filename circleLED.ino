#include "FastLED.h"
//#define NUM_LEDS 20
#define NUM_LEDS_PER_UNIT 20
#define NUM_UNITS 6
#define NUM_LEDS NUM_LEDS_PER_UNIT * NUM_UNITS

#define CLOCK loopcounter[unit]

CRGB leds[NUM_LEDS_PER_UNIT * NUM_UNITS];
int loopcounter[NUM_UNITS];

int center[NUM_UNITS];
int color[NUM_UNITS];
int tail[NUM_UNITS];

CRGB* unit_array[NUM_UNITS];


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2801>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_UNITS; i++) {
    loopcounter[i] = 0;
    tail[i] = 0;
    unit_array[i] = &leds[NUM_LEDS_PER_UNIT * i];
  }
}

void loop() {

  int repeat = NUM_LEDS_PER_UNIT * 20;
  int delayDuration = 30;

  //randomMulti(0);
  //randomMulti(1);

  smileCase(delayDuration, repeat);
  //hueHueHue(delayDuration, repeat);
  //ripple(delayDuration, repeat);
  //snake(10, delayDuration, repeat);
  //fire(delayDuration, repeat);
  //showCase(delayDuration, repeat);
}

void randomMulti(int unit) {
  lichtabsaugungMulti(unit);
  //int leFirstUnit = unit % NUM_LEDS_PER_UNIT;

  unit_array[random(NUM_UNITS) - 1][random(NUM_LEDS_PER_UNIT) - 1] = random(255);
  FastLED.show();

  loopcrement(unit);
  delay(100);
}

void smileCase(int delayDuration, int repeat) {

  for (int rep = 0; rep < repeat; rep++) {
    rotateMulti(-1, CRGB::Red);
    FastLED.show();
    delay(delayDuration);
  }
  
  for (int rep = 0; rep < repeat; rep++) {
    rippleMulti(-1, 0.9, 8);
    FastLED.show();
    delay(delayDuration);
  }
  
  for (int rep = 0; rep < repeat; rep++) {
    snakeMulti(-1, CRGB::Red, 5, 4000);
    FastLED.show();
    delay(0);
  }

  for (int rep = 0; rep < repeat; rep++) {
    fireMulti(-1, CRGB::Green, CRGB::Blue, 100);
    FastLED.show();
    delay(delayDuration);
  }

  for (int rep = 0; rep < repeat; rep++) {
    hueHueHueMulti(-1, CRGB::Red, 5, 3, 0, -5, 33, 255);
    FastLED.show();
    delay(delayDuration);
  }
}

void showCaseMulti(int delayDuration, int repeat)
{
  fire(delayDuration, repeat);
  snake(5, delayDuration, repeat);
  against(delayDuration, repeat);
  rotate(delayDuration, repeat);
  justOnExclamationMarkEleven(delayDuration);
  followMe(delayDuration, repeat);
  hueHueHue(delayDuration, repeat);
  ripple(delayDuration, repeat);

  for (int rep = 0; rep < repeat; rep++) {
    quartettRotateMulti(0, CRGB::Blue, CRGB::Red);
    fireMulti(1, CRGB::Green, CRGB::Blue, 100);
    FastLED.show();
    delay(delayDuration);
  }

  for (int rep = 0; rep < repeat; rep++) {
    singleColorMulti(0, CRGB::Green);
    singleColorMulti(1, CRGB::Aqua);
    FastLED.show();
    delay(delayDuration);
  }

}

void fire(int delayDuration, int repeat) {
  for (int rep = 0; rep < repeat; rep++) {
    fireMulti(0, CRGB::Green, CRGB::Blue, 100);
    fireMulti(1, CRGB::Red, CRGB::Black, 100);
    FastLED.show();
    delay(delayDuration);
  }
}

void fireMulti(int unit, const CRGB &color1, const CRGB &color2, int hue)
{
  if (unit < 0) {
    for (int unitCount = 0; unitCount < NUM_UNITS; unitCount++) {
      fireMulti(unitCount, color1, color2, hue);
    }
    return;
  }
  int half = (NUM_LEDS_PER_UNIT / 2);
  int leFirstDot = 0;
  int leSecondDot = half;

  leFirstDot = CLOCK % NUM_LEDS_PER_UNIT;
  leSecondDot = (NUM_LEDS_PER_UNIT - (CLOCK % NUM_LEDS_PER_UNIT));

  if (CLOCK < half) {
    unit_array[unit][leFirstDot] = color1;
    unit_array[unit][leSecondDot] = color1;
  }

  if (CLOCK >= half) {
    unit_array[unit][leFirstDot] = color2;
    unit_array[unit][leSecondDot] = color2;
  }
  loopcrement(unit);
}



void snake(int maxLength, int delayDuration, int repeat) {
  for (int rept = 0; rept < repeat; rept++) {
    snakeMulti(0, CRGB::Red, maxLength, 2500);
    snakeMulti(1, CRGB::Blue, maxLength, 4000);
    FastLED.show();
    delay(delayDuration);
  }
}

void snakeMulti(int unit, const CRGB &color1, int maxLength, int hue) {
  if (unit < 0) {
    for (int unitCount = 0; unitCount < NUM_UNITS; unitCount++) {
      snakeMulti(unitCount, color1, maxLength, hue);
    }
    return;
  }
  lichtabsaugungMulti(unit);
  int half = (NUM_LEDS_PER_UNIT / 2);
  int leFirstDot = CLOCK % NUM_LEDS_PER_UNIT;
  int leSecondDot = (half + CLOCK) % NUM_LEDS_PER_UNIT;

  if (CLOCK % 11 == 0) {
    tail[unit] = (tail[unit] + 1) % (maxLength);
  }
  for (int t = 0; t < tail[unit]; t++) {
    unit_array[unit][wrap(leFirstDot + t)] = CHSV(color1, 255, pow(t / 10, hue) * hue);
    unit_array[unit][wrap(leFirstDot + t)].setHue(hue - t * 20);
    unit_array[unit][wrap(leSecondDot + t)] = CHSV(color1, 255, pow(t / 10, hue) * hue);
    unit_array[unit][wrap(leSecondDot + t)].setHue(hue - t * 20);
  }
  loopcrement(unit);
}


void ripple(int delayDuration, int repeat) {

  for (int rep = 0; rep < repeat; rep++) {
    rippleMulti(0, 0.9, 8);
    rippleMulti(1, 0.9, 8);
    FastLED.show();
    delay(delayDuration);
  }
}

void rippleMulti(int unit, float fadeRate, int maxSteps)
{
  if (unit < 0) {
    for (int unitCount = 0; unitCount < NUM_UNITS; unitCount++) {
      rippleMulti(unitCount, fadeRate, maxSteps);
    }
    return;
  }
  int step = CLOCK % maxSteps;
  String output;
  String stringOne = "  ";


  if (step == 0) {
    center[unit] = random(NUM_LEDS_PER_UNIT);
    color[unit] = random(256);
    unit_array[unit][wrap(center[unit])] = CHSV(color[unit], 255, 255);
  }
  //output = step + stringOne + center[unit] + stringOne;
  //Serial.println(output);

  if (step > 0) {

    unit_array[unit][wrap(center[unit] + step)] = CHSV(color[unit], 255, pow(fadeRate, step) * 255);
    unit_array[unit][wrap(center[unit] - step)] = CHSV(color[unit], 255, pow(fadeRate, step) * 255);

    if (step % 2 == 0) {
      unit_array[unit][wrap(center[unit] + step - 2)] = CHSV(color[unit], 255, pow(fadeRate, step - 1) * 255);
      unit_array[unit][wrap(center[unit] - step + 2)] = CHSV(color[unit], 255, pow(fadeRate, step - 1) * 255);
    }
    if (step % 3 == 0) {
      unit_array[unit][wrap(center[unit] + step - 3)] = CHSV(color[unit], 255, pow(fadeRate, step - 3) * 255);
      unit_array[unit][wrap(center[unit] - step + 3)] = CHSV(color[unit], 255, pow(fadeRate, step - 3) * 255);
    }
  }

  loopcrement(unit);
}

int wrap(int step) {
  if (step < 0) {
    return (step + NUM_LEDS_PER_UNIT) % NUM_LEDS_PER_UNIT;
  }
  return step % NUM_LEDS_PER_UNIT;
}


void hueHueHue(int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    hueHueHueMulti(0, CRGB::Red, 5, 3, 0, -5, 33, 255);
    hueHueHueMulti(1, CRGB::Red, 5, 3, 0, -5, 33, 255);
    FastLED.show();
    delay(delayDuration);
  }
}

void hueHueHueMulti(int unit, const CRGB &color1, uint16_t gHue, uint8_t gHueDelta, int r, int b, int g, int mod)
{
  if (unit < 0) {
    for (int unitCount = 0; unitCount < NUM_UNITS; unitCount++) {
      hueHueHueMulti(unitCount, color1, gHue, gHueDelta, r, b, g, mod);
    }
    return;
  }
  if (CLOCK == 0) {
    for (int dot = 0; dot < NUM_LEDS_PER_UNIT; dot++) {
      unit_array[unit][dot] = color1;
    }
  }
  unit_array[unit][CLOCK].r = (unit_array[unit][CLOCK].r + r) % mod;
  unit_array[unit][CLOCK].g = (unit_array[unit][CLOCK].g + g) % mod;
  unit_array[unit][CLOCK].b = (unit_array[unit][CLOCK].b + b) % mod;

  loopcrement(unit);
}

void justOnExclamationMarkEleven(int delayDuration) {
  singleColorMulti(0, CRGB::White);
  singleColorMulti(1, CRGB::White);
  FastLED.show();
  delay(delayDuration);
}

void singleColorMulti(int unit, const CRGB &color1) {
  unit_array[unit][CLOCK] = color1;
  loopcrement(unit);
}

void rotate(int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    rotateMulti(0, CRGB::Purple);
    rotateMulti(1, CRGB::Blue);
    FastLED.show();
    delay(delayDuration);
  }
}

void rotateMulti(int unit, const CRGB &color1)
{
  if (unit < 0) {
    for (int unitCount = 0; unitCount < NUM_UNITS; unitCount++) {
      rotateMulti(unitCount, color1);
    }
    return;
  }
  lichtabsaugungMulti(unit);
  int leFirstDot = CLOCK % NUM_LEDS_PER_UNIT;
  unit_array[unit][leFirstDot] = color1;
  loopcrement(unit);

}

void quartettRotateMulti(int unit, const CRGB &color1, const CRGB &color2)
{
  lichtabsaugungMulti(unit);

  int leFirstDot = (CLOCK + (NUM_LEDS_PER_UNIT / 4 * 1)) % NUM_LEDS_PER_UNIT;
  int leSecondDot = (CLOCK + (NUM_LEDS_PER_UNIT / 4 * 2)) % NUM_LEDS_PER_UNIT;
  int leThirdDot = (CLOCK + (NUM_LEDS_PER_UNIT / 4 * 3)) % NUM_LEDS_PER_UNIT;
  int leFortthDot = (CLOCK + (NUM_LEDS_PER_UNIT / 4 * 4)) % NUM_LEDS_PER_UNIT;

  unit_array[unit][leFirstDot] = color1;
  unit_array[unit][leSecondDot] = color2;
  unit_array[unit][leThirdDot] = color1;
  unit_array[unit][leFortthDot] = color2;

  loopcrement(unit);
}

void followMe(int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    followMeMulti(0, CRGB::Aqua, CRGB::Blue);
    followMeMulti(1, CRGB::Red, CRGB::Green);
    FastLED.show();
    delay(delayDuration + 30);
  }
}

void followMeMulti(int unit, const CRGB &color1, const CRGB &color2)
{
  lichtabsaugungMulti(unit);

  int leFirstDot = ((CLOCK * 2)) % NUM_LEDS_PER_UNIT;
  int leSecondDot = ((CLOCK * 3)) % NUM_LEDS_PER_UNIT;
  unit_array[unit][leFirstDot] = color1;
  unit_array[unit][leSecondDot] = color2;

  loopcrement(unit);
}

void against(int delayDuration, int repeat)
{
  for (int rep = 0; rep < repeat; rep++) {
    againstMulti(0, CRGB::Red, CRGB::Aqua);
    againstMulti(1, CRGB::Red, CRGB::Blue);
    FastLED.show();
    delay(delayDuration);
  }
}

void againstMulti(int unit, const CRGB &color1, const CRGB &color2)
{
  lichtabsaugungMulti(unit);

  int leFirstDot = (CLOCK + 1) % NUM_LEDS_PER_UNIT;
  int leSecondDot = (NUM_LEDS_PER_UNIT - CLOCK) % NUM_LEDS_PER_UNIT;

  unit_array[unit][leFirstDot] = color1;
  unit_array[unit][leSecondDot] = color2;

  loopcrement(unit);
}

void loopcrement(int unit) {
  loopcounter[unit]++;
  if (loopcounter[unit] == NUM_LEDS_PER_UNIT) {
    loopcounter[unit] = 0;
  }
}

//void showCase(int delayDuration, int repeat)
//{

//
//  tickTock(CRGB::Green, CRGB::Blue, 60, 5);
//  tickTock(CRGB::Blue, CRGB::Purple, 60, 5);
//  tickTock(CRGB::Crimson, CRGB::Amethyst, 5);
//
//
//  //beat(CRGB::Aqua, 8 * 5, 10, 20, delayDuration);
//  //rainbowBeat(CRGB::Blue, 30, 10, 255);
//  //heartBeat(CRGB::Aqua, 300);
//}






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

void tickTockMulti(int unit, const CRGB &color1, const CRGB &color2, int delayDuration, int repeat)
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

void lichtabsaugung() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Black;
  }
}

void lichtabsaugungMulti(int unit) {
  for (int dot = 0; dot < NUM_LEDS_PER_UNIT; dot++) {
    unit_array[unit][dot] = CRGB::Black;
  }
  FastLED.show();
}







