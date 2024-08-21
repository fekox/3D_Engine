#pragma once

#include "CoreEngine/Renderer.h"

#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"

#include "Plane/Plane.h"
#include "OcclusionCulling/OcclusionCulling.h"

using namespace renderer;

class VolumeAABB
{
	public:
	VolumeAABB();
	VolumeAABB(glm::vec3 min, glm::vec3 max);
	VolumeAABB(glm::vec3 center, float extX, float extY, float extZ);
	~VolumeAABB();

	bool IsOnFrustum();
	bool IsOnPlane(Plane plane);
	vector<Vertex> GetVertexs();
	void SetGlobalVolume(glm::mat4 model);
	void SetVolume(glm::vec3 center, float extX, float extY, float extZ);

	glm::vec3 center;
	glm::vec3 extents;

};

