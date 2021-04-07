#include "Game.h"

float cameraMovementSpeed = 0.025f;
float spriteScaleFactor = 0.1f;
float spriteRotationFactor = 0.1f;

vec3 cameraMovement = vec3(0.0f, 0.0f, 0.0f);

//TileMap* tileMap;
Sprite* sprite1;
Sprite* sprite2;
Cube* cube;

Game::Game() {}

Game::~Game() {}

int Game::initialize()
{
	//------
	//Tile Map
	//Sprite* grassSprite = new Sprite(renderer);
	//grassSprite->setBufferData();
	//grassSprite->setTexture("res/assets/pasto.png", RGB);
	//
	//int tileMapWidth = 20;
	//int tileMapHeight = 10;
	//float tileWidth = 0.1f;
	//float tileHeight = 0.2f;
	//float initialX = -(1.0f - tileWidth / 2.0f);
	//float initialY = -(1.0f - tileHeight / 2.0f);
	//tileMap = new TileMap(tileMapWidth, tileMapHeight, tileWidth, tileHeight, initialX, initialY, grassSprite, renderer);
	//
	//Sprite* obsidianSprite = new Sprite(renderer);
	//obsidianSprite->setBufferData();
	//obsidianSprite->setTexture("res/assets/bloque obsidiana.jpg", RGB);
	//
	//tileMap->getTile(7, 7)->setSprite(obsidianSprite);
	//tileMap->getTile(7, 6)->setSprite(obsidianSprite);
	//tileMap->getTile(8, 7)->setSprite(obsidianSprite);
	//tileMap->getTile(8, 6)->setSprite(obsidianSprite);
	//tileMap->getTile(11, 7)->setSprite(obsidianSprite);
	//tileMap->getTile(11, 6)->setSprite(obsidianSprite);
	//tileMap->getTile(12, 7)->setSprite(obsidianSprite);
	//tileMap->getTile(12, 6)->setSprite(obsidianSprite);
	//tileMap->getTile(9, 5)->setSprite(obsidianSprite);
	//tileMap->getTile(10, 5)->setSprite(obsidianSprite);
	//tileMap->getTile(8, 2)->setSprite(obsidianSprite);
	//tileMap->getTile(8, 4)->setSprite(obsidianSprite);
	//tileMap->getTile(9, 4)->setSprite(obsidianSprite);
	//tileMap->getTile(10, 4)->setSprite(obsidianSprite);
	//tileMap->getTile(11, 4)->setSprite(obsidianSprite);
	//tileMap->getTile(8, 3)->setSprite(obsidianSprite);
	//tileMap->getTile(9, 3)->setSprite(obsidianSprite);
	//tileMap->getTile(10, 3)->setSprite(obsidianSprite);
	//tileMap->getTile(11, 3)->setSprite(obsidianSprite);
	//tileMap->getTile(11, 2)->setSprite(obsidianSprite);
	//
	//tileMap->getTile(7, 7)->setWalkability(false);
	//tileMap->getTile(7, 6)->setWalkability(false);
	//tileMap->getTile(8, 7)->setWalkability(false);
	//tileMap->getTile(8, 6)->setWalkability(false);
	//tileMap->getTile(11, 7)->setWalkability(false);
	//tileMap->getTile(11, 6)->setWalkability(false);
	//tileMap->getTile(12, 7)->setWalkability(false);
	//tileMap->getTile(12, 6)->setWalkability(false);
	//tileMap->getTile(9, 5)->setWalkability(false);
	//tileMap->getTile(10, 5)->setWalkability(false);
	//tileMap->getTile(8, 2)->setWalkability(false);
	//tileMap->getTile(8, 4)->setWalkability(false);
	//tileMap->getTile(9, 4)->setWalkability(false);
	//tileMap->getTile(10, 4)->setWalkability(false);
	//tileMap->getTile(11, 4)->setWalkability(false);
	//tileMap->getTile(8, 3)->setWalkability(false);
	//tileMap->getTile(9, 3)->setWalkability(false);
	//tileMap->getTile(10, 3)->setWalkability(false);
	//tileMap->getTile(11, 3)->setWalkability(false);
	//tileMap->getTile(11, 2)->setWalkability(false);
	//------

	//Sprite 1
	sprite1 = new Sprite(renderer);
	sprite1->setTexture("res/assets/gato 1.jpg", RGB);
	sprite1->setPosition(1.0f, 0.0f, -6.0f);
	sprite1->setRotationY(-45.0f);

	//Sprite 2
	sprite2 = new Sprite(renderer);
	sprite2->setTexture("res/assets/gato 2.jpg", RGB);
	sprite2->setPosition(-1.0f, 0.0f, -3.0f);
	sprite2->setRotationY(45.0f);

	//Cube
	cube = new Cube(renderer);
	cube->setPosition(0.0f, 3.0f, -4.5f);
	
	//Sprite animation
	//Animation* animation = new Animation();
	//animation->AddFrame(0.0f, 0.0f, 640.0f, 360.0f, 1280.0f, 720.0f, 4.0f, 4, 2);
	//animation->AddAnimation();
	//animation->SetCurrentAnimation(0);
	//sprite->setAnimation(animation);

	//Lighting
	lighting->enableDirectionalLight(vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 3.0f, -4.5f));

	return 0;
}

