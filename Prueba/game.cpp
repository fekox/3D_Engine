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
	//Cube - 1
	//*********************************************************************************
	cubePosition = Vector3{ -150, 0 , 0 };
	cubeScale = Vector3{ 80.0f, 80.0f, 80.0f };
	cubeRotation = Vector3{ 0,0,0 };

	//Material
	diffuseINT = 0;
	specularINT = 1;
	shininess = 64.0f;
	material = new Material(diffuseINT, specularINT, shininess);

	cube = new Shape3D(Shape3D::Shapes3D::Cube, material, GetRenderer(), cubePosition, cubeScale, cubeRotation);

	//Cube - 2
	//*********************************************************************************
	cubePosition2 = Vector3{ 150, 150 , 0 };
	cubeScale2 = Vector3{ 80.0f, 80.0f, 80.0f };
	cubeRotation2 = Vector3{ 0,0,0 };

	material2 = new Material(ambient, diffuseV3, specularV3, shininess);

	cube2 = new Shape3D(Shape3D::Shapes3D::Cube, material2, GetRenderer(), cubePosition2, cubeScale2, cubeRotation2);

	//Cube - 3
	//*********************************************************************************
	cubePosition3 = Vector3{ -150, -150 , 0};
	cubeScale3 = Vector3{ 80.0f, 80.0f, 80.0f };
	cubeRotation3 = Vector3{ 0,0,0 };
	material3 = new Material(diffuseINT, specularINT, shininess);

	cube3 = new Shape3D(Shape3D::Shapes3D::Cube, material3, GetRenderer(), cubePosition3, cubeScale3, cubeRotation3);

	//Init Sprite
	//*********************************************************************************
	TextureColor = Vector4{ 1.0f, 1.0f, 1.0f, 1 };
	TexturePosition = Vector3{0,0,0};
	TextureScale = Vector3{128,128,128};
	TextureRotation = Vector3{0,0,0};

	const char* path = "res/container.png";
	Container = new Sprite(path, TextureColor, GetRenderer(), TexturePosition, TextureScale, TextureRotation);

	//const char* path2 = "res/container_specular.png";
	//Container_specular = new Sprite(path2, TextureColor, GetRenderer(), TexturePosition, TextureScale, TextureRotation);

	//Light
	//*********************************************************************************
	light->SetLightPos(0.0f, 10.0f, 10.0f);
	light->SetLightColor(1.0f, 1.0f, 1.0f);
}

void Game::update()
{
	camera->SetCameraMode(Camera::CameraMode::FistPerson);
	glm::vec3 newPos = glm::vec3(0,0,0);
	//camera->ChangeCameraTarget(glm::vec3(newPos.x, newPos.y, newPos.z), glm::vec3(Sonic->getRotation().x, Sonic->getRotation().y, Sonic->getRotation().z));

	cube->Draw();
	cube2->Draw();
	cube3->Draw();
}

void Game::exit()
{
	delete Container;
	delete cube;
	delete cube2;
	delete cube3;
}