#include "GameBase.h"

GameBase::GameBase() {
	glfwInit();
	transX = 0.0f;
	transY = 0.0f;
	transZ = 0.0f;
	rotateX = 0.0f;
	rotateY = 0.0f;
	rotateZ = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;

	window = new Window();
	input = new Input(window);
	renderer = new Renderer();
	time = new Time();

	//if (!glfwInit() || window == NULL) return -1;

	window->createWindowValidate();
	window->createContexCurrent();
	window->initGLEW();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//create VBO
	renderer->createVBO();
	//create Tr
	renderer->bindVBO(renderer->getVBO());
	renderer->setVertexAttrib();
	//shader
	renderer->setShader();
	//Set texture
	renderer->generateTexture();
	renderer->setParameterTexture();
	//------
	glUseProgram(renderer->getShaderProgram());
}

GameBase::~GameBase() {
	glDeleteProgram(renderer->getShaderProgram());
	window->glfwTerminate();

	if (window) delete window;
	if (input) delete input;
	if (renderer) delete renderer;
	if (time) delete time;
}

void GameBase::run()
{
	initialize();

	while (!window->detecWindowShouldClose())
	{
		update();

		time->Tick();
		//std::cout << "FPS: " << 1.0 / time->DeltaTime() << std::endl;

		window->swapBuffers();
		window->pollEvents();
	}

	terminate();
}