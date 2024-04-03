#pragma once
#include "CoreEngine/BaseGame.h"

using namespace baseEngine;

class Game : public BaseGame
{
private:
	const char* windowName;
	//Shape
	Shape* triangle;

	Vector4 colorTriangleFront;
	Vector4 colorTriangleBack;

	Vector3 position;
	Vector3 position2;
	Vector3 position3;

	Vector3 scale;
	Vector3 rotation;

	//Sprite
	Sprite* Sonic;

	Vector3 lastTexturePos;

	Vector4 TextureColor;
	Vector3 TexturePosition;
	Vector3 TextureScale;
	Vector3 TextureRotation;

	Animation* idleAnimation;
	Animation* walkAnimation;

public:
	float width;
	float height;

	Game(float width, float height, const char* windowName);
	~Game();
	void init() override;
	void update() override;
	void exit() override;
};