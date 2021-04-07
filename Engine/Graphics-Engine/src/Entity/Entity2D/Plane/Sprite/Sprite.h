#ifndef SPRITE_H
#define SPRITE_H

#include "../Plane.h"
#include "Animation/Animation.h"
#include "TextureImporter/TextureImporter.h"

#define RGB 0x1907
#define RGBA 0x1908

class GENGINE_API Sprite : public Plane
{
private:
	int type;
	TextureData textureData;
	TextureImporter texture;
	Animation* animation;
public:
	bool movingUp;
	bool movingDown;
	bool movingRight;
	bool movingLeft;

	Sprite(Renderer* _renderer);
	~Sprite();
	TextureData setTexture(const char* filePath, int _type);
	void loadTexture();
	void setAnimation(Animation* _animation);
	Animation* getAnimation();
	void updateAnimation();
	void draw();
};

#endif // !SPRITE_H