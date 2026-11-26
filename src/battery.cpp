#include <battery.h>

// Battery Level
static constexpr unsigned long BATTERY_CHECK_MS = 10000;
static unsigned long nextCheckAt = 0;
static int battery = -1;
static float smoothed = 0;

// Charging
static constexpr unsigned long PLUGGED_CHECK_MS = 1000;
static constexpr int USB_PRESENT_MV = 4000;
static unsigned long nextPluggedInCheckAt = 0;
static bool pluggedIn = false;

int batteryLevel() {
  unsigned long now = millis();

  if (now >= nextCheckAt) {
    nextCheckAt = now + BATTERY_CHECK_MS;
    int newReading = M5.Power.getBatteryLevel();
    bool plugged = isPluggedIn();

    if (battery < 0) {
      battery = newReading;
      smoothed = battery;
    } else {

      if (newReading >= 0) {
        smoothed = smoothed * 0.8 + newReading * 0.2;

        // Display only drops on battery and only rises while plugged in
        if ((smoothed < battery && !plugged) ||
            (smoothed > battery && plugged)) {
          battery = smoothed;
        }
      }
    }
  }

  return battery;
}

bool isPluggedIn() {
  unsigned long now = millis();

  if (now >= nextPluggedInCheckAt) {
    nextPluggedInCheckAt = now + PLUGGED_CHECK_MS;

    int voltage = M5.Power.getVBUSVoltage();

    pluggedIn = voltage > USB_PRESENT_MV;
  }

  return pluggedIn;
}
