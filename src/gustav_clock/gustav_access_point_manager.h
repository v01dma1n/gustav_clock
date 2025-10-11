#ifndef GUSTAV_ACCESS_POINT_MANAGER_H
#define GUSTAV_ACCESS_POINT_MANAGER_H

#include <base_access_point_manager.h>
#include "gustav_preferences.h"

class GustavAccessPointManager : public BaseAccessPointManager {
public:
    GustavAccessPointManager(GustavPreferences& prefs) : BaseAccessPointManager(prefs) {}

protected:
    void initializeFormFields() override;
};

#endif // GUSTAV_ACCESS_POINT_MANAGER_H
