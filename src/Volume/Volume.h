#pragma once

#include "CoreEngine/Renderer.h"
#include "Plane/Plane.h"

#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"

using namespace std;
using namespace renderer;

class Volume
{
	Volume();
	~Volume();

	virtual void Init(Renderer* rendere) = 0;
	virtual void Draw(glm::mat4 model) = 0;
	void DeInit();

	virtual bool IsOnFrustum() = 0;
	virtual bool IsOnPlane(Plane plane) = 0;
	virtual vector<Vertex> GetVertexs() = 0;
	virtual void SetGlobalVolume(Volume* volume, glm::mat4 model) = 0;
	//Line* lines;
};

