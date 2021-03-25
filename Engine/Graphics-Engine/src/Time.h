#ifndef TIME_H
#define TIME_H
#include <chrono>
#include <time.h>
#include "includes.h"

class GENGINE_API Time {
private:
	std::chrono::system_clock::time_point startTime;
	static float elapsedTime;
	static float deltaTime;
	float timeScale;
	float framesCounter;
	int frames;
	float fps = 0;
public:
	Time();
	~Time();
	static float DeltaTime();
	void Reset();
	void SetTimeScale(float t);
	float GetTimeScale();
	float GetSeconds();
	void StartTime();
	void Tick();
	void CalculateFps();
	float GetFps();
	void FPS();
};

#endif // !TIME_H