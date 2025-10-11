#include "i2c_util.h"

#include <Arduino.h>

void i2c_bus_clear() {
    pinMode(SDA, INPUT_PULLUP);
    pinMode(SCL, INPUT_PULLUP);
    delay(5);
    for (int i = 0; i < 9; i++) {
        digitalWrite(SCL, HIGH);
        delay(5);
        digitalWrite(SCL, LOW);
        delay(5);
    }
}

