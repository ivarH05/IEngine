#pragma once
#include <chrono>

class Time
{
public:
    static void Update();

    static float Runtime();
    static float DeltaTime();
    static float TimeScale();
    static float UnscaledRuntime();
    static float UnscaledDeltaTime();

    static void SetTimeScale(float scale);

private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    static float _time;
    static float _deltaTime;
    static float _unscaledTime;
    static float _unscaledDeltaTime;
    static float _timeScale;
    static TimePoint _lastUpdate;
    static bool _initialized;
};
