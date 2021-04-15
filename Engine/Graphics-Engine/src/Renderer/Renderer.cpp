#include "Renderer.h"

Renderer::Renderer()
{
	unsigned int _posAttrib = 0;
	unsigned int _colorAttrib = 1;

	backgroundColor = vec3(0.05f, 0.05f, 0.05f);
}

Renderer::~Renderer()
{
	glDeleteTextures(1, &texture);
}

unsigned int& Renderer::getShaderProgram() { return shaderProgram; }

void Renderer::createVBO()
{
	glGenBuffers(1, &VBO);
}

void Renderer::createEBO()
{
	glGenVertexArrays(1, &EBO);
}

void Renderer::bindVBO(unsigned int _VBO)
{
	VBO = _VBO;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Renderer::bindEBO(unsigned int _EBO)
{
	EBO = _EBO;
	glBindVertexArray(EBO);
}

unsigned int Renderer::getVBO() { return VBO; }

unsigned int Renderer::getEBO() { return EBO; }

void Renderer::setBufferData(int size, float* vertexBuffer)
{
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertexBuffer, GL_DYNAMIC_DRAW);
}

void Renderer::clearBackground()
{
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setShader()
{
	shaderProgram = createShaderProgram("../Graphics-Engine/res/shaders/shader-vs.shader", "../Graphics-Engine/res/shaders/shader-fs.shader");
}

//---------------------
void Renderer::generateTexture()
{
	stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Renderer::setParameterTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE);
}

//---------------------
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

	const char* srcCode = sourceShaderCode.c_str();

	glShaderSource(id, 1, &srcCode, nullptr);
	glCompileShader(id);

	return id;
}

int Renderer::createShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	unsigned int sProgram = glCreateProgram();
	unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexPath);
	unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentPath);

	glAttachShader(sProgram, vertex);
	glAttachShader(sProgram, fragment);
	glLinkProgram(sProgram);
	glValidateProgram(sProgram);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return sProgram;
}

void Renderer::setModel(unsigned int _shaderProgram, mat4 model)
{
	unsigned int modelLocation = glGetUniformLocation(_shaderProgram, "model");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));
}

void Renderer::setProjection(unsigned int _shaderProgram, mat4 projection)
{
	unsigned int projectionLocation = glGetUniformLocation(_shaderProgram, "projection");

	updateProjection(projection);

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));
}

void Renderer::updateProjection(mat4& projection)
{
	projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	//projection = ortho(0.0f, 1280.0f, 0.0f, 720.0f);
}

void Renderer::setView(unsigned int _shaderProgram, mat4 view)
{
	unsigned int viewLocation = glGetUniformLocation(_shaderProgram, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));
}

//mat4 Renderer::getView() { return _VP.view; }

mat4 Renderer::getProjection() { return _VP.projection; }

//vec3 Renderer::getCameraPos() { return _VP.cameraPos; }
//
//vec3 Renderer::getCameraFront() { return _VP.cameraFront; }
//
//vec3 Renderer::getCameraUp() { return _VP.cameraUp; }

void Renderer::setVertexAttributes()
{
	//Position
	positionAttribute = glGetAttribLocation(shaderProgram, "aPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//Color
	colorAttribute = glGetAttribLocation(shaderProgram, "aColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Normal
	normalAttribute = glGetAttribLocation(shaderProgram, "aNormal");
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Texture coordinates
	glUniform1i(glGetUniformLocation(shaderProgram, "textureData"), 0);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);
}

void Renderer::updateUnifornTexture() {}

void Renderer::drawTriangles(int vertexAmount)
{
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawArrays(GL_TRIANGLES, 0, vertexAmount);
}

void Renderer::setBackgroundColor(vec3 value) { backgroundColor = value; }

vec3 Renderer::getBackgroundColor() { return backgroundColor; }