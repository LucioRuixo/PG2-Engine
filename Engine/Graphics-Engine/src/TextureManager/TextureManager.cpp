#include "TextureManager.h"

TextureManager::TextureManager(Renderer* _renderer)
{
	renderer = _renderer;
}

TextureManager::~TextureManager()
{
	for (auto item : textureMap) glDeleteTextures(1, &item.second.id);
	textureMap.clear();
}

void TextureManager::initializeTextureValues()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glActiveTexture(GL_TEXTURE0);

	glUniform1i(glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "textureData"), 0);

	glUniform1i(glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.diffuseTexture0"), 1);
	glUniform1i(glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.diffuseTexture1"), 2);
	glUniform1i(glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.diffuseTexture2"), 3);
	glUniform1i(glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.diffuseTexture3"), 4);

	glUniform1i(glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.specularTexture0"), 5);
	glUniform1i(glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.specularTexture1"), 6);
	glUniform1i(glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.specularTexture2"), 7);
	glUniform1i(glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.specularTexture3"), 8);

	stbi_set_flip_vertically_on_load(1);
}

Texture TextureManager::createTextureFromFile(const char* path, string name)
{
	Texture texture;
	glGenTextures(1, &texture.id);

	texture.type = "baseColorTexture";
	texture.data = stbi_load(path, &texture.width, &texture.height, &texture.channels, 0);

	if (texture.data)
	{
		GLenum format;
		if (texture.channels == 1) format = GL_RED;
		else if (texture.channels == 3) format = GL_RGB;
		else if (texture.channels == 4) format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, texture.data);
		glGenerateMipmap(GL_TEXTURE_2D);

		std::cout << "successfully loaded texture from path \"" << path << "\"" << std::endl;
	}
	else std::cout << "failed to load texture from path \"" << path << "\"" << std::endl;
	stbi_image_free(texture.data);

	textureMap[name] = texture;
	return texture;
}

Texture TextureManager::getTexture(string name)
{
	for (auto item : textureMap) if (item.first == name) return item.second;
	std::cout << "could not find texture with name \"" << name << "\"" << std::endl;
	
	Texture nullTexture;
	return nullTexture;
}