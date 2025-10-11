# ESP32 NTP Clock Framework

[](https://opensource.org/licenses/MIT)

A flexible, object-oriented C++ framework for building feature-rich, network-connected clocks on the ESP32 platform.

This library provides a complete "engine" for handling WiFi connectivity, time synchronization, display management, and web-based configuration. By using this framework, you can create a new, custom clock application with minimal boilerplate code, focusing only on your specific hardware and desired features.

-----

## ✨ Core Features

  * **Modular Architecture:** Cleanly separates core logic from application-specific hardware and configuration.
  * **State Machine Driven:** Manages the clock's state (connecting, syncing, running, AP mode) with a robust Finite State Machine.
  * **Abstracted Display & Animations:** Supports different display hardware through the `IDisplayDriver` interface and includes a `DisplayManager` for handling complex animations.
  * **Scene Management:** A data-driven `SceneManager` cycles through a user-defined "playlist" of what to display (e.g., time, date, weather).
  * **Web Configuration:** Includes a built-in captive portal (`BaseAccessPointManager`) for configuring WiFi, timezone, and other settings via a web browser.
  * **Robust Boot Logic:** Provides a `BootManager` to handle features like double-reset detection for entering configuration mode.

-----

## 🏛️ Architecture Overview

The framework is designed to separate the generic "engine" (the library) from the specific "application" (your clock).

### The `BaseNtpClockApp` Engine

The core of the framework is the `BaseNtpClockApp` class. An application inherits from this class to automatically get the main `setup()` and `loop()` logic, the state machine, and all the core managers.

### Interfaces (`IBaseClock` & `IWeatherClock`)

To connect the engine to the application, the framework uses interfaces. Your application must "implement" these interfaces, which acts as a contract.

  * **`IBaseClock`**: This is the minimum contract for any clock. It requires functions for getting hardware, WiFi credentials, etc.
  * **`IWeatherClock`**: This is an optional, extended interface for clocks that support weather features.

### Hardware Abstraction (`IDisplayDriver`)

The library can work with any display hardware. All you need to do is create a driver class that implements the `IDisplayDriver` interface. The `ESP32NTPClock_Drivers` repository provides examples of this.

-----

## 🚀 How to Use (Quick Start)

Here is how to build a new clock using the framework:

1.  **Create Your Application Class:** Inherit from `BaseNtpClockApp` and the required interfaces (e.g., `IWeatherClock` if you need weather).

2.  **Implement the Interface:** Provide implementations for all the pure virtual functions from the interface(s). This is where you connect your specific hardware and preferences.

3.  **Define a Scene Playlist:** Create an array of `DisplayScene` structs that defines what your clock will show and with which animations.

4.  **Instantiate and Run:** Create a global instance of your app and call its `setup()` and `loop()` from the main Arduino functions.

**Example (`MyClock.ino`):**

```cpp
#include <ESP32NTPClock.h>
#include <base_ntp_clock_app.h>
#include <MyDisplayDriver.h> // Your custom driver

// Define preferences and AP Manager
// ...

// Define your scene playlist
static const DisplayScene scenePlaylist[] = { /* ... */ };

// 1. Create your application class
class MyClockApp : public BaseNtpClockApp {
public:
    MyClockApp() : /* Initialize your hardware */ {
        // Assign pointers to base class
        _prefs = &_myPrefs;
        _apManager = &_myApManager;
    }

    void setup() override {
        // Initialize your hardware
        _display.begin();
        // Call the base engine's setup
        BaseNtpClockApp::setup();
        // Configure the scene manager
        _sceneManager->setup(scenePlaylist, numScenes);
    }
    
    // 2. Implement all functions from IBaseClock
    // ...
private:
    MyDisplayDriver _display;
    MyPreferences _myPrefs;
    MyApManager _myApManager;
    // ...
};

// 4. Instantiate and Run
MyClockApp app;

void setup() {
    app.setup();
}

void loop() {
    app.loop();
}
```

-----

## 📚 Dependencies

The `ESP32NTPClock` library requires the following third-party libraries to be installed:

  * [ESP Async WebServer](https://github.com/me-no-dev/ESPAsyncWebServer) & [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
  * [SimpleFSM](https://www.google.com/search?q=https://github.com/tockn/SimpleFSM)

-----

## 💡 Examples

The library includes the following examples to demonstrate its use:

  * **`bare_bones_clock`**: A minimal clock that only shows time and date, demonstrating the simplest possible implementation.
  * **`bubble_led_clock`**: A full-featured clock with an HT16K33 display, weather, and RTC.
  * **`gustav_clock`**: A full-featured clock with a VFD display and MAX6921.

-----

## 📜 License

This project is licensed under the MIT License.