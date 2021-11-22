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

//Cube* p1;
//Cube* p2;
//Cube* p3;
//Cube* vMin;
//Cube* vMax;
Cube* v0;
Cube* v1;
Cube* v2;
Cube* v3;
Cube* v4;
Cube* v5;
Cube* v6;
Cube* v7;

Model* bsp;

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
	bsp = modelManager->importModel("res/Assets/Modelos/Blender/Escena.dae");

	//p1 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//p2 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//p3 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	//vMin = new Cube(vec3(0.0f, 1.0f, 0.0f));
	//vMax = new Cube(vec3(0.0f, 1.0f, 0.0f));
	v0 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	v1 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	v2 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	v3 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	v4 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	v5 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	v6 = new Cube(vec3(1.0f, 0.0f, 0.0f));
	v7 = new Cube(vec3(1.0f, 0.0f, 0.0f));

	//p1->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//p2->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//p3->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//vMin->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	//vMax->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	v0->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	v1->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	v2->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	v3->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	v4->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	v5->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	v6->getTransform()->setScale(0.2f, 0.2f, 0.2f);
	v7->getTransform()->setScale(0.2f, 0.2f, 0.2f);
#pragma endregion

#pragma region Light
	lightingManager->addDirectionalLight(vec3(1.0f, -1.0f, 0.0f));

	lightingManager->addPointLight(0, vec3(0.0f, 0.0f, -12.0f));
	lightingManager->addPointLight(1, vec3(0.0f, 0.0f, -8.0f));
	lightingManager->addPointLight(2, vec3(0.0f, 1.0f, -4.5f));
	lightingManager->addPointLight(3, vec3(0.0f, 0.0f, 1.0f));
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
	ModelNode* bspScene = dynamic_cast<ModelNode*>(bsp->getRootNode());
	ModelNode* bspChild = dynamic_cast<ModelNode*>(bsp->getRootNode()->getChildren()[0]);
	//vec3 pp1 = dynamic_cast<ModelNode*>(bsp->getRootNode()->getChildren()[1]->getChildren()[0])->getTransform()->getBSPPlane()->getTransform()->getGlobalPosition();
	//vec3 f = dynamic_cast<ModelNode*>(bsp->getRootNode()->getChildren()[1]->getChildren()[0])->getTransform()->getBSPPlane()->getTransform()->getForward();
	//vec3 pp2 = dynamic_cast<ModelNode*>(bsp->getRootNode()->getChildren()[1]->getChildren()[1])->getTransform()->getBSPPlane()->getTransform()->getGlobalPosition();
	//vec3 pp3 = dynamic_cast<ModelNode*>(bsp->getRootNode()->getChildren()[1]->getChildren()[2])->getTransform()->getBSPPlane()->getTransform()->getGlobalPosition();

	CollisionBox cb = bspChild->getCollisionBox();
	vector<vec3> v = bspChild->getCollisionBoxVertices();

	//cout << endl;
	//p1->getTransform()->setPosition(pp1.x + f.x, pp1.y + f.y, pp1.z + f.z);
	//p2->getTransform()->setPosition(pp2.x, pp2.y, pp2.z);
	//p3->getTransform()->setPosition(pp3.x, pp3.y, pp3.z);
	//vMin->getTransform()->setPosition(cb.minEdge.x, cb.minEdge.y, cb.minEdge.z);
	//vMax->getTransform()->setPosition(cb.maxEdge.x, cb.maxEdge.y, cb.maxEdge.z);
	v0->getTransform()->setPosition(v[0].x, v[0].y, v[0].z);
	v1->getTransform()->setPosition(v[1].x, v[1].y, v[1].z);
	v2->getTransform()->setPosition(v[2].x, v[2].y, v[2].z);
	v3->getTransform()->setPosition(v[3].x, v[3].y, v[3].z);
	v4->getTransform()->setPosition(v[4].x, v[4].y, v[4].z);
	v5->getTransform()->setPosition(v[5].x, v[5].y, v[5].z);
	v6->getTransform()->setPosition(v[6].x, v[6].y, v[6].z);
	v7->getTransform()->setPosition(v[7].x, v[7].y, v[7].z);

	if (input->getKeyPress(PrintableKey::J)) bspChild->getTransform()->translate(cubeTranslationSpeed * time->getDeltaTime(), 0.0f, 0.0f);
	if (input->getKeyPress(PrintableKey::L)) bspChild->getTransform()->translate(-cubeTranslationSpeed * time->getDeltaTime(), 0.0f, 0.0f);

	if (input->getKeyPress(PrintableKey::M)) bspChild->getTransform()->rotate(0.0f, cubeRotationSpeed * time->getDeltaTime(), 0.0f);
	if (input->getKeyPress(PrintableKey::N)) bspChild->getTransform()->rotate(0.0f, -cubeRotationSpeed * time->getDeltaTime(), 0.0f);

	if (input->getKeyPress(PrintableKey::K)) bspChild->getTransform()->translate(0.0f, 0.0f, cubeTranslationSpeed * time->getDeltaTime());
	if (input->getKeyPress(PrintableKey::I)) bspChild->getTransform()->translate(0.0f, 0.0f, -cubeTranslationSpeed * time->getDeltaTime());
#pragma endregion
#pragma endregion

#pragma region Rendering
	rubyCube->draw();
	emeraldCube->draw();
	goldCube->draw();

	//bsp->draw();
	bsp->drawAsBSPScene(camera->getTransform()->getPosition(), true);

	//p1->draw();
	//p2->draw();
	//p3->draw();
	//vMin->draw();
	//vMax->draw();
	v0->draw();
	v1->draw();
	v2->draw();
	v3->draw();
	v4->draw();
	v5->draw();
	v6->draw();
	v7->draw();
#pragma endregion
}

int Game::terminate()
{
	if (rubyCube) delete rubyCube;
	if (emeraldCube) delete emeraldCube;
	if (goldCube) delete goldCube;

	if (bsp) delete bsp;

	//if (p1) delete p1;
	//if (p2) delete p2;
	//if (p3) delete p3;
	//if (vMin) delete v0;
	//if (vMax) delete v0;
	if (v0) delete v0;
	if (v1) delete v0;
	if (v2) delete v0;
	if (v3) delete v0;
	if (v4) delete v0;
	if (v5) delete v0;
	if (v6) delete v0;
	if (v7) delete v0;

	return 0;
}