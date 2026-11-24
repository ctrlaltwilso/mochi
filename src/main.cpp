#include <M5Unified.h>
#include <cloud.h>

M5Canvas canvas(&M5.Display); // off-screen canvas

void setup() {

  M5.begin(); // runs at boot

  // Portrait, set before drawing anything
  M5.Display.setRotation(0);
  M5.Display.setTextSize(2);

  // Create Canvas for render off screen
  canvas.createSprite(M5.Display.width(), M5.Display.height());

  drawCloud(canvas);
}

void loop() {
  M5.update();

  if (M5.BtnA.wasPressed()) {
    unsigned long chipTime = millis() / 1000;

    M5.Display.fillScreen(TFT_BLUE);
    M5.Display.setCursor(0, 0);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLUE);
    M5.Display.println("button pressed");
    M5.Display.printf("Chip time: %lu\n", chipTime);
    delay(3000);
  }
  drawCloud(canvas);
}
