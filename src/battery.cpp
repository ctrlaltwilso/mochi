#include <battery.h>

// Cycle Time
constexpr unsigned long CHECK_INTERVAL_MS = 10000;
unsigned long nextCheckAt = 0;
int battery = -1;
float smoothed = 0;

int batteryLevel() {
  unsigned long now = millis();

  if (now >= nextCheckAt) {
    nextCheckAt = now + CHECK_INTERVAL_MS;

    if (battery < 0) {
      battery = M5.Power.getBatteryLevel();
      smoothed = battery;
    } else {
      int newReading = M5.Power.getBatteryLevel();

      if (newReading >= 0) {
        smoothed = smoothed * 0.8 + newReading * 0.2;
        battery = smoothed;
      }
    }
  }

  return battery;
}
