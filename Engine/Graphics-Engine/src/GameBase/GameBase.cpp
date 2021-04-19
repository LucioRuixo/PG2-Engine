#include "GameBase.h"

GameBase::GameBase()
{
	if (!glfwInit())
	{
		std::cout << "Error: GLFW did not initialize" << std::endl;
		return;
	}

	window = new Window();
	renderer = new Renderer();
	camera = new Camera(renderer);
	lighting = new Lighting(renderer);
	input = new Input(window);
	time = new Time();

	if (!window)
	{
		std::cout << "Error: window is null" << std::endl;
		return;
	}

	window->createWindowValidate();
	window->createContexCurrent();
	window->initGLEW();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Create VBO
	renderer->createVBO();
	renderer->bindVBO(renderer->getVBO());
	renderer->setVertexAttributes();

	//Shader
	renderer->setShader();

	//Set texture
	renderer->generateTexture();
	renderer->setParameterTexture();
	//------
	glUseProgram(renderer->getShaderProgram());

	//Projection
	renderer->setProjection(renderer->getShaderProgram(), renderer->getProjection());

	//Camera
	camera->setPosition(0.0f, 0.0f, 0.0f);
}
 
GameBase::~GameBase()
{
	glDeleteProgram(renderer->getShaderProgram());
	window->glfwTerminate();

	if (window) delete window;
	if (renderer) delete renderer;
	if (camera) delete camera;
	if (lighting) delete lighting;
	if (input) delete input;
	if (time) delete time;
}

void GameBase::run()
{
	float elapsedTime = 0.0f;
	int framesInSecond = 0;

	initialize();

	while (!window->detecWindowShouldClose())
	{
		renderer->clearBackground();

		update();

		if (lighting->getLightSourceActive())
		{
			lighting->getLightSourceIcon()->loadTexture();
			lighting->getLightSourceIcon()->draw();
		}

		time->Tick();
		elapsedTime += time->DeltaTime();
		framesInSecond++;
		if (elapsedTime >= 1.0f)
		{
			std::cout << "FPS: " << (int)(1.0f / (elapsedTime / framesInSecond)) << std::endl;

			elapsedTime = 0.0f;
			framesInSecond = 0;
		}

		window->swapBuffers();
		window->pollEvents();
	}

	terminate();
}