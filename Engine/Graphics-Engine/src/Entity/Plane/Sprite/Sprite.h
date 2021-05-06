#ifndef SPRITE_H
#define SPRITE_H

#include "../Plane.h"
#include "Animation/Animation.h"
#include "TextureImporter/TextureImporter.h"

class GENGINE_API Sprite : public Plane
{
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
	Sprite(Renderer* _renderer, vec3 _color);
	Sprite(Renderer* _renderer, Material _material);
	Sprite(Renderer* _renderer, vec3 _color, Material _material);
	~Sprite();

	TextureData setTexture(const char* filePath, int _type);
	void loadTexture();
	void setAnimation(Animation* _animation);
	Animation* getAnimation();
	void updateAnimation();
};

#endif // !SPRITE_H