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

	Sprite(Renderer* _renderer, TextureManager* _textureManager);
	Sprite(Renderer* _renderer, TextureManager* _textureManager, const char* texturePath, int textureFormat, string textureName);
	Sprite(Renderer* _renderer, TextureManager* _textureManager, vec3 _color);
	Sprite(Renderer* _renderer, TextureManager* _textureManager, Material _material);
	Sprite(Renderer* _renderer, TextureManager* _textureManager, vec3 _color, Material _material);
	~Sprite();

	Texture setTexture(const char* path, int format, string name);
	Texture getTexture();

	void setAnimation(Animation* _animation);
	Animation* getAnimation();
	void updateAnimation();

	void draw();
};

#endif // !SPRITE_H