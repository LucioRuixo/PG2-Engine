#ifndef RENDERER_H
#define RENDERER_H

#include "../Tools/Includes.h"
#include "../stb_image/stb_image.h"

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
	unsigned int positionAttribute;
	unsigned int colorAttribute;
	unsigned int normalAttribute;
	unsigned int texture;

	vec3 backgroundColor;

	matrixVP _VP;
public:
	Renderer();
	~Renderer();
	unsigned int& getShaderProgram();
	void createVBO();
	void createEBO();
	void bindVBO(unsigned int _VBO);
	void bindEBO(unsigned int _EBO);
	unsigned int getVBO();
	unsigned int getEBO();
	void setBufferData(int tam, /*float* verterBuffer*/float vertexBuffer[]);
	void clearBackground();
	void setShader();
	//---------------
	void generateTexture();
	void setParameterTexture();
	//---------------
	unsigned int compileShader(unsigned int type, const char* source);
	int createShaderProgram(const char * vertexPath, const char * fragmentPath);
	void setModel(unsigned int/*&*/ _shaderProgram, mat4 model);
	void setProjection(unsigned int/*&*/ _shaderProgram, mat4 projection);
	void updateProjection(mat4 &projection);
	void setView(unsigned int/*&*/ _shaderProgram, mat4 view);
	void updateView(mat4 view);
	mat4 getView();
	mat4 getProjection();
	vec3 getCameraPos();
	vec3 getCameraFront();
	vec3 getCameraUp();
	void setVertexAttributes();
	void updateUnifornTexture();
	void drawTriangles(int vertexAmount);
	void setBackgroundColor(vec3 value);
	vec3 getBackgroundColor();
};

#endif // !RENDERER_H