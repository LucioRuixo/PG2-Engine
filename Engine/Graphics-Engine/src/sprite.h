#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D.h"
#include "Animation.h"
#include "textureImporter.h"

#define RGB 0x1907
#define RGBA 0x1908

class GENGINE_API Sprite : public Entity2D
{
private:
	int size;
	int type;
	TextureData textureData;
	textureImporter texture;
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
	void updateAnimation();
	void setBufferData();
	void setAnimation(Animation* _animation);
	Animation* getAnimation();
};

#endif // !SPRITE_H