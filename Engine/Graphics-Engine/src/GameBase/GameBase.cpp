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

	//Shader program
	renderer->setShaderProgram(ShaderType::Main, "../Graphics-Engine/res/shaders/MainShader_VS.shader", "../Graphics-Engine/res/shaders/MainShader_FS.shader");
	renderer->setShaderProgram(ShaderType::LightSource, "../Graphics-Engine/res/shaders/LightSourceShader_VS.shader", "../Graphics-Engine/res/shaders/LightSourceShader_FS.shader");

	//Create VBO
	renderer->createVBO();
	renderer->bindVBO(renderer->getVBO());
	renderer->setVertexAttributes();

	//Set texture
	renderer->generateTexture();
	renderer->setParameterTexture();

	//Projection
	for (int i = 0; i < ShaderType::Size; i++) renderer->setProjection(renderer->getProjection());

	//Camera
	renderer->useShader(ShaderType::Main);
	camera->setPosition(0.0f, 0.0f, 0.0f);
}

GameBase::~GameBase()
{
	for (int i = 0; i < ShaderType::Size; i++)
	{
		glDeleteProgram(renderer->getShaderProgram((ShaderType)i));
	}
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

		renderer->useShader(ShaderType::Main);
		update();

		renderer->useShader(ShaderType::LightSource);
		if (lighting->getLightSourceActive()) lighting->getLightSource()->draw();

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