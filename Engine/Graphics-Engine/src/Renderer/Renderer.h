#ifndef RENDERER_H
#define RENDERER_H

#include "Tools/Includes.h"
#include "stb_image/stb_image.h"

#define TRPOS6 6
#define TRPOS3 3

using namespace glm;
using namespace std;

enum ShaderType
{
	None = -1,
	Main,
	LightSource,
	Size
};

struct GENGINE_API FrustumData
{
	float verticalFOV = 45.0f;
	float width = 1280.0f;
	float height = 720.0f;
	float near = 0.1f;
	float far = 100.0f;
};

struct GENGINE_API Shader
{
	ShaderType type;
	unsigned int programID;
};

struct GENGINE_API VPMatrix
{
	mat4 view;
	mat4 projection;
	vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
	vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
};

class GENGINE_API Renderer
{
	unsigned int positionAttributeLocation;
	unsigned int colorAttribute;
	unsigned int normalAttributeLocation;

	FrustumData frustumData;
	float aspect;

	vec3 backgroundColor;

	int currentShader = ShaderType::None;
	Shader shaders[ShaderType::Size];

	VPMatrix vpMatrix;
public:
	//Renderer(float fov, float windowWidth, float windowHeight, float near, float far);
	Renderer(FrustumData frustum);
	~Renderer();

#pragma region Perspective
	FrustumData getFrustumData();
	float getAspect();
#pragma endregion

#pragma region Background
	void setBackgroundColor(vec3 value);
	vec3 getBackgroundColor();
	void clearBackground();
#pragma endregion

#pragma region Vertices
	void drawArrays(unsigned int vao, unsigned int vbo, int vertexAmount);
	void drawElements(unsigned int vao, unsigned int vbo, unsigned int ebo, int indexAmount);
#pragma endregion

#pragma region MVP
	void setModel(unsigned int _shaderProgram, mat4 model);
	void setView(mat4 view);
	void setProjection(mat4 projection);
	mat4 getProjection();
	void updateProjection(mat4 &projection);
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