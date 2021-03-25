#include"Animation.h"

Animation::Animation() {
	currentTime = 0;
	currentFrame = 0;
	length = 200;
}
Animation::~Animation() {
	if (animations.size() > 0)
		animations.clear();
	if (totalFrames.size() > 0)
		totalFrames.clear();
}
void Animation::Update() {
	currentTime += (Time::DeltaTime());

	while (currentTime >= length) {
		currentTime -= length;
	}

	float frameLength = length / animations[currentAnimation].size();
	currentFrame = static_cast<int>(currentTime / frameLength);
}
void Animation::AddFrame(float frameX, float frameY,
	int spriteWidth, int spriteHeigth,
	int textureWidth, int textureHeigth,
	float timeToAnim, int _totalFrames, int framesPerRow) {
	//---
	length = timeToAnim;

	float index_X = 0;
	float index_Y = 0;
	Frame frame;

	int spriteRows = _totalFrames / framesPerRow;
	int spriteColumns = framesPerRow;
	for (int y = 0; y < spriteRows; y++)
	{
		frameY = spriteHeigth * y;

		for (int x = 0; x < spriteColumns; x++)
		{
			frameX = spriteWidth * x;

			frame.frameCoords[0].u = (frameX / textureWidth);
			frame.frameCoords[0].v = ((frameY + spriteHeigth) / textureHeigth);
			frame.frameCoords[1].u = ((frameX + spriteWidth) / textureWidth);
			frame.frameCoords[1].v = ((frameY + spriteHeigth) / textureHeigth);
			frame.frameCoords[2].u = ((frameX + spriteWidth) / textureWidth);
			frame.frameCoords[2].v = (frameY / textureHeigth);
			frame.frameCoords[3].u = (frameX / textureWidth);
			frame.frameCoords[3].v = (frameY / textureHeigth);

			totalFrames.push_back(frame);
		}
	}
}
int Animation::GetCurrentFrame() {
	return currentFrame;
}
std::vector<Frame>& Animation::GetAnimation() {
	if (currentAnimation < animations.size())
		return animations[currentAnimation];

	return animations[animations.size() - 1];
}
void Animation::SetCurrentAnimation(int _currentAnimation) {
	currentAnimation = _currentAnimation;
}
void Animation::AddFrame(float frameX, float frameY,
	int spriteWidth, int spriteHeigth,
	int textureWidth, int textureHeigth, float timeToAnim) {
	//---
	length = timeToAnim;

	Frame frame;

	frame.frameCoords[0].u = ((frameX) / textureWidth);
	frame.frameCoords[0].v = ((spriteHeigth + frameY) / textureHeigth);
	//--------
	frame.frameCoords[1].u = (((frameX)+spriteWidth) / textureWidth);
	frame.frameCoords[1].v = ((spriteHeigth + frameY) / textureHeigth);
	//--------
	frame.frameCoords[2].u = (((frameX)+spriteWidth) / textureWidth);
	frame.frameCoords[2].v = ((frameY) / textureHeigth);
	//--------
	frame.frameCoords[3].u = ((frameX) / textureWidth);
	frame.frameCoords[3].v = ((frameY) / textureHeigth);
	//--------
	totalFrames.push_back(frame);
}
void Animation::AddAnimation() {
	if (totalFrames.size() > 0)
	{
		animations.push_back(totalFrames);
		totalFrames.clear();
	}
}