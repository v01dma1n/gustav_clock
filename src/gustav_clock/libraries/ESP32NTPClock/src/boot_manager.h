#ifndef BOOT_MANAGER_H
#define BOOT_MANAGER_H

#include "i_base_clock.h"

class BootManager {
public:
    // The constructor takes the generic clock interface
    BootManager(IBaseClock& clock);

    // This function will contain all the logic and return true if AP mode should be activated.
    bool checkForForceAPMode();

private:
    IBaseClock& _clock;
    const int _resetWindowSeconds = 5; // 5-second window for double reset
};

#endif // BOOT_MANAGER_H
