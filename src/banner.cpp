#include <banner.h>
#include <battery.h>

constexpr uint16_t BANNER_BG = lgfx::color565(200, 170, 230);
constexpr uint16_t BANNER_FG = lgfx::color565(30, 50, 100);

static void drawBattery(M5Canvas &canvas, int w, int h) {
  int level = batteryLevel();
  String text;

  if (level < 0) {
    text = "--";
  } else {
    text = String(level) + "%";
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
