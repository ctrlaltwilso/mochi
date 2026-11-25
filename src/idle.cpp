#include <idle.h>

static bool screenAsleep = false;
static unsigned long lastActivityAt = 0;
static constexpr unsigned long IDLE_TIMEOUT_MS = 30000;

bool isAwake() { return !screenAsleep; }

static void sleepScreen() {
  M5.Display.sleep();
  screenAsleep = true;
}

static void wakeScreen() {
  M5.Display.wakeup();
  screenAsleep = false;
}

static bool anyButtonPressed() {
  for (int i = 0; i < 5; i++) {
    if (M5.getButton(i).wasPressed()) {
      return true;
    }
  }
  return false;
}

void idleUpdate() {
  unsigned long now = millis();
  bool buttonPressed = anyButtonPressed();

  if (buttonPressed) {
    lastActivityAt = now;
    if (screenAsleep) {
      wakeScreen();
    }
  }

  if (!screenAsleep && (now - lastActivityAt >= IDLE_TIMEOUT_MS)) {
    sleepScreen();
  }
}
