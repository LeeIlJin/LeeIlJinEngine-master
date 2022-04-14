#include "MySystem.h"

#include "TimeSystem.h"
//

TimeSystem::TimeSystem() noexcept
	:ticksPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0), fpsUpdateInterval(0)
	, frameCount(0), framePerSecond(0)
{ }

TimeSystem::~TimeSystem() noexcept
{
}

void TimeSystem::Initialize(const MainWindowDescription& main_window_description)
{
	//	Empty
}

void TimeSystem::Release()
{
	timers.clear();
}

void TimeSystem::Update()
{
	//1. 현재시간을 가져와 시간 간격 및 진행 시간을 계산한다.
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	mainTimer.TimeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond;
	mainTimer.RunningTime += mainTimer.TimeElapsed;


	//2. FPS Update
	frameCount++;
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime);

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0;
	}

	lastTime = currentTime;

	for (TimerIterator iter = timers.begin(); iter != timers.end(); iter++)
	{
		if (iter->second.Stop == true)
		{
			iter->second.TimeElapsed = 0.0f;
			continue;
		}

		iter->second.TimeElapsed = mainTimer.TimeElapsed * iter->second.TimeScale;
		iter->second.RunningTime += iter->second.TimeElapsed;

		if (((iter->second.TimeScale < 0.0f)? iter->second.RunningTime <= iter->second.EndTime : iter->second.RunningTime >= iter->second.EndTime))
		{
			if (iter->second.Repeat == true)
				iter->second.RunningTime -= iter->second.EndTime;
			else
			{
				iter->second.RunningTime = iter->second.EndTime;
				iter->second.Stop = true;
			}
		}
	}
}

void TimeSystem::MainTimeStart()
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond);
	QueryPerformanceCounter((LARGE_INTEGER *)&lastTime);
	fpsUpdateInterval = ticksPerSecond >> 1;
}

bool TimeSystem::AddTimer(const std::string & key, bool time_start, float time_scale, float end_time, bool repeat)
{
	if (IsExistTimer(key) == true)
		return false;

	if (end_time == 0.0f)
		end_time = FLT_MAX;

	timers.insert(std::pair<std::string, Timer>(key, Timer(time_scale, !time_start, end_time, repeat)));
	return true;
}

bool TimeSystem::EraseTimer(const std::string & key)
{
	if (IsExistTimer(key) == false)
		return false;

	timers.erase(key);
	return true;
}

bool TimeSystem::IsExistTimer(const std::string & key)
{
	return timers.count(key) > 0;
}

void TimeSystem::TimerStart(const std::string & key)
{
	Timer* timer = GetTimer(key);

	if (timer == NULL)
		return;

	timer->Stop = false;
}

void TimeSystem::TimerStop(const std::string & key)
{
	Timer* timer = GetTimer(key);

	if (timer == NULL)
		return;

	timer->Stop = true;
}

void TimeSystem::TimerSetScale(const std::string & key, float time_scale)
{
	Timer* timer = GetTimer(key);

	if (timer == NULL)
		return;

	timer->TimeScale = time_scale;
}

void TimeSystem::TimerResetRunningTime(const std::string & key)
{
	Timer* timer = GetTimer(key);

	if (timer == NULL)
		return;

	timer->RunningTime = 0.0f;
}

void TimeSystem::TimerSetRunningTime(const std::string & key, float running_time)
{
	Timer* timer = GetTimer(key);

	if (timer == NULL)
		return;

	timer->RunningTime = running_time;
}

void TimeSystem::TimerSetEndTime(const std::string & key, float end_time)
{
	Timer* timer = GetTimer(key);

	if (timer == NULL)
		return;

	if (end_time == 0.0f)
		end_time = FLT_MAX;

	timer->EndTime = end_time;
}

void TimeSystem::TimerSetRepeat(const std::string & key, bool repeat)
{
	Timer* timer = GetTimer(key);

	if (timer == NULL)
		return;

	timer->Repeat = repeat;
}

bool TimeSystem::IsTimerStop(const std::string & key)
{
	Timer* timer = GetTimer(key);

	if (timer == NULL)
		return true;

	return timer->Stop;
}

float TimeSystem::TimerGetElapsedTime(const std::string & key)
{
	if (IsExistTimer(key) == false)
		return 0.0f;

	return timers.at(key).TimeElapsed;
}

float TimeSystem::TimerGetRunningTime(const std::string & key)
{
	if (IsExistTimer(key) == false)
		return 0.0f;

	return timers.at(key).RunningTime;
}

float TimeSystem::TimerGetScale(const std::string & key)
{
	if (IsExistTimer(key) == false)
		return 0.0f;

	return timers.at(key).TimeScale;
}

float TimeSystem::TimerGetEndTime(const std::string & key)
{
	if (IsExistTimer(key) == false)
		return 0.0f;

	return timers.at(key).EndTime;
}

bool TimeSystem::IsTimerRepeat(const std::string & key)
{
	if (IsExistTimer(key) == false)
		return false;

	return timers.at(key).Repeat;
}
