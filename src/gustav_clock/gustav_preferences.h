#ifndef GUSTAV_PREFERENCES_H
#define GUSTAV_PREFERENCES_H

#include "gustav_types.h"
#include <base_preferences.h> 

struct GustavConfig : public BaseConfig {
  bool showStartupAnimation;
  char owm_api_key[MAX_PREF_STRING_LEN];
  char owm_city[MAX_PREF_STRING_LEN];
  char owm_state_code[MAX_PREF_STRING_LEN];
  char owm_country_code[MAX_PREF_STRING_LEN];
  char tempUnit[MAX_PREF_STRING_LEN];
};

class GustavPreferences : public BasePreferences {
public:
    GustavPreferences() : BasePreferences(config) {}
    void getPreferences() override;
    void putPreferences() override;
    void dumpPreferences() override;
    GustavConfig config;
};

#endif // GUSTAV_PREFERENCES_H
