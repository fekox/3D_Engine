#include "game.h"

Game::Game(float width, float height, const char* windowName) : BaseGame(width, height, windowName)
{
	this->width = width;
	this->height = height;

	init();
}

Game::~Game()
{
	exit();
}

void Game::init()
{
	//Triangle 1
	colorTriangleFront = Vector4{ 1.0f, 1.0f, 0.0f, 1 };
	colorTriangleBack = Vector4{ 1.0f, 1.0f, 0.0f, 1 };
	position = Vector3{ 100, 0 , 0 };
	scale = Vector3{ 80.0f, 80.0f, 80.0f };
	rotation = Vector3{ 0,0,0 };
	triangle = new Shape(Shape::Shapes2D::Triangle, colorTriangleFront, GetRenderer(), position, scale, rotation);

	//Cube
	//*********************************************************************************
	colorCube = Vector4{ 1.0f, 1.0f, 1.0f, 1 };
	cubePosition = Vector3{ -150, 0 , 0 };
	cubeScale = Vector3{ 80.0f, 80.0f, 80.0f };
	cubeRotation = Vector3{ 0,0,0 };

	cube = new Shape3D(Shape3D::Shapes3D::Cube, colorCube, GetRenderer(), cubePosition, cubeScale, cubeRotation);

	//Init Shape
	//*********************************************************************************
	TextureColor = Vector4{ 1.0f, 1.0f, 1.0f, 1 };
	TexturePosition = Vector3{0,0, 0 };
	TextureScale = Vector3{128,128,128};
	TextureRotation = Vector3{0,0,0};

	const char* path = "res/Sonic_Mania_Sprite_Sheet.png";
	Sonic = new Sprite(path, TextureColor, GetRenderer(), TexturePosition, TextureScale, TextureRotation);

	//Idle Animation
	//*********************************************************************************
	walkAnimation = new Animation();
	walkAnimation->AddFrame(848, 203, 122/3, 48, 830, 465, 500, 3);

	idleAnimation = new Animation();
	idleAnimation->AddFrame(390, 98, 98 / 3, 43, 830, 465, 2500, 3);

	Sonic->SetAnimation(idleAnimation);
}

void Game::update()
{
	camera->SetCameraMode(Camera::CameraMode::FistPerson);
	glm::vec3 newPos = glm::vec3(Sonic->getPosition().x, Sonic->getPosition().y, Sonic->getPosition().z);
	camera->ChangeCameraTarget(glm::vec3(newPos.x, newPos.y, newPos.z), glm::vec3(Sonic->getRotation().x, Sonic->getRotation().y, Sonic->getRotation().z));

	Sonic->SetAnimation(idleAnimation);

	//Player Inputs;
	//*********************************************************************************
	if (inputSystem->getKey(inputSystem->N1, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setRotationY(-1.0f);
	}

	if (inputSystem->getKey(inputSystem->N2, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setRotationY(1.0f);
	}

	if (inputSystem->getKey(inputSystem->downArrow, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x, Sonic->getPosition().y - 1.0f,  Sonic->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->upArrow, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x, Sonic->getPosition().y + 1.0f, Sonic->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->leftArrow, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x - 1.0f, Sonic->getPosition().y, Sonic->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->rightArrow, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x + 1.0f, Sonic->getPosition().y, Sonic->getPosition().z});
	}
	//*********************************************************************************

	Sonic->Update();

	Sonic->Draw();

	triangle->Draw();

	cube->Draw();
}

void Game::exit()
{
	delete Sonic;
	delete triangle;
	delete cube;

	delete idleAnimation;
	delete walkAnimation;
}