#include "GameBase.h"

GameBase::GameBase() {
	glfwInit();
	translationX = 0.0f;
	translationY = 0.0f;
	translationZ = 0.0f;
	rotateX = 0.0f;
	rotateY = 0.0f;
	rotateZ = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;

	window = new Window();
	renderer = new Renderer();
	camera = new Camera(renderer);
	lighting = new Lighting(renderer);
	input = new Input(window);
	time = new Time();

	//if (!glfwInit() || window == NULL) return -1;

	window->createWindowValidate();
	window->createContexCurrent();
	window->initGLEW();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Create VBO
	renderer->createVBO();
	//Create Tr
	renderer->bindVBO(renderer->getVBO());
	renderer->setVertexAttrib();
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
 
GameBase::~GameBase() {
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
		update();

		time->Tick();

		//Print FPS
		//std::cout << "FPS: " << 1.0 / time->DeltaTime() << std::endl;

		window->swapBuffers();
		window->pollEvents();
	}

	terminate();
}