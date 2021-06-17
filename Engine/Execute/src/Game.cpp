#include "Game.h"

bool spacePressed = false;
bool onePressed = false;
bool twoPressed = false;
bool threePressed = false;

float cameraMovementSpeed = 1.0f;
float cameraRotationSpeed = 50.0f;
float spriteScaleAddition = 0.1f;

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
Model* couch;
Model* sniperRifle;
Model* car;
Model* dagger;
Model* plant;
Model* bottle;
Model* pistol2;
Model* phone;

Game::Game() {}

Game::~Game() {}

int Game::initialize()
{
	//Sprite 1
	//sprite1 = new Sprite(textureManager, "res/Assets/gato 1.jpg", "gato 1");
	//sprite1->setPosition(1.0f, -0.5f, -10.0f);
	
	//Sprite 2
	//sprite2 = new Sprite(textureManager, "res/Assets/gato 2.jpg", "gato 2");
	//sprite2->setPosition(-1.0f, 0.0f, -3.0f);
	
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
	//tree = new Model(textureManager, "res/Assets/Modelos/Tree/Lowpoly_tree_sample.obj");
	//tree->setPosition(-2.0f, -0.25f, -1.0f);
	//tree->setScale(0.1f, 0.1f, 0.1f);
	
	//couch = new Model(textureManager, "res/Assets/Modelos/Couch/Couch.obj");
	//couch->setPosition(0.0f, 0.0f, -3.0f);
	
	//sniperRifle = new Model(textureManager, "res/Assets/Modelos/Sniper_Rifle/Sniper_Rifle.obj");
	//sniperRifle->setPosition(1.5f, 0.0f, -3.0f);

	//car = new Model(textureManager, "res/Assets/Modelos/Mustang/Mustang.obj");
	//car->setPosition(1.5f, 0.0f, -3.0f);

	dagger = new Model(textureManager, "res/Assets/Modelos/Dagger/source/Dagger.obj");
	dagger->setPosition(0.0f, 0.0f, -3.0f);
	dagger->setScale(0.01f, 0.01f, 0.01f);

	plant = new Model(textureManager, "res/Assets/Modelos/Plant/A1.obj");
	plant->setPosition(1.5f, 0.0f, -3.0f);
	
	//bottle = new Model(textureManager, "res/Assets/Modelos/Bottle/Jack Daniel Bottle.obj");
	//bottle->setPosition(1.0f, -0.25f, -1.0f);
	//bottle->setRotation(-90.0f, 0.0f, 0.0f);
	//bottle->setScale(0.1f, 0.1f, 0.1f);

	//pistol2 = new Model(textureManager, "res/Assets/Modelos/Pistol 2/source/drakefire_pistol_low.obj");
	//pistol2->setPosition(1.5f, 0.0f, -3.0f);

	//phone = new Model(textureManager, "res/Assets/Modelos/Phone/Iphone 12 Pro.obj");
	//phone->setPosition(1.5f, 0.0f, -3.0f);

	//Lighting
	lighting->addDirectionalLight(vec3(1.0f, -1.0f, 0.0f));

	lighting->addPointLight(1, vec3(0.0f, 0.0f, -2.5f));
	lighting->addPointLight(2, vec3(0.0f, 0.0f, -8.0f));

	lighting->addSpotlight(1, vec3(0.0f, 1.0f, -4.5f), vec3(0.0f, -1.0f, -1.0f));
	lighting->addSpotlight(2, vec3(0.0f, 1.0f, -12.0f), vec3(0.0f, 0.0f, -1.0f));
	
	return 0;
}

void Game::update()
{
#pragma region Input
	if (input->getKeyPress(FunctionKey::ESCAPE)) window->setWindowShouldClose(true);

	//Move camera
	//-----------
	if (input->getKeyPress(PrintableKey::D)) camera->translate(cameraMovementSpeed * time->DeltaTime(), 0.0f, 0.0f);
	if (input->getKeyPress(PrintableKey::A)) camera->translate(-cameraMovementSpeed * time->DeltaTime(), 0.0f, 0.0f);

	if (input->getKeyPress(PrintableKey::Z)) camera->translate(0.0f, cameraMovementSpeed * time->DeltaTime(), 0.0f);
	if (input->getKeyPress(PrintableKey::X)) camera->translate(0.0f, -cameraMovementSpeed * time->DeltaTime(), 0.0f);

	if (input->getKeyPress(PrintableKey::S)) camera->translate(0.0f, 0.0f, cameraMovementSpeed * time->DeltaTime());
	if (input->getKeyPress(PrintableKey::W)) camera->translate(0.0f, 0.0f, -cameraMovementSpeed * time->DeltaTime());
	//-----------

	//Rotate camera
	//-----------
	if (input->getKeyPress(FunctionKey::UP)) camera->rotate(cameraRotationSpeed * time->DeltaTime(), 0.0f, 0.0f);
	if (input->getKeyPress(FunctionKey::DOWN)) camera->rotate(-cameraRotationSpeed * time->DeltaTime(), 0.0f, 0.0f);
	
	if (input->getKeyPress(FunctionKey::RIGHT)) camera->rotate(0.0f, cameraRotationSpeed * time->DeltaTime(), 0.0f);
	if (input->getKeyPress(FunctionKey::LEFT)) camera->rotate(0.0f, -cameraRotationSpeed * time->DeltaTime(), 0.0f);
	//-----------

	//Turn on/off light
	//-----------
	//if (input->getKeyPress(PrintableKey::SPACE) && !spacePressed)
	//{
	//	spacePressed = true;
	//
	//	if (lighting->getLightSourceActive()) lighting->setLightSourceActive(false);
	//	else lighting->setLightSourceActive(true);
	//}
	//else if (input->getKeyRelease(PrintableKey::SPACE)) spacePressed = false;
	//-----------

	//Change light type
	//-----------
	//if (input->getKeyPress(FunctionKey::KP_1) && !onePressed)
	//{
	//	onePressed = true;
	//	lighting->getLightSource()->setType(LightType::Directional);
	//}
	//else if (input->getKeyRelease(FunctionKey::KP_1)) onePressed = false;
	//
	//if (input->getKeyPress(FunctionKey::KP_2) && !twoPressed)
	//{
	//	twoPressed = true;
	//	lighting->getLightSource()->setType(LightType::Point);
	//}
	//else if (input->getKeyRelease(FunctionKey::KP_2)) twoPressed = false;
	//
	//if (input->getKeyPress(FunctionKey::KP_3) && !threePressed)
	//{
	//	threePressed = true;
	//	lighting->getLightSource()->setType(LightType::Spot);
	//}
	//else if (input->getKeyRelease(FunctionKey::KP_3)) threePressed = false;
	//-----------
#pragma endregion

#pragma region Rendering
	//sprite1->draw();
	//sprite2->draw();
	
	cube->draw();
	cube2->draw();
	
	rubyCube->draw();
	emeraldCube->draw();
	goldCube->draw();

	//tree->draw();
	//couch->draw();
	//sniperRifle->draw();
	//car->draw();
	dagger->draw();
	//bottle->draw();
	//pistol2->draw();
	//phone->draw();
	plant->draw();
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