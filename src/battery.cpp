#include <battery.h>

// Battery Level
constexpr unsigned long BATTERY_CHECK_MS = 10000;
unsigned long nextCheckAt = 0;
int battery = -1;
float smoothed = 0;

// Charging
constexpr unsigned long PLUGGED_CHECK_MS = 1000;
constexpr int USB_PRESENT_MV = 4000;
unsigned long nextPluggedInCheckAt = 0;
bool pluggedIn = false;

int batteryLevel() {
  unsigned long now = millis();

  if (now >= nextCheckAt) {
    nextCheckAt = now + BATTERY_CHECK_MS;
    int newReading = M5.Power.getBatteryLevel();
    bool pluggedIn = isPluggedIn();

    if (battery < 0) {
      battery = newReading;
      smoothed = battery;
    } else {

      if (newReading >= 0) {
        smoothed = smoothed * 0.8 + newReading * 0.2;

        // Battery level only increases while pluggedIn
        if ((smoothed < battery && pluggedIn) ||
            (smoothed > battery && pluggedIn)) {
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
