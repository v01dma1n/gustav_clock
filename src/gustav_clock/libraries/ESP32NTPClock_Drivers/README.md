# ESP32 NTP Clock - Display Drivers

[](https://opensource.org/licenses/MIT)

This repository is a collection of hardware-specific display drivers designed to work with the **[ESP32NTPClock framework](https://www.google.com/search?q=https://github.com/v01dma1n/ESP32NTPClock)**.

Each driver in this collection implements the `IDisplayDriver` interface from the core library. This allows the main clock engine to remain generic while supporting a wide variety of display technologies like 7-segment LEDs and VFDs.

## ⚠️ Prerequisites

This library is an add-on and **requires** the core `ESP32NTPClock` library to be installed.

## 📦 Included Drivers

This collection currently includes the following drivers:

### HT16K33 7-Segment LED Driver

A driver for common I2C-based 7-segment LED displays that use the Holtek HT16K33 chip.

**Usage:**

```cpp
#include <ESP32NTPClock_HT16K33.h>

// For an 8-digit display at the default I2C address of 0x70
DispDriverHT16K33 myDisplay(0x70, 8);
```

### MAX6921 VFD Driver

A driver for Vacuum Fluorescent Displays (VFD) that use the Maxim MAX6921 chip over the SPI bus.

**Usage:**

```cpp
#include <ESP32NTPClock_MAX6921.h>

// For a 12-digit VFD using standard VSPI pins
// DispDriverMAX6921(num_digits, SCLK, MISO, MOSI, SS, BLANK);
DispDriverMAX6921 myDisplay(12, 18, 19, 23, 5, 0);
```

-----

## 🚀 How to Use a Driver

To use one of these drivers in your clock project:

1.  Install this library (`ESP32NTPClock_Drivers`) and the core `ESP32NTPClock` library.
2.  In your main `.ino` or application header file, include the specific driver header you need (e.g., `#include <ESP32NTPClock_HT16K33.h>`).
3.  In your application class, create a member variable for the driver object, passing the correct hardware parameters to its constructor.
4.  Pass a reference to your driver object to the `DisplayManager` constructor. The `DisplayManager` will then use your specific hardware to render all animations and scenes.

-----

## ➕ Adding a New Driver

You can easily add your own driver to this collection by:

1.  Creating a new header and source file for your driver class.
2.  Ensuring your class inherits from `public IDisplayDriver`.
3.  Providing implementations for all the pure virtual functions defined in the `IDisplayDriver` interface.

-----

## 📜 License

This project is licensed under the MIT License.