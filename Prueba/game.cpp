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
	//Init Shape
	TextureColor = Vector4{ 1.0f, 1.0f, 1.0f, 1 };
	TexturePosition = Vector3{0,0, -700 };
	TextureScale = Vector3{ 128,128,128};
	TextureRotation = Vector3{ 0,0,0 };

	const char* path = "res/Sonic_Mania_Sprite_Sheet.png";
	Sonic = new Sprite(path, TextureColor, GetRenderer(), TexturePosition, TextureScale, TextureRotation);

	//Idle Animation
	walkAnimation = new Animation();
	walkAnimation->AddFrame(848, 203, 122/3, 48, 830, 465, 500, 3);

	idleAnimation = new Animation();
	idleAnimation->AddFrame(390, 98, 98 / 3, 43, 830, 465, 2500, 3);

	Sonic->SetAnimation(idleAnimation);
}

void Game::update()
{
	Sonic->SetAnimation(idleAnimation);

	//Inputs
	if (inputSystem->getKey(inputSystem->q, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x, Sonic->getPosition().y, Sonic->getPosition().z - 1.0f });

	}

	if (inputSystem->getKey(inputSystem->e, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x, Sonic->getPosition().y, Sonic->getPosition().z + 1.0f});
	}

	if (inputSystem->getKey(inputSystem->s, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x, Sonic->getPosition().y - 1.0f,  Sonic->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->w, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x, Sonic->getPosition().y + 1.0f, Sonic->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->a, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x - 1.0f, Sonic->getPosition().y, Sonic->getPosition().z});
	}

	if (inputSystem->getKey(inputSystem->d, inputSystem->Pressed))
	{
		Sonic->SetAnimation(walkAnimation);
		Sonic->setPosition(Vector3{ Sonic->getPosition().x + 1.0f, Sonic->getPosition().y, Sonic->getPosition().z});
	}

	Sonic->Update();

	Sonic->Draw();
}

void Game::exit()
{
	delete Sonic;

	delete idleAnimation;
	delete walkAnimation;
}