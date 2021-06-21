#include "Game.h"

bool onePressed = false;
bool twoPressed = false;
bool threePressed = false;
bool fourPressed = false;
bool fivePressed = false;

float cameraMovementSpeed = 1.0f;
float cameraRotationSpeed = 50.0f;
float spriteScaleAddition = 0.1f;

float treeYRotation = 0.0f;
float treeRotationSpeed = 50.0f;
float daggerYRotation = 0.0f;
float daggerRotationSpeed = 50.0f;
float sniperRifleYRotation = 0.0f;
float sniperRifleRotationSpeed = 50.0f;
float plantYRotation = 0.0f;
float plantRotationSpeed = 50.0f;
float alarakYRotation = 0.0f;
float alarakRotationSpeed = 50.0f;

vec3 lightSourcePosition = vec3(0.0f, 2.0f, -4.5f);
vec3 cameraMovement;
vec3 cameraRotation;

Sprite* sprite1;
Sprite* sprite2;

Cube* cube;
Cube* cube2;
Cube* rubyCube;
Cube* emeraldCube;
Cube* goldCube;

Model* tree;
Model* dagger;
Model* sniperRifle;
Model* plant;
Model* alarak;

Game::Game() {}

Game::~Game() {}

int Game::initialize()
{
	//Sprite 1
	//sprite1 = new Sprite(textureManager, "res/Assets/gato 1.jpg", "gato 1");
	//sprite1->setPosition(1.0f, -0.5f, -10.0f);
	
	//Sprite 2
	sprite2 = new Sprite(textureManager, "res/Assets/gato 2.jpg", "gato 2");
	sprite2->setPosition(-1.0f, 0.0f, -3.0f);
	
	//Cube
	cube = new Cube(vec3(1.0f, 0.1f, 0.1f));
	cube->setPosition(0.75f, 0.0f, -6.5f);
	
	//Cube 2
	cube2 = new Cube(vec3(0.1f, 0.1f, 1.0f));
	cube2->setPosition(-1.5f, -3.0f, -9.5f);
	cube2->setScale(3.0f, 3.0f, 3.0f);
	
	//Material cubes
	Material ruby;
	ruby.diffuse = vec3(0.61424f, 0.04136f, 0.04136f);
	ruby.specular = vec3(0.727811f, 0.626959f, 0.626959f);
	ruby.shininess = 0.6f;
	rubyCube = new Cube(vec3(0.607f, 0.066f, 0.117f), ruby);
	rubyCube->setPosition(-1.0f, 1.0f, -15.0f);
	rubyCube->setScale(1.0f, 3.0f, 1.0f);
	
	Material emerald;
	emerald.diffuse = vec3(0.07568f, 0.61424f, 0.07568f);
	emerald.specular = vec3(0.633f, 0.727811f, 0.633f);
	emerald.shininess = 0.6f;
	emeraldCube = new Cube(vec3(0.031f, 0.396f, 0.133f), emerald);
	emeraldCube->setPosition(0.0f, 1.0f, -15.0f);
	emeraldCube->setScale(1.0f, 3.0f, 1.0f);
	
	Material gold;
	gold.diffuse = vec3(0.75164f, 0.60648f, 0.22648f);
	gold.specular = vec3(0.628281f, 0.555802f, 0.366065f);
	gold.shininess = 0.4f;
	goldCube = new Cube(vec3(0.905f, 0.741f, 0.258f), gold);
	goldCube->setPosition(1.0f, 1.0f, -15.0f);
	goldCube->setScale(1.0f, 3.0f, 1.0f);

	//Models
	tree = new Model(textureManager, "res/Assets/Modelos/Tree/Lowpoly_tree_sample.obj");
	tree->setPosition(-3.0f, -1.0f, -4.0f);
	tree->setScale(0.075f, 0.075f, 0.075f);

	dagger = new Model(textureManager, "res/Assets/Modelos/Dagger/source/Dagger.obj");
	dagger->setPosition(-1.5f, 0.0f, -4.0f);
	dagger->setScale(0.005f, 0.005f, 0.005f);
	
	sniperRifle = new Model(textureManager, "res/Assets/Modelos/Sniper Rifle/OBJ/Sniper_Rifle.obj");
	sniperRifle->setPosition(0.0f, 0.5f, -4.0f);
	sniperRifle->setScale(0.25f, 0.25f, 0.25f);

	plant = new Model(textureManager, "res/Assets/Modelos/Plant/A1.obj");
	plant->setPosition(1.5f, -1.0f, -4.0f);

	alarak = new Model(textureManager, "res/Assets/Modelos/Alarak/source/Alarak-Protoss/Alarak VR.fbx");
	alarak->setPosition(-1.5f, -1.0f, -9.0f);

	//Lighting
	lightingManager->addDirectionalLight(vec3(1.0f, -1.0f, 0.0f));

	lightingManager->addPointLight(0, vec3(0.0f, 0.0f, -12.0f));
	lightingManager->addPointLight(1, vec3(0.0f, 0.0f, -8.0f));

	lightingManager->addSpotlight(0, vec3(0.0f, 1.0f, -4.5f), vec3(0.0f, -1.0f, -1.0f));
	lightingManager->addSpotlight(1, vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f));
	
	return 0;
}

