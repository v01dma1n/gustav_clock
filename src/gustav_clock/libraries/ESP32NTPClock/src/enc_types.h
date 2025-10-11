#ifndef ENC_TYPES_H
#define ENC_TYPES_H

#include <cstdint>

#define UNSET_VALUE -999.0f

enum AnimationType {
  SLOT_MACHINE,
  MATRIX,
  SCROLLING
};

struct DisplayScene {
  const char* scene_name;
  const char* format_string;
  AnimationType animation_type;
  bool dots_with_previous;
  unsigned long duration_ms;
  unsigned long anim_param_1;
  unsigned long anim_param_2;
  float (*getDataValue)(); 
};

// A generic struct to hold the text and value for a dropdown option
struct PrefSelectOption {
  const char* name; // The user-friendly text (e.g., "Eastern Time")
  const char* value; // The value to save (e.g., "EST5EDT,M3.2.0...")
};

// --- Shared Access Point Form Types ---
enum AppLogLevel {
  APP_LOG_ERROR,
  APP_LOG_INFO,
  APP_LOG_DEBUG
};

enum PrefType { 
  PREF_NONE, PREF_STRING, PREF_BOOL, PREF_INT, PREF_ENUM, PREF_SELECT
};

enum FieldValidation {
  VALIDATION_NONE, VALIDATION_IP_ADDRESS, VALIDATION_INTEGER,
};

typedef struct {
  const char *id;
  const char *name;
  bool isMasked;
  FieldValidation validation;
  PrefType prefType;
  union {
    char *str_pref;
    bool *bool_pref;
    int32_t *int_pref;
  } pref;
  const PrefSelectOption* select_options;
  int num_select_options;
} FormField;

#endif // ENC_TYPES_H
