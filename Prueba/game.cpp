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
	cubePosition = glm::vec3{ -300, 0 , 0 };
	cubeScale = glm::vec3{ 80.0f, 80.0f, 80.0f };
	cubeRotation = glm::vec3{ 0,0,0 };
	material = new Material();
	material->SetMaterial(Material::MaterialType::GOLD);

	cube = new Shape3D(Shape3D::Shapes3D::Cube, material, GetRenderer(), cubePosition, cubeScale, cubeRotation);

	//Cube - 2
	//*********************************************************************************
	cubePosition2 = glm::vec3{ 150, 150 , 0};
	cubeScale2 = glm::vec3{ 80.0f, 80.0f, 80.0f };
	cubeRotation2 = glm::vec3{ 0,0,0 };
	material2 = new Material();
	material2->SetMaterial(Material::MaterialType::BRONZE);

	cube2 = new Shape3D(Shape3D::Shapes3D::Cube, material2, GetRenderer(), cubePosition2, cubeScale2, cubeRotation2);

	//Cube - 3
	//*********************************************************************************
	cubePosition3 = glm::vec3{ -150, -150 , 0};
	cubeScale3 = glm::vec3{ 80.0f, 80.0f, 80.0f };
	cubeRotation3 = glm::vec3{ 0,0,0 };
	material3 = new Material();
	material3->SetMaterial(Material::MaterialType::CYAN_PLASTIC);

	cube3 = new Shape3D(Shape3D::Shapes3D::Cube, material3, GetRenderer(), cubePosition3, cubeScale3, cubeRotation3);

	//Background
	//*********************************************************************************
	backgroundPosition = glm::vec3{ 0, 0 , -100.0f };
	backgroundScale = glm::vec3{ 1000.0f, 1000.0f, 40.0f };
	backgroundRotation = glm::vec3{ 0,0,0 };

	material4 = new Material();
	material4->SetMaterial(Material::MaterialType::SILVER);

	background = new Shape3D(Shape3D::Shapes3D::Cube, material4, GetRenderer(), backgroundPosition, backgroundScale, backgroundRotation);

	//Model1
	//*********************************************************************************
	modelPosition = glm::vec3{ -100, 0 , 0 };
	modelScale = glm::vec3{ 10, 10 , 10};
	modelRotation = glm::vec3{ 0, 0 , 0 };

	model = new Model(GetRenderer(), modelPosition, modelScale, modelRotation, "res/Models/backpack/backpack.obj", true);

	//Model2
	//*********************************************************************************

	modelPosition2 = glm::vec3{ 25, 0 , 0 };
	modelScale2 = glm::vec3{ 0.1, 0.1, 0.1};
	modelRotation2 = glm::vec3{ 90, 0 , 0 };

	model2 = new Model(GetRenderer(), modelPosition2, modelScale2, modelRotation2, "res/Models/sword/source/Darth Vader's Lightsaber.FBX", false, model->transform);

	//Model3
	//*********************************************************************************
	 
	modelPosition3 = glm::vec3{ -25, 0 , 0};
	modelScale3 = glm::vec3{ 100, 100, 100 };
	modelRotation3 = glm::vec3{ 0, 0, 0};

	model3 = new Model(GetRenderer(), modelPosition3, modelScale3, modelRotation3, "res/Models/pingu/source/Cinematics_IntroCutscene_IntroCutscenePart1.fbx", false);

	//Init Shape
	//*********************************************************************************
	TextureColor = Vector4{ 1.0f, 1.0f, 1.0f, 1 };
	TexturePosition = glm::vec3{0,-100, 0 };
	TextureScale = glm::vec3{128,128,128};
	TextureRotation = glm::vec3{0,0,0};

	const char* path = "res/Sonic_Mania_Sprite_Sheet.png";
	Sonic = new Sprite(path, TextureColor, GetRenderer(), TexturePosition, TextureScale, TextureRotation);

	//Directional Light
	//*********************************************************************************
	directionaLight[0].SetLightColor(glm::vec3(100.0f, 100.0f, 50.0f));

	//Point Light
	//*********************************************************************************
	pointLight[0]->SetLightColor(glm::vec3(100.0f, 100.0f, 50.0f));
	pointLight[0]->SetConstant(1.0f);

	pointLight[1]->SetLightColor(glm::vec3(50.0f, 100.0f, 50.0f));
	pointLight[1]->SetConstant(1.0f);
	pointLight[1]->SetPosition(vec3(100, -200, -50));

	pointLight[2]->SetLightColor(glm::vec3(100.0f, 50.0f, 50.0f));
	pointLight[2]->SetConstant(1.0f);
	pointLight[2]->SetPosition(vec3(250, -200, -50));

	pointLight[3]->SetLightColor(glm::vec3(50.0f, 50.0f, 50.0f));
	pointLight[3]->SetConstant(1.0f);
	pointLight[3]->SetPosition(vec3(400, -200, -50));

	//Spot Light
	//*********************************************************************************
	spotLight[1]->SetPosition(vec3(-300, 0, 0));
	spotLight[1]->SetDirection(vec3(0,0, -1.0f));
	spotLight[1]->SetLightColor(vec3(100.0f, 100.0f, 0.0f));

	spotLight[2]->SetPosition(vec3(150, 150, 0));
	spotLight[2]->SetDirection(vec3(0, 0, -1.0f));
	spotLight[2]->SetLightColor(vec3(100.0f, 0.0f, 50.0f));

	spotLight[3]->SetPosition(vec3(-150, -150, 0));
	spotLight[3]->SetDirection(vec3(0, 0, -1.0f));
	spotLight[3]->SetLightColor(vec3(0.0f, 100.0f, 50.0f));

	//Idle Animation
	//*********************************************************************************
	walkAnimation = new Animation();
	walkAnimation->AddFrame(848, 203, 122/3, 48, 830, 465, 500, 3);

	idleAnimation = new Animation();
	idleAnimation->AddFrame(390, 98, 98 / 3, 43, 830, 465, 2500, 3);

	Sonic->SetAnimation(idleAnimation);	

	renderer = new Renderer(currentWindow, newCamera);
}

