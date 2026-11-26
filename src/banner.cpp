#include <banner.h>
#include <battery.h>
#include <lightning_png.h>

static M5Canvas lightningSprite;

static constexpr unsigned int LIGHTNING_W = 5;
static constexpr unsigned int LIGHTNING_H = 8;
static constexpr int BOLT_SCALE = 2;

static constexpr uint16_t BANNER_BG = lgfx::color565(200, 170, 230);
static constexpr uint16_t BANNER_FG = lgfx::color565(30, 50, 100);

void bannerInit() {
  lightningSprite.createSprite(LIGHTNING_W, LIGHTNING_H);
  lightningSprite.fillScreen(TFT_TRANSPARENT);
  lightningSprite.drawPng(lightning_png, lightning_png_len);
}

static void drawBattery(M5Canvas &canvas, int w, int h) {
  int level = batteryLevel();
  bool pluggedIn = isPluggedIn();
  String text;

  if (level < 0) {
    text = "--";
  } else {
    text = String(level) + "%";
  }

  int textLeft = w - 4 - canvas.textWidth(text);
  int boltX = textLeft - 3 - LIGHTNING_W * BOLT_SCALE / 2;

  if (pluggedIn) {
    lightningSprite.pushRotateZoom(&canvas, boltX, h / 2.0f, 0, BOLT_SCALE,
                                   BOLT_SCALE, TFT_TRANSPARENT);
  }

  canvas.drawString(text, w - 4, h / 2);
}

void drawBanner(M5Canvas &canvas) {
  int w = canvas.width();
  int h = 20;

  canvas.fillRect(0, 0, w, h, BANNER_BG);
  canvas.setTextColor(BANNER_FG, BANNER_BG);
  canvas.setTextDatum(middle_right);
  canvas.setTextSize(2);
  drawBattery(canvas, w, h);
}
