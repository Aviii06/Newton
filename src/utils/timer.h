#pragma once

#include <chrono>

#include "../common/types.h"

#define NS_TO_MS 1e-6f
#define MS_TO_S 1e-3f

// A point in time of the high resolution clock
typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

// Helper to keep track of time.
class Timer
{
protected:
	static const std::chrono::high_resolution_clock s_Clock;

	TimePoint m_StartTime;
	TimePoint m_EndTime;

public:
	static TimePoint Now();

	Timer();

	Timer(Timer&) = delete;

	virtual ~Timer() = default;

	float getTimeMs() const { return (float)(s_Clock.now() - m_StartTime).count() * NS_TO_MS; }

	float getTimeNs() const { return (s_Clock.now() - m_StartTime).count(); }
};
