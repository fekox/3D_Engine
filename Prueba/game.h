#pragma once
#include "CoreEngine/BaseGame.h"
#include "..\libs\glm\include\glm.hpp"
#include "..\src\3DImporter\Model.h"

using namespace baseEngine;

class Game : public BaseGame
{
private:
	const char* windowName;
	
	//Model
	Model* model;

	Vector3 modelPosition;
	Vector3 modelScale;
	Vector3 modelRotation;

	//Shape3D - 1
	Shape3D* cube;
	Material* material;

	Vector3 cubePosition;
	Vector3 cubeScale;
	Vector3 cubeRotation;

	//Shape3D - 2
	Shape3D* cube2;
	Material* material2;


	Vector3 cubePosition2;
	Vector3 cubeScale2;
	Vector3 cubeRotation2;

	//Shape3D - 3
	Shape3D* cube3;
	Material* material3;

	Vector3 cubePosition3;
	Vector3 cubeScale3;
	Vector3 cubeRotation3;

	//Shape2D
	Shape* triangle;

	Vector4 colorTriangleFront;
	Vector4 colorTriangleBack;

	Vector3 position;
	Vector3 position2;
	Vector3 position3;

	Vector3 scale;
	Vector3 rotation;

	//Shape2D
	Shape* rectangle;

	Vector4 colorRectangle;
	Vector4 colorRectangleeBack;

	Vector3 rectanglePosition;

	Vector3 rectangleScale;
	Vector3 rectangleRotation;

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