#include "Plane.h"

Plane::Plane()
{
	normal = glm::vec3();
	distance = 0.f;
}

Plane::Plane(const glm::vec3& p1, const glm::vec3& norm) : normal(glm::normalize(norm)),
distance(glm::dot(normal, p1))
{
}

Plane::~Plane()
{
}

float Plane::GetSignedDistanceToPlane(const glm::vec3& point) const
{
	return glm::dot(normal, point) - distance;
}