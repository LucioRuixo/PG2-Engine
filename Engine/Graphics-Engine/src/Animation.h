#ifndef ANIMATION_H
#define ANIMATION_H
#include"includes.h"
#include"Time.h"
#include"Frame.h"
#include<vector>

class GENGINE_API Animation {
private:
	int currentFrame;
	float currentTime;
	float length;
	int acumulationWidth;
	int acumulationHeigth;
	std::vector<Frame> totalFrames;
	std::vector<std::vector<Frame>> animations;
	int currentAnimation = 0;
public:
	Animation();
	~Animation();
	void Update();
	void AddFrame(float frameX, float frameY, 
		int spriteWidth, int spriteHeigth, 
		int textureWidth, int tectureHeight,
		float timeToAnim, int totalFrames, int countFramesForFilas);
	int GetCurrentFrame();
	std::vector<Frame>& GetAnimation();
	void SetCurrentAnimation(int _currentAnimation);
	void AddFrame(float frameX, float frameY, 
		int spriteWidth, int spriteHeigth,
		int textureWigth, int textureHeigth, float timeToAnim);
	void AddAnimation();
};

#endif // !ANIMATION_H