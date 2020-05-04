#include <Adafruit_NeoPixel.h>

#define PIN 13
#define NUMPIXELS 40

#define switchMode 12

byte helix[NUMPIXELS / 2];

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 1000

void setup() {
  pinMode(switchMode, INPUT);

  fillHelixArray();

  pixels.begin();
  pixels.clear();
}

void loop() {
  if (digitalRead(switchMode) == HIGH) {  //Rainbow Mode
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
      for (int i = 0; i < NUMPIXELS / 2; i++) {
        int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
        pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
        pixels.setPixelColor((NUMPIXELS - 1 - i), pixels.gamma32(pixels.ColorHSV(pixelHue)));
      }
    }
  } else if (digitalRead(switchMode) == LOW) {  //DNA Mode
    updateHelixArray();
    parseHelixArray();
  }

  pixels.show();
}

void fillHelixArray () {
  for (int i = 0; i < sizeof(helix); i++) {
    helix[i] = random(0, 3);
  }
}

void updateHelixArray () {
  for (int i = 0; i < (sizeof(helix) - 1); i++) {
    helix[(i + 1)] = helix[i];
  }

  helix[0] = random(0, 3);
}

void parseHelixArray () {
  for (int i = 0; i < sizeof(helix); i++) {
    if (helix[i] == 0) {
      pixels.setPixelColor(i, 255, 0, 0);
      pixels.setPixelColor((NUMPIXELS - 1 - i), 0, 0, 255);
    } else if (helix[i] == 1) {
      pixels.setPixelColor(i, 0, 255, 0);
      pixels.setPixelColor((NUMPIXELS - 1 - i), 255, 255, 0);
    } else if (helix[i] == 2) {
      pixels.setPixelColor(i, 0, 0, 255);
      pixels.setPixelColor((NUMPIXELS - 1 - i), 255, 0, 0);
    } else if (helix[i] == 3) {
      pixels.setPixelColor(i, 255, 255, 0);
      pixels.setPixelColor((NUMPIXELS - 1 - i), 0, 255, 0);
    }
  }
}
