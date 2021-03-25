#include "Time.h"

float Time::elapsedTime = 0.0f;
float Time::deltaTime = 0.0f;

Time::Time() {
	Reset();
	timeScale = 1.0f;
}
Time::~Time() {

}
double oldT = clock();
void Time::Reset() {
	startTime = std::chrono::system_clock::now();
}
void Time::SetTimeScale(float t) {
	timeScale = t;
}
float Time::GetTimeScale() {
	return timeScale;
}
float Time::GetSeconds() {
	return 0;
}
void Time::StartTime() {

}
void Time::Tick() {
	double t = clock();
	deltaTime = (float)((t - oldT) / 1000.0f);
	oldT = t;
}
float Time::DeltaTime() {
	return deltaTime;
}
void Time::CalculateFps() {
	elapsedTime += DeltaTime();
	frames++;
	if (elapsedTime >= 1.0f) {
		fps = frames / elapsedTime;
		frames = 0;
		elapsedTime = 0;
	}
}
float Time::GetFps() {
	return fps;
}
void Time::FPS() {
	std::cout << "FPS: " << 1.0f / DeltaTime() << std::endl;
}