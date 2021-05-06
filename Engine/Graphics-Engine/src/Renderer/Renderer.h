#ifndef RENDERER_H
#define RENDERER_H

#include "Tools/Includes.h"
#include "stb_image/stb_image.h"

#define TRPOS6 6
#define TRPOS3 3

using namespace glm;

enum ShaderType
{
	Main,
	LightSource,
	Size
};

struct Shader
{
	ShaderType type;
	unsigned int programID;
};

struct VPMatrix
{
	mat4 view;
	mat4 projection;
	vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
	vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
};

class GENGINE_API Renderer
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

	unsigned int positionAttributeLocation;
	unsigned int colorAttribute;
	unsigned int normalAttributeLocation;
	unsigned int texture;

	vec3 backgroundColor;

	int currentShader = -1;
	Shader shaders[ShaderType::Size];

	VPMatrix vpMatrix;
public:
	Renderer();
	~Renderer();

#pragma region Background
	void setBackgroundColor(vec3 value);
	vec3 getBackgroundColor();
	void clearBackground();
#pragma endregion

#pragma region Vertices
	void createVAO();
	void bindVAO(unsigned int _vao);
	unsigned int getVAO();

	void createVBO();
	void bindVBO(unsigned int _vbo);
	unsigned int getVBO();

	void createEBO();
	void bindEBO(unsigned int _ebo);
	unsigned int getEBO();

	void setVertexBufferData(int size, float* verterBuffer);
	void setIndexBufferData(int size, unsigned int* indexBuffer);
	void setVertexAttributes();
	void drawArrays(int vertexAmount);
	void drawElements(int indexAmount);
#pragma endregion

#pragma region MVP
	void setModel(unsigned int _shaderProgram, mat4 model);
	void setView(mat4 view);
	void setProjection(mat4 projection);
	mat4 getProjection();
	void updateProjection(mat4 &projection);
#pragma endregion

#pragma region Textures
	void generateTexture();
	void setParameterTexture();
#pragma endregion

#pragma region Shaders
	unsigned int compileShader(unsigned int type, const char* source);
	unsigned int createShaderProgram(const char * vertexPath, const char * fragmentPath);
	void setShaderProgram(ShaderType type, const char* vertexPath, const char* fragmentPath);
	unsigned int getShaderProgram(ShaderType type);
	void useShader(ShaderType type);
	ShaderType getCurrentShader();
#pragma endregion
};

#endif // !RENDERER_H