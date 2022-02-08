#include "Game.h"

bool onePressed = false;
bool twoPressed = false;
bool threePressed = false;
bool fourPressed = false;
bool fivePressed = false;

float cameraMovementSpeed = 2.0f;
float cameraRotationSpeed = 50.0f;
float spriteScaleAddition = 0.1f;

float cubeTranslationSpeed = 1.0f;
float cubeRotationSpeed = 50.0f;
float cubeScaleSpeed = 10.0f;

float planeTranslationSpeed = 10.0f;
float planeRotationSpeed = 50.0f;

vec3 lightSourcePosition = vec3(0.0f, 2.0f, -4.5f);
vec3 cameraMovement;
vec3 cameraRotation;

Cube* rubyCube;
Cube* emeraldCube;
Cube* goldCube;

//Model* bsp;
//Cube* v0;
//Cube* v1;
//Cube* v2;
//Cube* v3;
//Cube* v4;
//Cube* v5;
//Cube* v6;
//Cube* v7;

Game::Game() {}

Game::~Game() {}

int Game::initialize()
{
#pragma region Material Cubes
	Material ruby;
	ruby.diffuse = vec3(0.61424f, 0.04136f, 0.04136f);
	ruby.specular = vec3(0.727811f, 0.626959f, 0.626959f);
	ruby.shininess = 0.6f;
	rubyCube = new Cube(vec3(0.607f, 0.066f, 0.117f), ruby);
	rubyCube->getTransform()->setPosition(-1.0f, 1.0f, -15.0f);
	rubyCube->getTransform()->setScale(1.0f, 3.0f, 1.0f);
	
	Material emerald;
	emerald.diffuse = vec3(0.07568f, 0.61424f, 0.07568f);
	emerald.specular = vec3(0.633f, 0.727811f, 0.633f);
	emerald.shininess = 0.6f;
	emeraldCube = new Cube(vec3(0.031f, 0.396f, 0.133f), emerald);
	emeraldCube->getTransform()->setPosition(0.0f, 1.0f, -15.0f);
	emeraldCube->getTransform()->setScale(1.0f, 3.0f, 1.0f);
	
	Material gold;
	gold.diffuse = vec3(0.75164f, 0.60648f, 0.22648f);
	gold.specular = vec3(0.628281f, 0.555802f, 0.366065f);
	gold.shininess = 0.4f;
	goldCube = new Cube(vec3(0.905f, 0.741f, 0.258f), gold);
	goldCube->getTransform()->setPosition(1.0f, 1.0f, -15.0f);
	goldCube->getTransform()->setScale(1.0f, 3.0f, 1.0f);
#pragma endregion

#pragma region Models
	//bsp = modelManager->importModel("res/Assets/Modelos/Blender/Escena.dae");
	//bsp->getRootNode()->getTransform()->translate(0.0f, 0.0f, -4.0f);
	//
	//v0 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//v1 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//v2 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//v3 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//v4 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//v5 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//v6 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//v7 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//
	//v0->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//v1->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//v2->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//v3->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//v4->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//v5->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//v6->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//v7->getTransform()->setScale(0.2f, 0.2f, 0.2f);
#pragma endregion

#pragma region Light
	lightingManager->addDirectionalLight(vec3(1.0f, -1.0f, 0.0f));

	lightingManager->addPointLight(0, vec3(0.0f, 0.0f, -12.0f));
	lightingManager->addPointLight(1, vec3(0.0f, 0.0f, -8.0f));
	lightingManager->addPointLight(2, vec3(0.0f, 1.0f, -4.5f));
	lightingManager->addPointLight(3, vec3(0.0f, 0.0f, 1.0f));
#pragma endregion
	
#pragma region Camera
	FrustumData frustumData;
	frustumData.near = 1.0f;
	frustumData.far = 3.0f;

	camera->enableFrustumCulling(frustumData);

	camera->getTransform()->setPosition(0.0f, 0.0f, 0.0f);
	camera->getTransform()->setRotation(0.0f, 180.0f, 0.0f);
#pragma endregion

	return 1;
}

