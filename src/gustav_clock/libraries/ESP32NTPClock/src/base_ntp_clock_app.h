#ifndef BASE_NTP_CLOCK_APP_H
#define BASE_NTP_CLOCK_APP_H

#include <memory>
#include "i_base_clock.h"
#include "base_preferences.h"
#include "base_access_point_manager.h"
#include "clock_fsm_manager.h"
#include "scene_manager.h"
#include "boot_manager.h"

// This is the generic application "engine"
class BaseNtpClockApp : public virtual IBaseClock {
public:
    virtual void setup();
    virtual void loop();

    // These are already implemented by IGenericClock and must be provided by the final app
    virtual DisplayManager& getClock() = 0;
    virtual RTC_DS1307& getRtc() = 0;
    virtual bool isRtcActive() const = 0;

protected:
    // The constructor is protected to ensure this class is only used as a base
    BaseNtpClockApp();

    virtual void setupHardware() = 0;
        
    // Generic managers owned by the base class
    BasePreferences* _prefs;
    BaseAccessPointManager* _apManager;
    std::unique_ptr<ClockFsmManager> _fsmManager;
    std::unique_ptr<SceneManager> _sceneManager;
    std::unique_ptr<BootManager> _bootManager;
};

#endif // BASE_NTP_CLOCK_APP_H
