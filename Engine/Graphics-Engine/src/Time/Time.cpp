#include "Time.h"

float Time::elapsedTime = 0.0f;
float Time::deltaTime = 0.0f;

double oldTime = clock();

float Time::getDeltaTime() { return deltaTime; }

Time::Time()
{
	reset();
	timeScale = 1.0f;
}

Time::~Time() {}

void Time::tick()
{
	double time = clock();
	deltaTime = (float)((time - oldTime) / 1000.0f);
	oldTime = time;
}

void Time::reset()
{
	startTime = std::chrono::system_clock::now();
}

void Time::setTimeScale(float value) { timeScale = value; }

float Time::getTimeScale() { return timeScale; }

float Time::getSeconds() { return 0; }

void Time::calculateFPS()
{
	elapsedTime += deltaTime;
	frames++;
	if (elapsedTime >= 1.0f)
	{
		fps = frames / elapsedTime;
		frames = 0;
		elapsedTime = 0;
	}
}
float Time::getFPS() { return fps; }

void Time::printFPS()
{
	std::cout << "FPS: " << 1.0f / deltaTime << std::endl;
}