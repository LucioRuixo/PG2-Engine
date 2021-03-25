#include "Game.h"

Game::Game() {}

Game::~Game() {}

//Sprite* sprite;
//Sprite* sprite2;
Sprite* playerSprite;
TileMap* tileMap;

int Game::initialize()
{
	//------
	//Tile Map
	Sprite* grassSprite = new Sprite(renderer);
	grassSprite->setBufferData();
	grassSprite->setTexture("res/assets/pasto.png", RGB);

	int tileMapWidth = 20;
	int tileMapHeight = 10;
	float tileWidth = 0.1f;
	float tileHeight = 0.2f;
	float initialX = -(1.0f - tileWidth / 2.0f);
	float initialY = -(1.0f - tileHeight / 2.0f);
	tileMap = new TileMap(tileMapWidth, tileMapHeight, tileWidth, tileHeight, initialX, initialY, grassSprite, renderer);

	Sprite* obsidianSprite = new Sprite(renderer);
	obsidianSprite->setBufferData();
	obsidianSprite->setTexture("res/assets/bloque obsidiana.jpg", RGB);

	tileMap->getTile(7, 7)->setSprite(obsidianSprite);
	tileMap->getTile(7, 6)->setSprite(obsidianSprite);
	tileMap->getTile(8, 7)->setSprite(obsidianSprite);
	tileMap->getTile(8, 6)->setSprite(obsidianSprite);
	tileMap->getTile(11, 7)->setSprite(obsidianSprite);
	tileMap->getTile(11, 6)->setSprite(obsidianSprite);
	tileMap->getTile(12, 7)->setSprite(obsidianSprite);
	tileMap->getTile(12, 6)->setSprite(obsidianSprite);
	tileMap->getTile(9, 5)->setSprite(obsidianSprite);
	tileMap->getTile(10, 5)->setSprite(obsidianSprite);
	tileMap->getTile(8, 2)->setSprite(obsidianSprite);
	tileMap->getTile(8, 4)->setSprite(obsidianSprite);
	tileMap->getTile(9, 4)->setSprite(obsidianSprite);
	tileMap->getTile(10, 4)->setSprite(obsidianSprite);
	tileMap->getTile(11, 4)->setSprite(obsidianSprite);
	tileMap->getTile(8, 3)->setSprite(obsidianSprite);
	tileMap->getTile(9, 3)->setSprite(obsidianSprite);
	tileMap->getTile(10, 3)->setSprite(obsidianSprite);
	tileMap->getTile(11, 3)->setSprite(obsidianSprite);
	tileMap->getTile(11, 2)->setSprite(obsidianSprite);

	tileMap->getTile(7, 7)->setWalkability(false);
	tileMap->getTile(7, 6)->setWalkability(false);
	tileMap->getTile(8, 7)->setWalkability(false);
	tileMap->getTile(8, 6)->setWalkability(false);
	tileMap->getTile(11, 7)->setWalkability(false);
	tileMap->getTile(11, 6)->setWalkability(false);
	tileMap->getTile(12, 7)->setWalkability(false);
	tileMap->getTile(12, 6)->setWalkability(false);
	tileMap->getTile(9, 5)->setWalkability(false);
	tileMap->getTile(10, 5)->setWalkability(false);
	tileMap->getTile(8, 2)->setWalkability(false);
	tileMap->getTile(8, 4)->setWalkability(false);
	tileMap->getTile(9, 4)->setWalkability(false);
	tileMap->getTile(10, 4)->setWalkability(false);
	tileMap->getTile(11, 4)->setWalkability(false);
	tileMap->getTile(8, 3)->setWalkability(false);
	tileMap->getTile(9, 3)->setWalkability(false);
	tileMap->getTile(10, 3)->setWalkability(false);
	tileMap->getTile(11, 3)->setWalkability(false);
	tileMap->getTile(11, 2)->setWalkability(false);
	//------

	//Player
	//------
	playerSprite = new Sprite(renderer);
	playerSprite->setBufferData();

	playerSprite->setTexture("res/assets/gato.jpg", RGB);
	playerSprite->SetPosition(-0.7f, -0.7f, 0.0f);
	playerSprite->SetScale(0.15f, 0.25f, 0.0f);
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
	//input
	if (input->getKeyPress(FunctionKey::ESCAPE)) window->setWindowShouldClose(true);

	//transform
	if (input->getKeyPress(PrintableKey::W))
	{
		transY += 0.025f;
		playerSprite->translateBounds(0.0f, 0.025f);
		playerSprite->movingUp = true;
	}
	else playerSprite->movingUp = false;

	if (input->getKeyPress(PrintableKey::S))
	{
		transY -= 0.025f;
		playerSprite->translateBounds(0.0f, -0.025f);
		playerSprite->movingDown = true;
	}
	else playerSprite->movingDown = false;

	if (input->getKeyPress(PrintableKey::D))
	{
		transX += 0.025f;
		playerSprite->translateBounds(0.025f, 0.0f);
		playerSprite->movingRight = true;
	}
	else playerSprite->movingRight = false;

	if (input->getKeyPress(PrintableKey::A))
	{
		transX -= 0.025f;
		playerSprite->translateBounds(-0.025f, 0.0f);
		playerSprite->movingLeft = true;
	}
	else playerSprite->movingLeft = false;

	if (input->getKeyPress(PrintableKey::X)) transZ += 0.001f;
	if (input->getKeyPress(PrintableKey::Z)) transZ -= 0.001f;

	////rotate
	//if (input->getKeyPress(PrintableKey::U)) rotateX += 0.01f;
	//if (input->getKeyPress(PrintableKey::J)) rotateX -= 0.01f;
	//if (input->getKeyPress(PrintableKey::I)) rotateY += 0.01f;
	//if (input->getKeyPress(PrintableKey::K)) rotateY -= 0.01f;
	//if (input->getKeyPress(PrintableKey::O)) rotateZ += 0.01f;
	//if (input->getKeyPress(PrintableKey::L)) rotateZ -= 0.01f;
	//
	////scale
	//if (input->getKeyPress(FunctionKey::UP))
	//{
	//	scaleX += 0.001f;
	//	scaleY += 0.001f;
	//	scaleZ += 0.001f;
	//}
	//if (input->getKeyPress(FunctionKey::DOWN))
	//{
	//	scaleX -= 0.001f;
	//	scaleY -= 0.001f;
	//	scaleZ -= 0.001f;
	//}

	//clear screen
	renderer->clearBackground();

	//view
	renderer->setView(renderer->getShaderProgram(), renderer->getView());

	//proj
	renderer->setProj(renderer->getShaderProgram(), renderer->getProj());

	//------
	//Tile Map
	tileMap->draw(renderer);

	//------
	//Player
	playerSprite->Translate(transX, transY, transZ);

	playerSprite->loadTexture();
	renderer->setModel(renderer->getShaderProgram(), playerSprite->getModel());
	renderer->drawTriangles();

	transX = 0.0f;
	transY = 0.0f;
	transZ = 0.0f;

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
	tileMap->detectCollisions(playerSprite);

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
	if (tileMap) delete tileMap;
	if (playerSprite) delete playerSprite;

	//if (sprite) delete sprite;
	//if (sprite2) delete sprite2;

	return 0;
}