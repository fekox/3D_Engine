#pragma once
#include "CoreEngine/BaseGame.h"
#include "..\libs\glm\include\glm.hpp"

using namespace baseEngine;

class Game : public BaseGame
{
private:
	const char* windowName;
	
	//Shape3D - 1
	Shape3D* cube;

	Vector3 cubePosition;
	Vector3 cubeScale;
	Vector3 cubeRotation;

	//Material - 1

	Material* material;

	int diffuseINT;
	int specularINT;
	float shininess;

	//Shape3D - 2
	Shape3D* cube2;

	vec3 ambient = glm::vec3(1.0f, 0.5f, 0.31f);
	vec3 diffuseV3 = glm::vec3(1.0f, 0.5f, 0.31f);
	vec3 specularV3 = glm::vec3(0.5f, 0.5f, 0.5f);

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

	//Sprite 
	Sprite* Container;
	Sprite* Container_specular;

	Vector3 lastTexturePos;

	Vector4 TextureColor;
	Vector3 TexturePosition;
	Vector3 TextureScale;
	Vector3 TextureRotation;

	//Sprite 2

public:
	float width;
	float height;

	Game(float width, float height, const char* windowName);
	~Game();
	void init() override;
	void update() override;
	void exit() override;
};