void Game::update()
{
	camera->SetCameraMode(Camera::CameraMode::FistPerson);
	glm::vec3 newPos = glm::vec3(Sonic->getPosition().x, Sonic->getPosition().y, Sonic->getPosition().z);
	camera->ChangeCameraTarget(glm::vec3(newPos.x, newPos.y, newPos.z), glm::vec3(Sonic->getRotation().x, Sonic->getRotation().y, Sonic->getRotation().z));

	//Sonic->SetAnimation(idleAnimation);

	//Player Inputs;
	//*********************************************************************************
	if (inputSystem->getKey(inputSystem->N1, inputSystem->Pressed))
	{
		//Sonic->SetAnimation(walkAnimation);
		model->setRotation(glm::vec3(model->getRotation().x -1, 0, 0));
	}

	if (inputSystem->getKey(inputSystem->N2, inputSystem->Pressed))
	{
		//Sonic->SetAnimation(walkAnimation);
		model->setRotation(glm::vec3(model->getRotation().x + 1, 0, 0));
	}

	if (inputSystem->getKey(inputSystem->downArrow, inputSystem->Pressed))
	{
		//Sonic->SetAnimation(walkAnimation);
		model->setPosition(glm::vec3{ model->getPosition().x, model->getPosition().y - 2.0f,  model->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->upArrow, inputSystem->Pressed))
	{
		//Sonic->SetAnimation(walkAnimation);
		model->setPosition(glm::vec3{ model->getPosition().x, model->getPosition().y + 2.0f, model->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->leftArrow, inputSystem->Pressed))
	{
		//Sonic->SetAnimation(walkAnimation);
		model->setPosition(glm::vec3{ model->getPosition().x - 2.0f, model->getPosition().y, model->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->rightArrow, inputSystem->Pressed))
	{
		////Sonic->SetAnimation(walkAnimation);
		model->setPosition(glm::vec3{ model->getPosition().x + 2.0f, model->getPosition().y, model->getPosition().z});
	}

	//Lights
	//*********************************************************************************
	//pointLight[0]->SetPosition(newPos);

	spotLight[0]->SetPosition(camera->cameraPos);
	spotLight[0]->SetDirection(camera->cameraFront);

	Sonic->Update();

	//Drawn and Update
	//*********************************************************************************

	//model2->Draw();

	model3->Draw();

	//Sonic->Draw();

	background->Draw();

	cube->Draw();

	cube2->Draw();

	cube3->Draw();

	if (model->IsOnFrustum(camera->CreateFrustumFromCamera(camera, width / height, glm::radians(camera->zoom), camera->nearPlane, camera->farPlane - 500)))
	{
		model->Draw();
		cout << "Se dibuja" << endl;
	}

	else
	{
		cout << "No se dibuja" << endl;
	}
}

void Game::exit()
{
	delete Sonic;
	delete background;
	delete cube;
	delete cube2;
	delete cube3;

	delete idleAnimation;
	delete walkAnimation;
	delete model;
	delete model2;
	delete model3;
}