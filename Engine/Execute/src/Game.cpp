#include "Game.h"

Game::Game() {}

Game::~Game() {}

//Sprite* sprite;
//Sprite* sprite2;
Sprite* sprite1;
Sprite* sprite2;
//TileMap* tileMap;

float scaleFactor = 0.1f;
float rotationFactor = 0.1f;

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
	//------
	sprite1 = new Sprite(renderer);
	sprite1->setBufferData();

	sprite1->setTexture("res/assets/gato.jpg", RGB);
	sprite1->SetPosition(0.0f, 0.0f, -3.0f);
	sprite1->SetScale(1.0f, 1.0f, 0.0f);
	//------

	//Sprite 2
	//------
	sprite2 = new Sprite(renderer);
	sprite2->setBufferData();

	sprite2->setTexture("res/assets/Cato in despair.jpg", RGB);
	sprite2->SetPosition(0.0f, 0.0f, -10.0f);
	sprite2->SetScale(1.0f, 1.0f, 0.0f);
	//------

	//sprite = new Sprite(renderer);
	//sprite2 = new Sprite(renderer);
	//
	//sprite->setBufferData();
	//sprite2->setBufferData();
	//
	////------
	////Set Sprite animation
	//Animation* animation = new Animation();
	//animation->AddFrame(0.0f, 0.0f, 640.0f, 360.0f, 1280.0f, 720.0f, 4.0f, 4, 2);
	//animation->AddAnimation();
	//animation->SetCurrentAnimation(0);
	//sprite->setAnimation(animation);

	return 0;
}

void Game::update()
{
	//clear screen
	renderer->clearBackground();

	//input
	if (input->getKeyPress(FunctionKey::ESCAPE)) window->setWindowShouldClose(true);

	//transform
	if (input->getKeyPress(PrintableKey::W)) transY += 0.025f;

	if (input->getKeyPress(PrintableKey::S)) transY -= 0.025f;

	if (input->getKeyPress(PrintableKey::D)) transX += 0.025f;

	if (input->getKeyPress(PrintableKey::A)) transX -= 0.025f;

	if (input->getKeyPress(PrintableKey::X)) transZ += 0.01f;
	if (input->getKeyPress(PrintableKey::Z)) transZ -= 0.01f;

	//rotate
	if (input->getKeyPress(PrintableKey::U)) sprite1->SetRotationX(sprite1->transform.rotation.x + rotationFactor);
	if (input->getKeyPress(PrintableKey::J)) sprite1->SetRotationX(sprite1->transform.rotation.x - rotationFactor);
	if (input->getKeyPress(PrintableKey::I)) sprite1->SetRotationY(sprite1->transform.rotation.y + rotationFactor);
	if (input->getKeyPress(PrintableKey::K)) sprite1->SetRotationY(sprite1->transform.rotation.y - rotationFactor);
	if (input->getKeyPress(PrintableKey::O)) sprite1->SetRotationZ(sprite1->transform.rotation.z + rotationFactor);
	if (input->getKeyPress(PrintableKey::L)) sprite1->SetRotationZ(sprite1->transform.rotation.z - rotationFactor);
	
	//scale
	if (input->getKeyPress(FunctionKey::UP))
		sprite1->SetScale(sprite1->transform.scale.x + scaleFactor, sprite1->transform.scale.y + scaleFactor, sprite1->transform.scale.z + scaleFactor);
	if (input->getKeyPress(FunctionKey::DOWN))
		sprite1->SetScale(sprite1->transform.scale.x - scaleFactor, sprite1->transform.scale.y - scaleFactor, sprite1->transform.scale.z - scaleFactor);

	//------
	//Tile Map
	//tileMap->draw(renderer);

	//------
	//Player
	//playerSprite->Translate(transX, transY, transZ);

	sprite2->loadTexture();
	renderer->setModel(renderer->getShaderProgram(), sprite2->getModel());
	renderer->drawTriangles();

	sprite1->loadTexture();
	renderer->setModel(renderer->getShaderProgram(), sprite1->getModel());
	renderer->drawTriangles();

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

	//view
	glm::mat4 translatedView = glm::translate(renderer->getView(), glm::vec3(-transX, -transY, -transZ));
	renderer->setView(renderer->getShaderProgram(), translatedView);

	//proj
	renderer->setProj(renderer->getShaderProgram(), renderer->getProj());
}

int Game::terminate()
{
	//if (tileMap) delete tileMap;
	if (sprite1) delete sprite1;
	if (sprite2) delete sprite2;

	//if (sprite) delete sprite;
	//if (sprite2) delete sprite2;

	return 0;
}