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

	//Ambient light
	lighting->setAmbientLightColor(lighting->getAmbientLightColor());
	lighting->setAmbientLightStrenth(lighting->getAmbientLightStrenth());
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
	initialize();

	while (!window->detecWindowShouldClose())
	{
		renderer->clearBackground();

		update();

		time->Tick();

		//Print FPS
		//std::cout << "FPS: " << 1.0 / time->DeltaTime() << std::endl;

		window->swapBuffers();
		window->pollEvents();
	}

	terminate();
}