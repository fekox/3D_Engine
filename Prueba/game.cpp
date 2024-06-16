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
	//Rectangle
	rectanglePosition = Vector3{ 0.0f, 0.0f, -100.0f};
	colorRectangle = Vector4{ 0.5f, 0.5f, 0.5f, 1 };
	rectangleScale = Vector3{ 800.0f, 800.0f, 800.0f };
	rectangleRotation = Vector3{ 0,0,0 };
	rectangle = new Shape(Shape::Shapes2D::Square, colorRectangle, GetRenderer(), rectanglePosition, rectangleScale, rectangleRotation);

	//Cube - 1
	//*********************************************************************************
	cubePosition = Vector3{ -300, 0 , 0 };
	cubeScale = Vector3{ 80.0f, 80.0f, 80.0f };
	cubeRotation = Vector3{ 0,0,0 };
	material = new Material();
	material->SetMaterial(Material::MaterialType::GOLD);

	cube = new Shape3D(Shape3D::Shapes3D::Cube, material, GetRenderer(), cubePosition, cubeScale, cubeRotation);

	//Cube - 2
	//*********************************************************************************
	cubePosition2 = Vector3{ 150, 150 , 0 };
	cubeScale2 = Vector3{ 80.0f, 80.0f, 80.0f };
	cubeRotation2 = Vector3{ 0,0,0 };
	material2 = new Material();
	material2->SetMaterial(Material::MaterialType::SILVER);

	cube2 = new Shape3D(Shape3D::Shapes3D::Cube, material2, GetRenderer(), cubePosition2, cubeScale2, cubeRotation2);

	//Cube - 3
	//*********************************************************************************
	cubePosition3 = Vector3{ -150, -150 , 0};
	cubeScale3 = Vector3{ 80.0f, 80.0f, 80.0f };
	cubeRotation3 = Vector3{ 0,0,0 };
	material3 = new Material();
	material3->SetMaterial(Material::MaterialType::CYAN_PLASTIC);

	cube3 = new Shape3D(Shape3D::Shapes3D::Cube, material3, GetRenderer(), cubePosition3, cubeScale3, cubeRotation3);

	//Model1
	//*********************************************************************************
	modelPosition = Vector3{ -100, 0 , 0 };
	modelScale = Vector3{ 10, 10 , 10};
	modelRotation = Vector3{ 0, 0 , 0 };

	model = new Model(GetRenderer(), modelPosition, modelScale, modelRotation, "res/Models/backpack/backpack.obj", true);

	//Model2
	//*********************************************************************************

	modelPosition2 = Vector3{ 100, 0 , 0 };
	modelScale2 = Vector3{ 0.1, 0.1, 0.1};
	modelRotation2 = Vector3{ 90, 0 , 0 };

	model2 = new Model(GetRenderer(), modelPosition2, modelScale2, modelRotation2, "res/Models/sword/source/Darth Vader's Lightsaber.FBX", false);

	//Model3
	//*********************************************************************************
	 
	modelPosition3 = Vector3{ 0, 0 , 0};
	modelScale3 = Vector3{ 100, 100, 100 };
	modelRotation3 = Vector3{ 0, 0, 0};

	model3 = new Model(GetRenderer(), modelPosition3, modelScale3, modelRotation3, "res/Models/pingu/source/Cinematics_IntroCutscene_IntroCutscenePart1.fbx", false);

	//Init Shape
	//*********************************************************************************
	TextureColor = Vector4{ 1.0f, 1.0f, 1.0f, 1 };
	TexturePosition = Vector3{0,-100, 0 };
	TextureScale = Vector3{128,128,128};
	TextureRotation = Vector3{0,0,0};

	const char* path = "res/Sonic_Mania_Sprite_Sheet.png";
	Sonic = new Sprite(path, TextureColor, GetRenderer(), TexturePosition, TextureScale, TextureRotation);

	//Light
	//*********************************************************************************
	pointLight[0]->SetLightColor(glm::vec3(100.0f, 100.0f, 50.0f));
	pointLight[0]->SetConstant(1.0f);

	pointLight[1]->SetLightColor(glm::vec3(50.0f, 100.0f, 50.0f));
	pointLight[1]->SetConstant(1.0f);
	pointLight[1]->SetPosition(vec3(-300, 0, 0));

	pointLight[2]->SetLightColor(glm::vec3(100.0f, 50.0f, 50.0f));
	pointLight[2]->SetConstant(1.0f);
	pointLight[2]->SetPosition(vec3(150, 150, 0));

	pointLight[3]->SetLightColor(glm::vec3(50.0f, 50.0f, 50.0f));
	pointLight[3]->SetConstant(1.0f);
	pointLight[3]->SetPosition(vec3(-150, -150, 0));

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
		Sonic->setPosition(Vector3{ Sonic->getPosition().x, Sonic->getPosition().y - 2.0f,  Sonic->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->upArrow, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x, Sonic->getPosition().y + 2.0f, Sonic->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->leftArrow, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x - 2.0f, Sonic->getPosition().y, Sonic->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->rightArrow, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x + 2.0f, Sonic->getPosition().y, Sonic->getPosition().z});
	}
	//*********************************************************************************

	pointLight[0]->SetPosition(newPos);

	Sonic->Update();

	model->Draw();
	model2->Draw();
	model3->Draw();

	//Sonic->Draw();

	rectangle->Draw();

	cube->Draw();
	cube2->Draw();
	cube3->Draw();
}

void Game::exit()
{
	delete Sonic;
	delete rectangle;
	delete cube;
	delete cube2;
	delete cube3;

	delete idleAnimation;
	delete walkAnimation;
	delete model;
	delete model2;
	delete model3;
}