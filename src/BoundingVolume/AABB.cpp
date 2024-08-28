#include "AABB.h"

AABB::AABB()
{
	center = { 0.f, 0.f, 0.f };
	extents = { 0.f, 0.f, 0.f };
}

AABB::AABB(glm::vec3& min, glm::vec3& max) : BoundingVolume{}, center{ (max + min) * 0.5f }, extents{ max.x - center.x, max.y - center.y, max.z - center.z }
{
}

AABB::AABB(glm::vec3& inCenter, float iI, float iJ, float iK) : BoundingVolume{}, center{ inCenter }, extents{ iI, iJ, iK }
{
}

std::array<glm::vec3, 8> AABB::GetVertice()
{
	std::array<glm::vec3, 8> vertice;

	vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
	vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
	vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
	vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
	vertice[4] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
	vertice[5] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
	vertice[6] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
	vertice[7] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };

	return vertice;
}

bool AABB::IsOnOrForwardPlane(Plane plane)
{
	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	const float r = extents.x * std::abs(plane.normal.x) + extents.y * std::abs(plane.normal.y) +
		extents.z * std::abs(plane.normal.z);

	return -r <= plane.GetSignedDistanceToPlane(center);
}

bool AABB::IsOnFrustum(Frustum camFrustum, Transform transform)
{
	//Get global scale thanks to our transform
	glm::vec3 globalCenter{ transform.GetModelMatrix() * glm::vec4(center, 1.f) };

	// Scaled orientation
	 glm::vec3 right = transform.GetRight() * extents.x;
	 glm::vec3 up = transform.GetUp() * extents.y;
	 glm::vec3 forward = transform.GetForward() * extents.z;

	 float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

	 float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

	 float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

	 AABB globalAABB(globalCenter, newIi, newIj, newIk);

	return (globalAABB.IsOnOrForwardPlane(camFrustum.leftFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.rightFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.topFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.bottomFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.nearFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.farFace));
}