void Game::update()
{
#pragma region Input
	if (input->getKeyPress(FunctionKey::ESCAPE)) window->setWindowShouldClose(true);
	
#pragma region Camera
	//Move camera
	//-----------
	if (input->getKeyPress(PrintableKey::D)) camera->getTransform()->translate(cameraMovementSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	if (input->getKeyPress(PrintableKey::A)) camera->getTransform()->translate(-cameraMovementSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	
	if (input->getKeyPress(PrintableKey::Z)) camera->getTransform()->translate(0.0f, cameraMovementSpeed * time->getDeltaTime(), 0.0f);
	if (input->getKeyPress(PrintableKey::X)) camera->getTransform()->translate(0.0f, -cameraMovementSpeed * time->getDeltaTime(), 0.0f);
	
	if (input->getKeyPress(PrintableKey::S)) camera->getTransform()->translate(0.0f, 0.0f, cameraMovementSpeed * time->getDeltaTime());
	if (input->getKeyPress(PrintableKey::W)) camera->getTransform()->translate(0.0f, 0.0f, -cameraMovementSpeed * time->getDeltaTime());
	//-----------

	//Rotate camera
	//-----------
	if (input->getKeyPress(FunctionKey::UP)) camera->getTransform()->rotate(cameraRotationSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	if (input->getKeyPress(FunctionKey::DOWN)) camera->getTransform()->rotate(-cameraRotationSpeed * time->getDeltaTime(), 0.0f, 0.0f);

	if (input->getKeyPress(FunctionKey::RIGHT)) camera->getTransform()->rotate(0.0f, cameraRotationSpeed * time->getDeltaTime(), 0.0f);
	if (input->getKeyPress(FunctionKey::LEFT)) camera->getTransform()->rotate(0.0f, -cameraRotationSpeed * time->getDeltaTime(), 0.0f);
	//-----------

	//Transform frustum
	//-----------
	//if (input->getKeyPress(PrintableKey::U)) camera->getFrustum()->getTransform()->translate(0.0f, 0.0f, cameraMovementSpeed * time->getDeltaTime());
	//if (input->getKeyPress(PrintableKey::J)) camera->getFrustum()->getTransform()->translate(0.0f, 0.0f, -cameraMovementSpeed * time->getDeltaTime());
	//
	//if (input->getKeyPress(PrintableKey::I)) camera->getFrustum()->getTransform()->rotate(0.0f, cameraRotationSpeed * time->getDeltaTime(), 0.0f);
	//if (input->getKeyPress(PrintableKey::K)) camera->getFrustum()->getTransform()->rotate(0.0f, -cameraRotationSpeed * time->getDeltaTime(), 0.0f);
	//
	//if (input->getKeyPress(PrintableKey::O)) camera->getFrustum()->getTransform()->rotate(cameraRotationSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	//if (input->getKeyPress(PrintableKey::L)) camera->getFrustum()->getTransform()->rotate(-cameraRotationSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	//-----------

	//Move testing cube
	//-----------
	if (input->getKeyPress(PrintableKey::U)) camera->getFrustum()->getTransform()->translate(0.0f, 0.0f, cameraMovementSpeed * time->getDeltaTime());
	if (input->getKeyPress(PrintableKey::J)) camera->getFrustum()->getTransform()->translate(0.0f, 0.0f, -cameraMovementSpeed * time->getDeltaTime());

	if (input->getKeyPress(PrintableKey::I)) camera->getFrustum()->getTransform()->translate(0.0f, cameraMovementSpeed * time->getDeltaTime(), 0.0f);
	if (input->getKeyPress(PrintableKey::K)) camera->getFrustum()->getTransform()->translate(0.0f, -cameraMovementSpeed * time->getDeltaTime(), 0.0f);

	if (input->getKeyPress(PrintableKey::O)) camera->getFrustum()->getTransform()->translate(cameraMovementSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	if (input->getKeyPress(PrintableKey::L)) camera->getFrustum()->getTransform()->translate(-cameraMovementSpeed * time->getDeltaTime(), 0.0f, 0.0f);

	//string isInside = camera->getFrustum()->isInside(cube->getTransform()->getGlobalPosition()) ? "true" : "false";
	//cout << "cube is inside frustum: " << isInside << endl;

	//cout << "entities: " << Entity::getEntities().size() << endl;
	//-----------
#pragma endregion

#pragma region Light
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

#pragma region Models
	//ModelNode* bspScene = dynamic_cast<ModelNode*>(bsp->getRootNode());
	//ModelNode* bspRoot = dynamic_cast<ModelNode*>(bsp->getRootNode()->getChildren()[0]);
	//ModelNode* bspChild = dynamic_cast<ModelNode*>(bsp->getRootNode()->getChildren()[0]);
	//vector<vec3> v = bspChild->getCollisionBoxVertices();
	//
	//v0->getTransform()->setPosition(v[0].x, v[0].y, v[0].z);
	//v1->getTransform()->setPosition(v[1].x, v[1].y, v[1].z);
	//v2->getTransform()->setPosition(v[2].x, v[2].y, v[2].z);
	//v3->getTransform()->setPosition(v[3].x, v[3].y, v[3].z);
	//v4->getTransform()->setPosition(v[4].x, v[4].y, v[4].z);
	//v5->getTransform()->setPosition(v[5].x, v[5].y, v[5].z);
	//v6->getTransform()->setPosition(v[6].x, v[6].y, v[6].z);
	//v7->getTransform()->setPosition(v[7].x, v[7].y, v[7].z);
	//
	//if (input->getKeyPress(PrintableKey::J)) bspRoot->getTransform()->translate(cubeTranslationSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	//if (input->getKeyPress(PrintableKey::L)) bspRoot->getTransform()->translate(-cubeTranslationSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	//
	//if (input->getKeyPress(PrintableKey::M)) bspRoot->getTransform()->rotate(0.0f, cubeRotationSpeed * time->getDeltaTime(), 0.0f);
	//if (input->getKeyPress(PrintableKey::N)) bspRoot->getTransform()->rotate(0.0f, -cubeRotationSpeed * time->getDeltaTime(), 0.0f);
	//
	//if (input->getKeyPress(PrintableKey::K)) bspRoot->getTransform()->translate(0.0f, 0.0f, cubeTranslationSpeed * time->getDeltaTime());
	//if (input->getKeyPress(PrintableKey::I)) bspRoot->getTransform()->translate(0.0f, 0.0f, -cubeTranslationSpeed * time->getDeltaTime());
#pragma endregion
#pragma endregion

#pragma region Rendering
	//rubyCube->draw();
	//emeraldCube->draw();
	//goldCube->draw();

	//bsp->drawAsBSPScene(camera->getTransform()->getPosition(), true);
	//v0->draw();
	//v1->draw();
	//v2->draw();
	//v3->draw();
	//v4->draw();
	//v5->draw();
	//v6->draw();
	//v7->draw();

	//camera->drawFrustum();
#pragma endregion
}

int Game::terminate()
{
	if (rubyCube) delete rubyCube;
	if (emeraldCube) delete emeraldCube;
	if (goldCube) delete goldCube;

	//if (bsp) delete bsp;
	//if (v0) delete v0;
	//if (v1) delete v0;
	//if (v2) delete v0;
	//if (v3) delete v0;
	//if (v4) delete v0;
	//if (v5) delete v0;
	//if (v6) delete v0;
	//if (v7) delete v0;

	return 0;
}