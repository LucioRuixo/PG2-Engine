#include "Renderer.h"

//Renderer::Renderer(float fov, float windowWidth, float windowHeight, float near, float far)
Renderer::Renderer(FrustumData frustum)
{
	unsigned int _posAttrib = 0;
	unsigned int _colorAttrib = 1;

	frustumData = frustum;
	aspect = frustumData.width / frustumData.height;

	backgroundColor = vec3(0.025f, 0.025f, 0.025f);

	for (int i = 0; i < ShaderType::Size; i++)
	{
		shaders[i].type = (ShaderType)i;
		shaders[i].programID = 0;
	}
}

Renderer::~Renderer() {}

#pragma region Perspective
FrustumData Renderer::getFrustumData() { return frustumData; }

float Renderer::getAspect() { return aspect; }
#pragma endregion

#pragma region Background
void Renderer::setBackgroundColor(vec3 value) { backgroundColor = value; }
vec3 Renderer::getBackgroundColor() { return backgroundColor; }

void Renderer::clearBackground()
{
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
#pragma endregion

#pragma region Vertices
void Renderer::drawArrays(unsigned int vao, unsigned int vbo, int vertexAmount)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glDrawArrays(GL_TRIANGLES, 0, vertexAmount);
}

void Renderer::drawElements(unsigned int vao, unsigned int vbo, unsigned int ebo, int indexAmount)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glDrawElements(GL_TRIANGLES, indexAmount, GL_UNSIGNED_INT, nullptr);
}
#pragma endregion

#pragma region MVP
void Renderer::setModel(unsigned int shaderProgram, mat4 model)
{
	unsigned int modelLocation = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));
}

void Renderer::setView(mat4 view)
{
	ShaderType currentShaderAux = getCurrentShader();

	for (int i = 0; i < ShaderType::Size; i++)
	{
		useShader((ShaderType)i);

		unsigned int viewLocation = glGetUniformLocation(shaders[i].programID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));
	}

	useShader(currentShaderAux);
}

void Renderer::setProjection(mat4 projection)
{
	ShaderType currentShaderAux = getCurrentShader();
	updateProjection(projection);

	for (int i = 0; i < ShaderType::Size; i++)
	{
		useShader((ShaderType)i);

		unsigned int projectionLocation = glGetUniformLocation(shaders[i].programID, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));
	}

	useShader(currentShaderAux);
}
mat4 Renderer::getProjection() { return vpMatrix.projection; }

void Renderer::updateProjection(mat4 &projection)
{
	projection = perspective(radians(frustumData.verticalFOV), aspect, frustumData.near, frustumData.far);
	//projection = ortho(0.0f, 1280.0f, 0.0f, 720.0f);
}
#pragma endregion

#pragma region Shaders
unsigned int Renderer::compileShader(unsigned int type, const char* source)
{
	unsigned int id = glCreateShader(type);

	std::string sourceShaderCode;
	std::ifstream sourceShaderFile;

	sourceShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		sourceShaderFile.open(source);
		std::stringstream sourceShaderStream;

		sourceShaderStream << sourceShaderFile.rdbuf();

		sourceShaderFile.close();

		sourceShaderCode = sourceShaderStream.str();
	}
	catch (std::ifstream::failure& e) { std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl; }

	const char* sourceCode = sourceShaderCode.c_str();

	glShaderSource(id, 1, &sourceCode, nullptr);
	glCompileShader(id);

	return id;
}

unsigned int Renderer::createShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	unsigned int programID = glCreateProgram();
	unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexPath);
	unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentPath);

	glAttachShader(programID, vertex);
	glAttachShader(programID, fragment);
	glLinkProgram(programID);
	glValidateProgram(programID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return programID;
}

void Renderer::setShaderProgram(ShaderType type, const char* vertexPath, const char* fragmentPath)
{
	unsigned int shaderProgram = createShaderProgram(vertexPath, fragmentPath);
	shaders[type].programID = shaderProgram;
}

unsigned int Renderer::getShaderProgram(ShaderType type)
{
	if (type == ShaderType::Size)
	{
		cout << "Invalid shader type" << endl;
		return 0;
	}
	else return shaders[type].programID;
}

void Renderer::useShader(ShaderType type)
{
	if (type == ShaderType::Size) return;

	currentShader = type;
	glUseProgram(shaders[type].programID);
}

ShaderType Renderer::getCurrentShader() { return (ShaderType)currentShader; }
#pragma endregion