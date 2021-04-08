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

	//Ambient light
	lighting->setAmbientLightColor(lighting->getAmbientLightColor());
	lighting->setAmbientLightStrength(lighting->getAmbientLightStrength());
	lighting->setSpecularStrength(lighting->getSpecularStrength());
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

		//Test de specular
		//--------------
		//vec3 fragmentPosition = vec3(0.0f, 3.0f, -7.5f);
		//vec3 lightSourcePosition = lighting->getLightSourcePosition();
		//vec3 lightSourceDirection = normalize(lightSourcePosition - fragmentPosition);
		//
		//vec3 nNormal = vec3(0.0f, 0.0f, 1.0f);
		//
		//vec3 cameraPosition = camera->transform->position;
		//vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
		//vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);
		//std::cout << "cameraPosition: " << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << std::endl;
		//std::cout << "viewDirection: " << viewDirection.x << ", " << viewDirection.y << ", " << viewDirection.z << std::endl;
		//std::cout << "reflectDirection: " << reflectDirection.x << ", " << reflectDirection.y << ", " << reflectDirection.z << std::endl;
		//
		//float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
		//std::cout << "specularImpact: " << specularImpact << std::endl << std::endl;
		//--------------

		time->Tick();

		//Print FPS
		//std::cout << "FPS: " << 1.0 / time->DeltaTime() << std::endl;

		window->swapBuffers();
		window->pollEvents();
	}

	terminate();
}