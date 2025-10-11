#include "debug.h"
#include "gustav_preferences.h"
#include <ESP32NTPClock.h>

#define APP_PREF_SHOW_STARTUP_ANIM "startup_anim"
#define APP_PREF_OWM_API_KEY "owm_api_key"
#define APP_PREF_OWM_CITY    "owm_city"
#define APP_PREF_OWM_STATE_CODE "owm_state"
#define APP_PREF_OWM_COUNTRY_CODE "owm_country"
#define APP_PREF_TEMP_UNIT "temp_unit"

void GustavPreferences::getPreferences() {
  BasePreferences::getPreferences();
  prefs.begin(PREF_NAMESPACE, true);
  config.showStartupAnimation = prefs.getBool(APP_PREF_SHOW_STARTUP_ANIM, true); 
  prefs.getString(APP_PREF_OWM_API_KEY, config.owm_api_key, sizeof(config.owm_api_key));
  prefs.getString(APP_PREF_OWM_CITY, config.owm_city, sizeof(config.owm_city));
  prefs.getString(APP_PREF_OWM_STATE_CODE, config.owm_state_code, sizeof(config.owm_state_code));
  prefs.getString(APP_PREF_OWM_COUNTRY_CODE, config.owm_country_code, sizeof(config.owm_country_code));
  prefs.getString(APP_PREF_TEMP_UNIT, config.tempUnit, sizeof(config.tempUnit));
  prefs.end();
}

void GustavPreferences::putPreferences() {
  BasePreferences::putPreferences();
  prefs.begin(PREF_NAMESPACE, false);
  prefs.putBool(APP_PREF_SHOW_STARTUP_ANIM, config.showStartupAnimation);
  prefs.putString(APP_PREF_OWM_API_KEY, config.owm_api_key);
  prefs.putString(APP_PREF_OWM_CITY, config.owm_city);
  prefs.putString(APP_PREF_OWM_STATE_CODE, config.owm_state_code);
  prefs.putString(APP_PREF_OWM_COUNTRY_CODE, config.owm_country_code);
  prefs.putString(APP_PREF_TEMP_UNIT, config.tempUnit);
  prefs.end();
}

void GustavPreferences::dumpPreferences() {
  BasePreferences::dumpPreferences();
  LOGMSG(APP_LOG_DEBUG, "Pref=%s: %s", APP_PREF_SHOW_STARTUP_ANIM, config.showStartupAnimation ? "Yes" : "No");
  LOGMSG(APP_LOG_DEBUG, "Pref=%s: %s", APP_PREF_OWM_CITY, config.owm_city);
  LOGMSG(APP_LOG_DEBUG, "Pref=%s: %s", APP_PREF_OWM_STATE_CODE, config.owm_state_code);
  LOGMSG(APP_LOG_DEBUG, "Pref=%s: %s", APP_PREF_OWM_COUNTRY_CODE, config.owm_country_code);
  LOGMSG(APP_LOG_DEBUG, "Pref=%s: %s", APP_PREF_OWM_API_KEY, "***"); 
  LOGMSG(APP_LOG_DEBUG, "Pref=%s: %s", APP_PREF_TEMP_UNIT, config.tempUnit);
}
