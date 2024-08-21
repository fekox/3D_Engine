#pragma once

#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"

class Plane
{
private:
	glm::vec3 normal;
	float distance;

public:
	Plane();
	Plane(glm::vec3 normal, glm::vec3 point);
	Plane(glm::vec3 normal, float distance);
	Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	~Plane();

	void SetNormal(glm::vec3 normal);
	void SetDistance(float distance);

	glm::vec3 GetNormal();
	float GetDistance();

	void SetPositionAndNormal(glm::vec3 point, glm::vec3 normal);
	void Set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c);

	void Flip();
	void Translate(glm::vec3 translation);

	glm::vec3 ClosestPointOnPlane(glm::vec3 point);
	float GetDistanceToPoint(glm::vec3 point);

	bool GetSide(glm::vec3 point);
	bool SameSide(glm::vec3 point1, glm::vec3 point2);

};