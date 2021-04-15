#include "TextureImporter.h"

TextureData TextureImporter::importTexture(const char* filePath, int type)
{
	TextureData textureData;
	textureData.pixelData = stbi_load(filePath, &textureData.width, &textureData.height, &textureData.nrChannels, 0);

	if (textureData.pixelData)
	{
		switch (type)
		{
		case GL_RGB:
			glTexImage2D(GL_TEXTURE_2D, 0, type, textureData.width, textureData.height, 0, type, GL_UNSIGNED_BYTE, textureData.pixelData);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		case GL_RGBA:
			glTexImage2D(GL_TEXTURE_2D, 0, type, textureData.width, textureData.height, 0, type, GL_UNSIGNED_BYTE, textureData.pixelData);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		}
	}
	else std::cout << "Failed to import texture: pixel data null" << std::endl;

	return textureData;
}

void TextureImporter::loadTexture(TextureData textureData, int type)
{
	if (textureData.pixelData)
	{
		switch (type)
		{
		case GL_RGB:
			glTexImage2D(GL_TEXTURE_2D, 0, type, textureData.width, textureData.height, 0, type, GL_UNSIGNED_BYTE, textureData.pixelData);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		case GL_RGBA:
			glTexImage2D(GL_TEXTURE_2D, 0, type, textureData.width, textureData.height, 0, type, GL_UNSIGNED_BYTE, textureData.pixelData);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		}
	}
	else std::cout << "Failed to load texture: pixel data null" << std::endl;
}