void Game::update()
{
#pragma region Input
	if (input->getKeyPress(FunctionKey::ESCAPE)) window->setWindowShouldClose(true);

	//Move camera
	//-----------
	if (input->getKeyPress(PrintableKey::D)) camera->translate(cameraMovementSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	if (input->getKeyPress(PrintableKey::A)) camera->translate(-cameraMovementSpeed * time->getDeltaTime(), 0.0f, 0.0f);

	if (input->getKeyPress(PrintableKey::Z)) camera->translate(0.0f, cameraMovementSpeed * time->getDeltaTime(), 0.0f);
	if (input->getKeyPress(PrintableKey::X)) camera->translate(0.0f, -cameraMovementSpeed * time->getDeltaTime(), 0.0f);

	if (input->getKeyPress(PrintableKey::S)) camera->translate(0.0f, 0.0f, cameraMovementSpeed * time->getDeltaTime());
	if (input->getKeyPress(PrintableKey::W)) camera->translate(0.0f, 0.0f, -cameraMovementSpeed * time->getDeltaTime());
	//-----------

	//Rotate camera
	//-----------
	if (input->getKeyPress(FunctionKey::UP)) camera->rotate(cameraRotationSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	if (input->getKeyPress(FunctionKey::DOWN)) camera->rotate(-cameraRotationSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	
	if (input->getKeyPress(FunctionKey::RIGHT)) camera->rotate(0.0f, cameraRotationSpeed * time->getDeltaTime(), 0.0f);
	if (input->getKeyPress(FunctionKey::LEFT)) camera->rotate(0.0f, -cameraRotationSpeed * time->getDeltaTime(), 0.0f);
	//-----------

	//Turn on/off light
	//-----------
	if (input->getKeyPress(PrintableKey::ONE) && !onePressed)
	{
		onePressed = true;
		lightingManager->getDirectionalLight()->setOn(!lightingManager->getDirectionalLight()->getOn());
	}
	else if (input->getKeyRelease(PrintableKey::ONE)) onePressed = false;
	
	if (input->getKeyPress(PrintableKey::TWO) && !twoPressed)
	{
		twoPressed = true;
		lightingManager->getPointLight(0)->setOn(!lightingManager->getPointLight(0)->getOn());
	}
	else if (input->getKeyRelease(PrintableKey::TWO)) twoPressed = false;
	
	if (input->getKeyPress(PrintableKey::THREE) && !threePressed)
	{
		threePressed = true;
		lightingManager->getPointLight(1)->setOn(!lightingManager->getPointLight(1)->getOn());
	}
	else if (input->getKeyRelease(PrintableKey::THREE)) threePressed = false;

	if (input->getKeyPress(PrintableKey::FOUR) && !fourPressed)
	{
		fourPressed = true;
		lightingManager->getSpotlight(0)->setOn(!lightingManager->getSpotlight(0)->getOn());
	}
	else if (input->getKeyRelease(PrintableKey::FOUR)) fourPressed = false;

	if (input->getKeyPress(PrintableKey::FIVE) && !fivePressed)
	{
		fivePressed = true;
		lightingManager->getSpotlight(1)->setOn(!lightingManager->getSpotlight(1)->getOn());
	}
	else if (input->getKeyRelease(PrintableKey::FIVE)) fivePressed = false;
	//-----------
#pragma endregion

#pragma region Transformations
	treeYRotation += treeRotationSpeed * time->getDeltaTime();
	tree->setRotation(0.0f, treeYRotation, 0.0f);

	daggerYRotation += daggerRotationSpeed * time->getDeltaTime();
	dagger->setRotation(0.0f, daggerYRotation, -90.0f);

	sniperRifleYRotation += sniperRifleRotationSpeed * time->getDeltaTime();
	sniperRifle->setRotation(0.0f, sniperRifleYRotation, -90.0f);

	plantYRotation += plantRotationSpeed * time->getDeltaTime();
	plant->setRotation(0.0f, plantYRotation, 0.0f);

	alarakYRotation += alarakRotationSpeed * time->getDeltaTime();
	alarak->setRotation(-90.0f, 0.0f, alarakYRotation);
#pragma endregion

#pragma region Rendering
	//sprite1->draw();
	//sprite2->draw();
	
	cube->draw();
	cube2->draw();
	
	rubyCube->draw();
	emeraldCube->draw();
	goldCube->draw();

	tree->draw();
	dagger->draw();
	sniperRifle->draw();
	plant->draw();
	alarak->draw();
#pragma endregion
}

int Game::terminate()
{
	if (sprite1) delete sprite1;
	if (sprite2) delete sprite2;
	if (cube) delete cube;
	if (rubyCube) delete rubyCube;
	if (emeraldCube) delete emeraldCube;
	if (goldCube) delete goldCube;
	if (tree) delete tree;

	return 0;
}