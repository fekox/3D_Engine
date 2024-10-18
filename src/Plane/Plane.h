#pragma once

#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"

struct Plane
{
    glm::vec3 normal = { 0.f, 1.f, 0.f };

    float distance = 0.f;

	Plane() = default;
	Plane(const glm::vec3& p1, const glm::vec3& norm);

	float GetSignedDistanceToPlane(const glm::vec3& point) const;

    void SetNormalAndDistance(glm::vec3 point, glm::vec3 normal);

    bool GetSide(glm::vec3 point);
};