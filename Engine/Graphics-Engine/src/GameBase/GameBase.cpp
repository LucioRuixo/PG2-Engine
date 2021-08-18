#include "GameBase.h"

void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length,
	const GLchar *message, const void *data)
{
	const char* _source;
	const char* _type;
	const char* _severity;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		_source = "API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		_source = "WINDOW SYSTEM";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		_source = "SHADER COMPILER";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		_source = "THIRD PARTY";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		_source = "APPLICATION";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		_source = "UNKNOWN";
		break;
	default:
		_source = "UNKNOWN";
		break;
	}

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		_type = "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		_type = "DEPRECATED BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		_type = "UDEFINED BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		_type = "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		_type = "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		_type = "OTHER";
		break;
	case GL_DEBUG_TYPE_MARKER:
		_type = "MARKER";
		break;
	default:
		_type = "UNKNOWN";
		break;
	}

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		_severity = "HIGH";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		_severity = "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		_severity = "LOW";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		_severity = "NOTIFICATION";
		break;
	default:
		_severity = "UNKNOWN";
		break;
	}

	if (_severity == "NOTIFICATION") return;

	printf("%d: %s of %s severity, raised from %s: %s\n",
		id, _type, _severity, _source, message);
}

GameBase::GameBase()
{
	if (!glfwInit())
	{
		std::cout << "Error: GLFW did not initialize" << std::endl;
		return;
	}

	window = new Window(1280, 720);
	renderer = new Renderer();
	camera = new Camera(renderer);
	textureManager = new TextureManager(renderer);
	modelManager = new ModelManager(textureManager);
	lightingManager = new LightingManager(renderer);
	input = new Input(window);
	time = new Time();

	if (!window)
	{
		std::cout << "Error: window is null" << std::endl;
		return;
	}

	window->validateWindow();
	window->makeContextCurrent();
	window->initializeGLEW();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEBUG_OUTPUT);
	//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(debugMessageCallback, 0);

	//Shader program
	renderer->setShaderProgram(ShaderType::Main, "../Graphics-Engine/res/shaders/MainShader_VS.shader", "../Graphics-Engine/res/shaders/MainShader_FS.shader");
	renderer->setShaderProgram(ShaderType::LightSource, "../Graphics-Engine/res/shaders/LightSourceShader_VS.shader", "../Graphics-Engine/res/shaders/LightSourceShader_FS.shader");
	renderer->useShader(ShaderType::Main);

	//Textures
	textureManager->initializeTextureValues();

	//Entities
	Entity::setRenderer(renderer);
	Entity::setTextureManager(textureManager);
	Plane::initializeRenderingObjects();
	Cube::initializeRenderingObjects();

	//Projection
	for (int i = 0; i < ShaderType::Size; i++) renderer->setProjection(renderer->getProjection());

	//Lighting
	lightingManager->initializeShaderValues();

	//Camera
	camera->getTransform()->setPosition(0.0f, 0.0f, 0.0f);
	camera->getTransform()->setRotation(0.0f, 180.0f, 0.0f);
}

GameBase::~GameBase()
{
	for (int i = 0; i < ShaderType::Size; i++) glDeleteProgram(renderer->getShaderProgram((ShaderType)i));
	window->terminateGLFW();

	if (window) delete window;
	if (renderer) delete renderer;
	if (camera) delete camera;
	if (textureManager) delete textureManager;
	if (modelManager) delete modelManager;
	if (lightingManager) delete lightingManager;
	if (input) delete input;
	if (time) delete time;
}

void GameBase::run()
{
	float elapsedTime = 0.0f;
	int framesInSecond = 0;

	initialize();

	while (!window->getWindowShouldClose())
	{
		renderer->clearBackground();

		renderer->useShader(ShaderType::Main);
		update();

		renderer->useShader(ShaderType::LightSource);
		for (int i = 0; i < MAX_POINT_LIGHT_AMOUNT; i++)
		{
			if (lightingManager->getPointLight(i)) lightingManager->getPointLight(i)->draw();
		}
		for (int i = 0; i < MAX_SPOTLIGHT_AMOUNT; i++)
		{
			if (lightingManager->getSpotlight(i)) lightingManager->getSpotlight(i)->draw();
		}

		time->tick();
		elapsedTime += time->getDeltaTime();
		framesInSecond++;
		if (elapsedTime >= 1.0f)
		{
			//std::cout << "FPS: " << round(1.0f / (elapsedTime / framesInSecond)) << std::endl;

			elapsedTime = 0.0f;
			framesInSecond = 0;
		}

		window->swapBuffers();
		window->pollEvents();
	}

	terminate();
}