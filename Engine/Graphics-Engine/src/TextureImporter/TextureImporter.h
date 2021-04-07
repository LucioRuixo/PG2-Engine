#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include "Tools/Includes.h"
#include "stb_image/stb_image.h"

struct TextureData
{
	unsigned char* pixelData;
	int width;
	int height;
	int nrChannels;
};

class TextureImporter
{
public:
	TextureData importTexture(const char* filePath, int type);
	void loadTexture(TextureData textureData, int type);
};

#endif // !TEXTURE_IMPORTER_H