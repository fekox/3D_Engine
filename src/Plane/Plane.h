#pragma once

#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"

class Plane
{
public:
	glm::vec3 normal;
	float distance;

	Plane();
	Plane(const glm::vec3& p1, const glm::vec3& norm);
	~Plane();

	float GetSignedDistanceToPlane(const glm::vec3& point) const;
};