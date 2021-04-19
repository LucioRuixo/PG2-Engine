#ifndef RENDERER_H
#define RENDERER_H

#include "Tools/Includes.h"
#include "stb_image/stb_image.h"

#define TRPOS6 6
#define TRPOS3 3

using namespace glm;

struct matrixVP
{
	mat4 view;
	mat4 projection;
	vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
	vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
};

class GENGINE_API Renderer
{
private:
	unsigned int VBO;
	unsigned int EBO;
	unsigned int shaderProgram;
	unsigned int positionAttributeLocation;
	unsigned int colorAttribute;
	unsigned int normalAttributeLocation;
	unsigned int texture;

	vec3 backgroundColor;

	matrixVP _VP; //TODO: cambiar nombre
public:
	Renderer();
	~Renderer();

#pragma region Background
	void setBackgroundColor(vec3 value);
	vec3 getBackgroundColor();
	void clearBackground();
#pragma endregion

#pragma region Vertices
	void createVBO();
	void bindVBO(unsigned int _VBO);
	unsigned int getVBO();
	void createEBO();
	void bindEBO(unsigned int _EBO);
	unsigned int getEBO();
	void setBufferData(int tam, float* verterBuffer);
	void setVertexAttributes();
	void drawTriangles(int vertexAmount);
#pragma endregion

#pragma region MVP
	void setModel(unsigned int _shaderProgram, mat4 model);
	void setView(unsigned int _shaderProgram, mat4 view);
	void setProjection(unsigned int _shaderProgram, mat4 projection);
	mat4 getProjection();
	void updateProjection(mat4 &projection);
#pragma endregion

#pragma region Textures
	void generateTexture();
	void setParameterTexture();
#pragma endregion

#pragma region Shaders
	void setShader();
	unsigned int compileShader(unsigned int type, const char* source);
	int createShaderProgram(const char * vertexPath, const char * fragmentPath);
	unsigned int& getShaderProgram();
#pragma endregion
};

#endif // !RENDERER_H