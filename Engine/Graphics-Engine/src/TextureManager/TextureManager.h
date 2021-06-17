#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>
#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "stb_image/stb_image.h"

using namespace std;

struct Texture
{
	unsigned int id = -1;

	string type;

	int width;
	int height;
	int channels;

	unsigned char* data;
};

class TextureManager
{
	map<string, Texture> textureMap;

	Renderer* renderer;
public:
	TextureManager(Renderer* _renderer);
	~TextureManager();

	void initializeTextureValues();

	Texture createTextureFromFile(const char* path, string name);
	Texture getTexture(string name);
};

#endif // !TEXTURE_MANAGER_H