#include "cloud_closed_png.h"
#include "cloud_eye_png.h"
#include "cloud_png.h"
#include <cloud.h>

// Cloud canvas
static M5Canvas cloudSprite;
static M5Canvas cloudEyeSprite;
static M5Canvas cloudClosedSprite;

static constexpr unsigned int CLOUD_W = 30;
static constexpr unsigned int CLOUD_H = 17;

// Cloud Peeking
static constexpr unsigned long PEEK_MS = 1000;
static constexpr unsigned long BLINK_TRANSITION_MS = 80;
static unsigned long peekStartedAt = 0;
static unsigned long nextPeekAt = 5000;

// Day time
static constexpr uint16_t BG = lgfx::color565(110, 160, 220);

// Cloud Breathing
static constexpr float BASE_SCALE = 3.0;
static constexpr float BREATH_X = 0.15;
static constexpr float BREATH_Y = 0.40;
static constexpr float INHALE_S = 4.0;
static constexpr float EXHALE_S = 6.0;

// Cloud Movement
static constexpr float FLOAT_PERIOD_S = 4.0;
static constexpr int FLOAT_AMPLITUDE = 10;

void cloudInit() {
  cloudSprite.createSprite(CLOUD_W, CLOUD_H);
  cloudSprite.fillScreen(TFT_TRANSPARENT);
  cloudSprite.drawPng(cloud_png, cloud_png_len);

  cloudEyeSprite.createSprite(CLOUD_W, CLOUD_H);
  cloudEyeSprite.fillScreen(TFT_TRANSPARENT);
  cloudEyeSprite.drawPng(cloud_eye_png, cloud_eye_png_len);

  cloudClosedSprite.createSprite(CLOUD_W, CLOUD_H);
  cloudClosedSprite.fillScreen(TFT_TRANSPARENT);
  cloudClosedSprite.drawPng(cloud_closed_png, cloud_closed_png_len);
}

static float breathAmount(float t) {
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
  M5Canvas *sprite = &cloudSprite;

  float t = millis() / 1000.0;
  float floatWave = sin(t * 2 * PI / FLOAT_PERIOD_S);

  float breath = breathAmount(t);

  float scaleX = BASE_SCALE + breath * BREATH_X;
  float scaleY = BASE_SCALE + breath * BREATH_Y;

  // Position
  float x = canvas.width() / 2.0f;
  float baseY = canvas.height() / 2.0f;
  float y = baseY + floatWave * FLOAT_AMPLITUDE;

  unsigned long now = millis();
  if (now >= nextPeekAt) {
    peekStartedAt = now;
    nextPeekAt = now + random(5000, 15000);
  }

  unsigned long elapsed = now - peekStartedAt;

  if (elapsed < BLINK_TRANSITION_MS) {
    sprite = &cloudClosedSprite;
  } else if (elapsed < BLINK_TRANSITION_MS + PEEK_MS) {
    sprite = &cloudEyeSprite;
  } else if (elapsed < BLINK_TRANSITION_MS * 2 + PEEK_MS) {
    sprite = &cloudClosedSprite;
  }

  canvas.fillScreen(BG);
  sprite->pushRotateZoom(&canvas, x, y, 0, scaleX, scaleY, TFT_TRANSPARENT);
}
