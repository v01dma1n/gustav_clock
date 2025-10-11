#ifndef I_WEATHER_CLOCK_H
#define I_WEATHER_CLOCK_H

#include "i_base_clock.h"
#include "openweather_client.h"

// This interface extends the base clock with weather-specific functions
class IWeatherClock : public virtual IBaseClock {
public:
    virtual ~IWeatherClock() {}

    // Override the check to confirm this object supports the weather interface
    IWeatherClock* asWeatherClock() override { return this; }

    // --- WEATHER-SPECIFIC METHODS ---
    virtual const char* getTempUnit() const = 0;
    virtual const char* getOwmApiKey() const = 0;
    virtual const char* getOwmCity() const = 0;
    virtual const char* getOwmStateCode() const = 0;
    virtual const char* getOwmCountryCode() const = 0;
    virtual void setWeatherData(const OpenWeatherData& data) = 0;
};

#endif // I_WEATHER_CLOCK_H
