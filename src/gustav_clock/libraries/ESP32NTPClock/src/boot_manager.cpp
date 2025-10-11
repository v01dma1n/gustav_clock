#include "boot_manager.h"
#include "enc_debug.h"

#include <Preferences.h>
#include "RTClib.h" // Needed for DateTime

BootManager::BootManager(IBaseClock& clock) : _clock(clock) {}

bool BootManager::checkForForceAPMode() {
    // This logic is moved from the application's setup() function.
    // It only works if the clock has an active RTC.
    if (!_clock.isRtcActive()) {
        ENC_LOG("Double-reset check skipped: RTC not active.");
        return false;
    }

    Preferences boot_prefs;
    boot_prefs.begin("boot_check", false);
    
    uint32_t last_boot_time_s = boot_prefs.getUInt("last_boot_s", 0);
    uint32_t current_boot_time_s = _clock.getRtc().now().unixtime();
    
    ENC_LOG("Last boot time read: %lu", last_boot_time_s);
    ENC_LOG("Current RTC time:    %lu", current_boot_time_s);
    
    // Store the current boot time for the next check
    boot_prefs.putUInt("last_boot_s", current_boot_time_s);
    boot_prefs.end();
    
    // Add a small delay to ensure the value is committed to flash before a
    // rapid second reset can occur. 50ms is more than enough.
    delay(50);
    
    // Check if the time between boots is within our window
    if (last_boot_time_s > 0) {
        uint32_t diff = current_boot_time_s - last_boot_time_s;
        ENC_LOG("Time since last boot: %lu seconds.", diff);
        if (diff < _resetWindowSeconds) {
            ENC_LOG("Double reset detected!");
            return true; // Double reset detected
        }
    }
    
    return false; // Normal boot
}
