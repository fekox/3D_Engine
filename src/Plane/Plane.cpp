#include "Plane.h"


Plane::Plane(const glm::vec3& p1, const glm::vec3& norm)
{
    normal = (glm::normalize(norm));
    distance = -(glm::dot(normal, p1));
}

float Plane::GetSignedDistanceToPlane(const glm::vec3& point) const
{
	return glm::dot(normal, point) - distance;
}

void Plane::SetNormalAndDistance(glm::vec3 point, glm::vec3 normal)
{
    this->normal = glm::normalize(normal);
    distance = glm::dot(this->normal, point);
}

bool Plane::GetSide(glm::vec3 point)
{
    return glm::dot(normal, point) + distance > 0.0F;
}