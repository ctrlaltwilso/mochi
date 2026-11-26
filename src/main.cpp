#include <M5Unified.h>
#include <banner.h>
#include <cloud.h>
#include <idle.h>

M5Canvas canvas(&M5.Display); // off-screen canvas

constexpr unsigned long FRAME_MS = 1000 / 15;

void setup() {

  M5.begin(); // runs at boot
  M5.Display.setBrightness(80);
  setCpuFrequencyMhz(160);

  // Portrait, set before drawing anything
  M5.Display.setRotation(0);
  M5.Display.setTextSize(2);

  // Create Canvas for render off screen
  canvas.createSprite(M5.Display.width(), M5.Display.height());

  cloudInit();
  bannerInit();
}

void loop() {
  unsigned long frameStart = millis();

  M5.update();
  bool justWoke = idleUpdate();

  if (M5.BtnA.wasPressed() && !justWoke) {
    unsigned long chipTime = millis() / 1000;

    M5.Display.fillScreen(TFT_BLUE);
    M5.Display.setCursor(0, 0);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLUE);
    M5.Display.println("button pressed");
    M5.Display.printf("Chip time: %lu\n", chipTime);
    delay(3000);
  }

  if (isAwake()) {
    drawCloud(canvas);
    drawBanner(canvas);
    canvas.pushSprite(0, 0);
  }

  // Set fps
  unsigned long elapsed = millis() - frameStart;
  if (elapsed < FRAME_MS) {
    delay(FRAME_MS - elapsed);
  }
}
