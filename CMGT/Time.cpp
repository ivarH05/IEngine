#include "Time.h"
using namespace std::chrono;

float Time::_time = 0.0f;
float Time::_deltaTime = 0.0f;
float Time::_unscaledTime = 0.0f;
float Time::_unscaledDeltaTime = 0.0f;
float Time::_timeScale = 1.0f;

Time::TimePoint Time::_lastUpdate;
bool Time::_initialized = false;

void Time::Update()
{
    auto now = Clock::now();

    if (!_initialized)
    {
        _lastUpdate = now;
        _initialized = true;
        return;
    }

    duration<float> duration_seconds = now - _lastUpdate;
    _unscaledDeltaTime = duration_seconds.count();
    _unscaledTime += _unscaledDeltaTime;

    _deltaTime = _unscaledDeltaTime * _timeScale;
    _time += _deltaTime;

    _lastUpdate = now;
}

float Time::Runtime() { return _time; }
float Time::DeltaTime() { return _deltaTime; }
float Time::UnscaledRuntime() { return _unscaledTime; }
float Time::UnscaledDeltaTime() { return _unscaledDeltaTime; }
float Time::TimeScale() { return _timeScale; }
void Time::SetTimeScale(float scale) { _timeScale = scale; }