void Game::update()
{
	//input
	if (input->getKeyPress(FunctionKey::ESCAPE)) window->setWindowShouldClose(true);

	//transform
	if (input->getKeyPress(PrintableKey::D)) cameraMovement.x += cameraMovementSpeed;
	if (input->getKeyPress(PrintableKey::A)) cameraMovement.x -= cameraMovementSpeed;

	if (input->getKeyPress(PrintableKey::W)) cameraMovement.y += cameraMovementSpeed;
	if (input->getKeyPress(PrintableKey::S)) cameraMovement.y -= cameraMovementSpeed;

	if (input->getKeyPress(PrintableKey::X)) cameraMovement.z += cameraMovementSpeed;
	if (input->getKeyPress(PrintableKey::Z)) cameraMovement.z -= cameraMovementSpeed;

	//rotate
	if (input->getKeyPress(PrintableKey::U)) sprite1->setRotationX(sprite1->transform.rotation.x + spriteRotationFactor);
	if (input->getKeyPress(PrintableKey::J)) sprite1->setRotationX(sprite1->transform.rotation.x - spriteRotationFactor);
	if (input->getKeyPress(PrintableKey::I)) sprite1->setRotationY(sprite1->transform.rotation.y + spriteRotationFactor);
	if (input->getKeyPress(PrintableKey::K)) sprite1->setRotationY(sprite1->transform.rotation.y - spriteRotationFactor);
	if (input->getKeyPress(PrintableKey::O)) sprite1->setRotationZ(sprite1->transform.rotation.z + spriteRotationFactor);
	if (input->getKeyPress(PrintableKey::L)) sprite1->setRotationZ(sprite1->transform.rotation.z - spriteRotationFactor);
	
	//scale
	if (input->getKeyPress(FunctionKey::UP))
		sprite1->setScale(sprite1->transform.scale.x + spriteScaleFactor, sprite1->transform.scale.y + spriteScaleFactor, sprite1->transform.scale.z + spriteScaleFactor);
	if (input->getKeyPress(FunctionKey::DOWN))
		sprite1->setScale(sprite1->transform.scale.x - spriteScaleFactor, sprite1->transform.scale.y - spriteScaleFactor, sprite1->transform.scale.z - spriteScaleFactor);

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

	//se rompe cuando hace setModel()
	//cube->draw();

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

	camera->translate(cameraMovement.x, cameraMovement.y, cameraMovement.z);
}

int Game::terminate()
{
	//if (tileMap) delete tileMap;
	if (sprite1) delete sprite1;
	if (sprite2) delete sprite2;
	if (cube) delete cube;

	return 0;
}