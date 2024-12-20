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
	Renderer* renderer;

	Camera* newCamera;
	Window* currentWindow;

	glm::vec3 modelPosition;
	glm::vec3 modelScale;
	glm::vec3 modelRotation;

	//Model2
	Model* model2;

	glm::vec3 modelPosition2;
	glm::vec3 modelScale2;
	glm::vec3 modelRotation2;

	//Model3
	Model* model3;

	glm::vec3 modelPosition3;
	glm::vec3 modelScale3;
	glm::vec3 modelRotation3;

	//Shape3D - 1
	Shape3D* cube;
	Material* material;

	glm::vec3 cubePosition;
	glm::vec3 cubeScale;
	glm::vec3 cubeRotation;

	//Shape3D - 2
	Shape3D* cube2;
	Material* material2;

	glm::vec3 cubePosition2;
	glm::vec3 cubeScale2;
	glm::vec3 cubeRotation2;

	//Shape3D - 3
	Shape3D* cube3;
	Material* material3;

	glm::vec3 cubePosition3;
	glm::vec3 cubeScale3;
	glm::vec3 cubeRotation3;

	//Shape3D - 4
	Shape3D* background;
	Material* material4;

	glm::vec3 backgroundPosition;
	glm::vec3 backgroundScale;
	glm::vec3 backgroundRotation;

	//Plane - 1
	glm::vec3 planeScale;

	Model* plane1;
	glm::vec3 Plane1Pos;
	glm::vec3 Plane1PosEsc;
	glm::vec3 Plane1Rot;

	Sprite* plane2;
	glm::vec3 Plane2Pos;
	glm::vec3 Plane2PosEsc;
	glm::vec3 Plane2Rot;

	Sprite* plane3;
	glm::vec3 Plane3Pos;
	glm::vec3 Plane3PosEsc;
	glm::vec3 Plane3Rot;

	Sprite* plane4;
	glm::vec3 Plane4Pos;
	glm::vec3 Plane4PosEsc;
	glm::vec3 Plane4Rot;

	Sprite* plane5;
	glm::vec3 Plane5Pos;
	glm::vec3 Plane5PosEsc;
	glm::vec3 Plane5Rot;


	//Sprite
	Sprite* Sonic;

	glm::vec3 lastTexturePos;

	Vector4 TextureColor;
	glm::vec3 TexturePosition;
	glm::vec3 TextureScale;
	glm::vec3 TextureRotation;

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