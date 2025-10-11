#ifndef GUSTAV_WEATHER_MANAGER_H
#define GUSTAV_WEATHER_MANAGER_H

class IWeatherClock;

class GustavWeatherDataManager {
public:
    GustavWeatherDataManager(IWeatherClock& app);
    void update();
private:
    IWeatherClock& _app;
    unsigned long _lastWeatherFetchTime;
    const unsigned long _weatherFetchInterval = 900000;
};

#endif // GUSTAV_WEATHER_MANAGER_H
