#pragma once
#include "System\Source\Interface\ISystem.h"

class TimeSystem : public ISystem
{
	friend class SystemManager;

	struct Timer
	{
		Timer() :TimeElapsed(0.0f), RunningTime(0.0f), TimeScale(1.0f), EndTime(FLT_MAX), Repeat(false), Stop(true) {}
		explicit Timer(float scale, bool stop, float endTime = FLT_MAX, bool repeat = false) :TimeElapsed(0.0f), RunningTime(0.0f), TimeScale(scale), EndTime(endTime), Stop(stop), Repeat(repeat) {}

		Timer(const Timer& other)
		{
			memcpy(this, &other, sizeof(other));
		}
		Timer(Timer&& other) noexcept
		{
			memcpy(this, &other, sizeof(other));
		}

		float TimeElapsed;
		float RunningTime;

		float TimeScale;
		bool Stop;

		float EndTime;
		bool Repeat;
	};
	
private:
	TimeSystem() noexcept;
	~TimeSystem() noexcept;

	TimeSystem(const TimeSystem& other) {}

public:
	//	* Time System Initialize (Empty)
	void Initialize(const MainWindowDescription& main_window_description) override;
	
	//	* Time System Release (Empty)
	void Release() override;

	//	* Time System Update
	//	* Running Time , Frame Per Second , Elapsed Time(Delta Time) Update
	void Update();


	//	* Time System TimeStart : Start Timer
	void MainTimeStart();

	//	* Get Elapsed Time (Get Delta Time)
	inline const float& GetElapsedTime() const noexcept { return mainTimer.TimeElapsed; }

	//	* Get Running Time (Begin To TimeStart() Function)
	inline const float& GetRunningTime() const noexcept { return mainTimer.RunningTime; }

	//	* Get Frame Per Second (FPS)
	inline const float& GetFPS() const noexcept { return framePerSecond; }


	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	//	Timer

	//	* Add Timer (time_start : Start Immediately , time_scale : elapsed * scale)
	//	* end_time can be negative value ([# Recommend #] If end_time is negative value, time_scale should set negative too.)
	//	* end_time == 0.0f --> FLT_MAX (Infinity)
	bool AddTimer(const std::string& key, bool time_start = false, float time_scale = 1.0f, float end_time = 0.0f, bool repeat = false);

	//	* Erase Timer
	bool EraseTimer(const std::string& key);

	//	* Is Exist Timer
	bool IsExistTimer(const std::string& key);

	///////////////////////////////////////////////////////////////////////////
	//	Set

	//	* Timer Start
	void TimerStart(const std::string& key);

	//	* Timer Stop
	void TimerStop(const std::string& key);


	//	* Set Timer Scale
	void TimerSetScale(const std::string& key, float time_scale);

	//	* Reset Zero Timer Running Time ( = 0.0f)
	void TimerResetRunningTime(const std::string& key);

	//	* Set Timer RunningTime
	void TimerSetRunningTime(const std::string& key, float running_time);

	//	* Set Timer Max Time
	//	* end_time can be negative value ([# Recommend #] If end_time is negative value, time_scale should set negative too.)
	//	* end_time == 0.0f --> FLT_MAX (Infinity)
	void TimerSetEndTime(const std::string& key, float end_time);

	//	* Set Timer Repeat
	void TimerSetRepeat(const std::string& key, bool repeat);

	///////////////////////////////////////////////////////////////////////////
	//	Get

	//	* Is Timer Stop (If Not Exist, Return True)
	bool IsTimerStop(const std::string& key);

	//	* Get Timer Elapsed Time (If Not Exist, Return 0.0f)
	float TimerGetElapsedTime(const std::string& key);

	//	* Get Timer Running Time (If Not Exist, Return 0.0f)
	float TimerGetRunningTime(const std::string& key);

	//	* Get Timer Time Scale (If Not Exist, Return 1.0f)
	float TimerGetScale(const std::string& key);

	//	* Get Timer Max Time
	float TimerGetEndTime(const std::string& key);

	//	* Is Timer Repeat
	bool IsTimerRepeat(const std::string& key);


private:
	Timer* GetTimer(const std::string& key) { if (IsExistTimer(key) == false) { return NULL; } return &timers.at(key); }

private:
	Timer mainTimer;

	signed long long ticksPerSecond;///< 초당 틱카운트
	signed long long currentTime;///< 현재 시간
	signed long long lastTime;///< 이전시간
	signed long long lastFPSUpdate;///< 마지막 FPS 업데이트 시간
	signed long long fpsUpdateInterval;///< fps 업데이트 간격

	unsigned int frameCount;///< 프레임 수
	float framePerSecond;///< FPS

	typedef std::unordered_map<std::string, Timer>::iterator TimerIterator;
	std::unordered_map<std::string, Timer> timers;
};
