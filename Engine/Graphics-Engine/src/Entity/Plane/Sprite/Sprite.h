#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "../Plane.h"
#include "Animation/Animation.h"
#include "TextureManager/TextureManager.h"

using namespace std;

class GENGINE_API Sprite : public Plane
{
	Texture texture;

	Animation* animation;
	TextureManager* textureManager;
public:
	bool movingUp;
	bool movingDown;
	bool movingRight;
	bool movingLeft;

	Sprite(TextureManager* _textureManager);
	Sprite(TextureManager* _textureManager, const char* texturePath, string textureName);
	Sprite(TextureManager* _textureManager, vec3 _color);
	Sprite(TextureManager* _textureManager, Material _material);
	Sprite(TextureManager* _textureManager, vec3 _color, Material _material);
	~Sprite();

	Texture setTexture(const char* path, string name);
	Texture getTexture();

	void setAnimation(Animation* _animation);
	Animation* getAnimation();
	void updateAnimation();

	void draw();
};

#endif // !SPRITE_H