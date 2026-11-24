#include "cloud_closed_png.h"
#include "cloud_eye_png.h"
#include "cloud_png.h"
#include <cloud.h>

// Cloud Peeking
constexpr unsigned long PEEK_MS = 1000;
constexpr unsigned long BLINK_TRANSITION_MS = 80;
unsigned long peekStartedAt = 0;
unsigned long nextPeekAt = 5000;

// Day time
constexpr uint16_t BG = lgfx::color565(110, 160, 220);

// Cloud Breathing
constexpr float BASE_SCALE = 3.0;
constexpr float BREATH_X = 0.15;
constexpr float BREATH_Y = 0.40;
constexpr float INHALE_S = 4.0;
constexpr float EXHALE_S = 6.0;

// Cloud Movement
constexpr float FLOAT_PERIOD_S = 4.0;
constexpr int FLOAT_AMPLITUDE = 10;

float breathAmount(float t) {
  float phase = fmod(t, INHALE_S + EXHALE_S); // seconds into current breath

  if (phase < INHALE_S) {
    float p = phase / INHALE_S;
    return (1 - cos(PI * p)) / 2;
  } else {
    float p = (phase - INHALE_S) / EXHALE_S;
    return 1 - (1 - cos(PI * p)) / 2;
  }
}
void drawCloud(M5Canvas &canvas) {

  float t = millis() / 1000.0;
  float floatWave = sin(t * 2 * PI / FLOAT_PERIOD_S);

  float breath = breathAmount(t);

  float scaleX = BASE_SCALE + breath * BREATH_X;
  float scaleY = BASE_SCALE + breath * BREATH_Y;

  // Current size on screen
  int w = 30 * scaleX;
  int h = 17 * scaleY;

  // Position
  int x = (M5.Display.width() - w) / 2;
  int baseY = (M5.Display.height() - h) / 2;
  int y = baseY + floatWave * FLOAT_AMPLITUDE;

  unsigned long now = millis();
  if (now >= nextPeekAt) {
    peekStartedAt = now;
    nextPeekAt = now + random(5000, 15000);
  }

  unsigned long elapsed = now - peekStartedAt;

  const unsigned char *img = cloud_png; // default: happy eyes
  unsigned int len = cloud_png_len;

  if (elapsed < BLINK_TRANSITION_MS) {
    img = cloud_closed_png;
    len = cloud_closed_png_len;
  } else if (elapsed < BLINK_TRANSITION_MS + PEEK_MS) {
    img = cloud_eye_png;
    len = cloud_eye_png_len;
  } else if (elapsed < BLINK_TRANSITION_MS * 2 + PEEK_MS) {
    img = cloud_closed_png;
    len = cloud_closed_png_len;
  }

  canvas.fillScreen(BG);
  canvas.drawPng(img, len, x, y, 0, 0, 0, 0, scaleX, scaleY);
  canvas.pushSprite(0, 0);
}
