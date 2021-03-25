#include "Renderer.h"

Renderer::Renderer() {
	unsigned int _posAttrib = 0;
	unsigned int _colorAttrib = 1;
}

Renderer::~Renderer() {
	glDeleteTextures(1, &texture);
}

unsigned int& Renderer::getShaderProgram() {
	return shaderProgram;
}

void Renderer::createVBO() {
	glGenBuffers(1, &VBO);
}

void Renderer::createEBO() {
	glGenVertexArrays(1, &EBO);
}

void Renderer::bindVBO(unsigned int _VBO) {
	VBO = _VBO;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Renderer::bindEBO(unsigned int _EBO) {
	EBO = _EBO;
	glBindVertexArray(EBO);
}

unsigned int Renderer::getVBO() {
	return VBO;
}

unsigned int Renderer::getEBO() {
	return EBO;
}

void Renderer::setBufferData(int tam, float* vertexBuffer) {
	glBufferData(GL_ARRAY_BUFFER, tam * sizeof(float), vertexBuffer, GL_DYNAMIC_DRAW);
}

void Renderer::clearBackground() {
	glClearColor(0.5f, 0.2f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setShader() {
	shaderProgram = createShaderProgram("../Graphics-Engine/res/shaders/shader-vs.shader","../Graphics-Engine/res/shaders/shader-fs.shader");
}

//---------------------
void Renderer::generateTexture() {
	stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}
void Renderer::setParameterTexture() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE);
}
//---------------------

unsigned int Renderer::compileShader(unsigned int type, const char* source) {
	unsigned int id = glCreateShader(type);

	std::string sourceShaderCode;

	std::ifstream sourceShaderFile;

	sourceShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		sourceShaderFile.open(source);
		std::stringstream sourceShaderStream;

		sourceShaderStream << sourceShaderFile.rdbuf();

		sourceShaderFile.close();

		sourceShaderCode = sourceShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* srcCode = sourceShaderCode.c_str();

	glShaderSource(id, 1, &srcCode, nullptr);
	glCompileShader(id);

	return id;
}

int Renderer::createShaderProgram(const char* vertexPath, const char* fragmentPath) {
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

void Renderer::setModel(unsigned int& _shaderProg, glm::mat4 model) {
	unsigned int modelLoc = glGetUniformLocation(_shaderProg, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void Renderer::setProj(unsigned int& _shaderProg, glm::mat4 projection) {
	unsigned int projectionLoc = glGetUniformLocation(_shaderProg, "projection");

	updateProj(projection);

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::updateProj(glm::mat4 projection) {
	//projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
}

void Renderer::setView(unsigned int& _shaderProg, glm::mat4 view) {
	unsigned int viewLoc = glGetUniformLocation(_shaderProg, "view");

	updateView(view);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void Renderer::updateView(glm::mat4 view) {
	view = glm::lookAt(getCameraPos(), getCameraPos() + getCameraFront(), getCameraUp());
}

glm::mat4 Renderer::getView() {
	return _VP.view;
}

glm::mat4 Renderer::getProj() {
	return _VP.projection;
}

glm::vec3 Renderer::getCameraPos() {
	return _VP.cameraPos;
}

glm::vec3 Renderer::getCameraFront() {
	return _VP.cameraFront;
}

glm::vec3 Renderer::getCameraUp() {
	return _VP.cameraUp;
}

void Renderer::setVertexAttrib() {
	_posAttrib = glGetAttribLocation(shaderProgram, "aPos");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	_colorAttrib = glGetAttribLocation(shaderProgram, "aColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture coord
	glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void Renderer::updateUnifornTexture() {
	
}

void Renderer::drawTriangles() {
	glDrawArrays(GL_TRIANGLES, 0, 6);
}