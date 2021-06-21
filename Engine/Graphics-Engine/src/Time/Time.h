#ifndef TIME_H
#define TIME_H

#include <chrono>
#include <time.h>
#include "Tools/Includes.h"

class GENGINE_API Time
{
private:
	static float elapsedTime;
	static float deltaTime;

	int frames;

	float timeScale;
	float framesCounter;
	float fps = 0;

	std::chrono::system_clock::time_point startTime;
public:
	static float getDeltaTime();

	Time();
	~Time();

	void tick();
	void reset();
	void setTimeScale(float value);
	float getTimeScale();
	float getSeconds();
	void calculateFPS();
	float getFPS();
	void printFPS();
};

#endif // !TIME_H