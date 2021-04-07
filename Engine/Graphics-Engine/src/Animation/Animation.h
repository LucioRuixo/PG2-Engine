#ifndef ANIMATION_H
#define ANIMATION_H

#include "Tools/Includes.h"
#include "Frame.h"
#include "Time/Time.h"
#include <vector>

using namespace std;

class GENGINE_API Animation
{
private:
	int currentFrame;
	float currentTime;
	float length;
	int acumulationWidth;
	int acumulationHeigth;
	int currentAnimation = 0;
	vector<Frame> totalFrames;
	vector<vector<Frame>> animations;
public:
	Animation();
	~Animation();
	void update();
	void addFrame(float frameX, float frameY,
		int spriteWidth, int spriteHeigth,
		int textureWigth, int textureHeigth, float timeToAnim);
	void addFrame(float frameX, float frameY, 
		int spriteWidth, int spriteHeigth, 
		int textureWidth, int tectureHeight,
		float timeToAnim, int totalFrames, int countFramesForFilas);
	int getCurrentFrame();
	vector<Frame>& getAnimation();
	void setCurrentAnimation(int _currentAnimation);
	void addAnimation();
};

#endif // !ANIMATION_H