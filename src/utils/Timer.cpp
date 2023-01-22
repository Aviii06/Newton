#include "Timer.h"

TimePoint Timer::Now()
{
	return s_Clock.now();
}

Timer::Timer()
    : m_StartTime(s_Clock.now())
{
}