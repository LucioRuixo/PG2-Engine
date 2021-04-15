#include "Time.h"

float Time::elapsedTime = 0.0f;
float Time::deltaTime = 0.0f;

Time::Time()
{
	Reset();
	timeScale = 1.0f;
}

Time::~Time() {}

double oldTime = clock();

void Time::Reset()
{
	startTime = std::chrono::system_clock::now();
}

void Time::SetTimeScale(float value) { timeScale = value; }

float Time::GetTimeScale() { return timeScale; }

float Time::GetSeconds() { return 0; }

void Time::StartTime() {}

void Time::Tick()
{
	double time = clock();
	deltaTime = (float)((time - oldTime) / 1000.0f);
	oldTime = time;
}
float Time::DeltaTime() { return deltaTime; }

void Time::CalculateFPS()
{
	elapsedTime += DeltaTime();
	frames++;
	if (elapsedTime >= 1.0f)
	{
		fps = frames / elapsedTime;
		frames = 0;
		elapsedTime = 0;
	}
}
float Time::GetFps() { return fps; }

void Time::PrintFPS()
{
	std::cout << "FPS: " << 1.0f / DeltaTime() << std::endl;
}