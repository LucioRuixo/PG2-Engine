#include "Game.h"

float cameraMovementSpeed = 1.0f;
float cameraRotationSpeed = 50.0f;
float spriteScaleAddition = 0.1f;

vec3 cameraMovement;
vec3 cameraRotation;

Sprite* sprite1;
Sprite* sprite2;
Cube* cube1;
Cube* cube2;

Game::Game() {}

Game::~Game() {}

int Game::initialize()
{
	//Sprite 1
	sprite1 = new Sprite(renderer);
	sprite1->setTexture("res/Assets/gato 1.jpg", GL_RGB);
	sprite1->setPosition(1.0f, 0.0f, -6.0f);

	//Animation* animation = new Animation();
	//animation->addFrame(0.0f, 0.0f, 640.0f, 360.0f, 1280.0f, 720.0f, 4.0f, 4, 2);
	//animation->addAnimation();
	//animation->setCurrentAnimation(0);
	//sprite1->setAnimation(animation);

	//Sprite 2
	sprite2 = new Sprite(renderer);
	sprite2->setTexture("res/Assets/gato 2.jpg", GL_RGB);
	sprite2->setPosition(-1.0f, 0.0f, -3.0f);

	//Cube 1
	cube1 = new Cube(renderer);
	cube1->setPosition(-1.0f, 1.5f, -3.5f);

	//Cube 2
	cube2 = new Cube(renderer);
	cube2->setPosition(2.5f, 0.5f, -10.0f);
	cube2->setScale(2.0f, 2.0f, 2.0f);

	//Lighting
	lighting->enableLightSource(vec3(0.75f, 0.75f, 0.75f), vec3(0.0f, 2.0f, -4.5f));

	return 0;
}

void Game::update()
{
	if (input->getKeyPress(FunctionKey::ESCAPE)) window->setWindowShouldClose(true);

	//Move camera
	//-----------
	if (input->getKeyPress(PrintableKey::D)) camera->translate(cameraMovementSpeed * time->DeltaTime(), 0.0f, 0.0f);
	if (input->getKeyPress(PrintableKey::A)) camera->translate(-cameraMovementSpeed * time->DeltaTime(), 0.0f, 0.0f);

	if (input->getKeyPress(PrintableKey::X)) camera->translate(0.0f, cameraMovementSpeed * time->DeltaTime(), 0.0f);
	if (input->getKeyPress(PrintableKey::Z)) camera->translate(0.0f, -cameraMovementSpeed * time->DeltaTime(), 0.0f);

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
	
	//Scale sprite 1
	//if (input->getKeyPress(FunctionKey::UP))
	//	sprite1->setScale(sprite1->transform->scale.x + spriteScaleAddition, sprite1->transform->scale.y + spriteScaleAddition, sprite1->transform->scale.z + spriteScaleAddition);
	//if (input->getKeyPress(FunctionKey::DOWN))
	//	sprite1->setScale(sprite1->transform->scale.x - spriteScaleAddition, sprite1->transform->scale.y - spriteScaleAddition, sprite1->transform->scale.z - spriteScaleAddition);

	//------
	//Tile Map
	//tileMap->draw(renderer);

	//------
	//Player
	//playerSprite->Translate(transX, transY, transZ);

	sprite1->loadTexture();
	sprite1->draw();

	sprite2->loadTexture();
	sprite2->draw();

	cube1->draw();
	cube2->draw();

	//------
	//Sprite
	//Sprite load texture
	//sprite->loadTexture("res/assets/AprobamePorfa.jpg", RGB);
	//
	////Model
	//renderer->setModel(renderer->getShaderProgram(), sprite->getModel());
	//renderer->drawTr();

	//------
	//Sprite2
	//Sprite load texture
	//sprite2->loadTexture("res/assets/dragon.png", RGBA);

	//Model
	//renderer->setModel(renderer->getShaderProgram(), sprite2->getModel());
	//renderer->drawTr();

	//------
	//Collision detection
	//tileMap->detectCollisions(playerSprite);

	//if (sprite->getBounds().min.x < sprite2->getBounds().max.x
	//	&&
	//	sprite->getBounds().max.x > sprite2->getBounds().min.x
	//	&&
	//	sprite->getBounds().min.y < sprite2->getBounds().max.y
	//	&&
	//	sprite->getBounds().max.y > sprite2->getBounds().min.y)
	//	std::cout << "Colliding: YES" << std::endl;
	//else std::cout << "Colliding: NO" << std::endl;
}

int Game::terminate()
{
	if (sprite1) delete sprite1;
	if (sprite2) delete sprite2;
	if (cube1) delete cube1;
	if (cube2) delete cube2;

	return 0;
}