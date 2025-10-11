#include <ESP32NTPClock.h>
#include <ESP32NTPClock_HT16K33.h>
#include <base_ntp_clock_app.h>

// 1. DEFINE MINIMAL CONFIGURATION
struct BareConfig : public BaseConfig {};

class BarePreferences : public BasePreferences {
public:
    BarePreferences() : BasePreferences(config) {}
    BareConfig config;
};

class BareAccessPointManager : public BaseAccessPointManager {
public:
    BareAccessPointManager(BarePreferences& prefs) : BaseAccessPointManager(prefs) {}
};

// 2. DEFINE THE SCENE PLAYLIST
float getTimeData() { return 0; }
static const DisplayScene scenePlaylist[] = {
    {"Time", "%H.%M.%S", SLOT_MACHINE, false, 10000, 200, 50, getTimeData},
    {"Date", "%b %d %Y", SCROLLING, true, 7000, 300, 0, getTimeData},
};

static const int numScenes = sizeof(scenePlaylist) / sizeof(DisplayScene);

// 3. CREATE THE APPLICATION CLASS
class BareBonesClockApp : public BaseNtpClockApp {
public:
    BareBonesClockApp() :
        _display(HT16K33_I2C_DEF_ADR, HT16K33_DEF_DISP_SIZE),
        _displayManager(_display),
        _myPrefs(), // These are constructed first
        _myApManager(_myPrefs)
    {
        // Now that members are created, assign the pointers in the base class
        _prefs = &_myPrefs;
        _apManager = &_myApManager;
        
    }

    void setup() override {
        i2c_bus_clear(); // bus clear here for robustness
        Wire.begin();
        _displayManager.begin();
        _rtcActive = _rtc.begin();
        
        // Initialize RTC time if it's invalid
        if (_rtcActive && (!_rtc.isrunning() || _rtc.now() < DateTime(F(__DATE__), F(__TIME__)))) {
            _rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
    
        // Now that hardware is ready, call the base class's setup engine
        BaseNtpClockApp::setup();
        
        // Finally, configure the scene manager with our playlist
        if (_sceneManager) {
            _sceneManager->setup(scenePlaylist, numScenes);
        }
    }

    // --- Implement IGenericClock pure virtual functions ---
    DisplayManager& getClock() override { return _displayManager; }
    RTC_DS1307& getRtc() override { return _rtc; }
    bool isRtcActive() const override { return _rtcActive; }

    // --- Implement other overrides needed by the library ---
    const char* getAppName() const override { return "ESP32 NTP Clock"; }

    const char* getSsid() const override { return _myPrefs.config.ssid; }
    const char* getPassword() const override { return _myPrefs.config.password; }
    const char* getTimezone() const override { return _myPrefs.config.time_zone; }
    void activateAccessPoint() override {
        _myApManager.setup(getAppName());
        _myApManager.runBlockingLoop(getClock(), "AP SETUP MODE", "CONNECT...");
    }
    void syncRtcFromNtp() override { if (_rtcActive) _rtc.adjust(DateTime(time(nullptr))); }

    void formatTime(char* txt, unsigned int txt_size, const char* format, time_t now) override { strftime(txt, txt_size, format, localtime(&now)); }
    bool isOkToRunScenes() const override { return _fsmManager->isInState("RUNNING_NORMAL"); }
    IDisplayDriver& getDisplay() override { return _display; }

private:
    DispDriverHT16K33 _display;
    DisplayManager _displayManager;
    RTC_DS1307 _rtc;
    bool _rtcActive;

    // The derived app fully owns its specific managers
    BarePreferences _myPrefs;
    BareAccessPointManager _myApManager;
};

// 4. STANDARD ARDUINO SETUP and LOOP
BareBonesClockApp app;
void setup() {
    Serial.begin(115200);
    app.setup();
}

void loop() {
    app.loop();
}
