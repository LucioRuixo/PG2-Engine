#include "TextureManager.h"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

Texture TextureManager::createTextureFromFile(const char* path, int format, string name)
{
	Texture texture;
	glGenTextures(1, &texture.id);

	texture.type = "texture_baseColor";
	texture.data = stbi_load(path, &texture.width, &texture.height, &texture.channels, 0);

	if (texture.data)
	{
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, texture.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else std::cout << "Failed to load texture from path: " << path << std::endl;
	stbi_image_free(texture.data);

	textureMap[name] = texture;
	return texture;
}

Texture TextureManager::getTexture(string name)
{
	for (auto item : textureMap) if (item.first == name) return item.second;
	std::cout << "Could not find texture with name: " << name << std::endl;
	
	Texture nullTexture;
	return nullTexture;
}