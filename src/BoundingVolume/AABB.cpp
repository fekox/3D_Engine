#include "AABB.h"

AABB::~AABB()
{

}

std::vector<glm::vec3> AABB::GetVertice()
{
	std::vector<glm::vec3> vertice(8);

	vertice[0] = center + glm::vec3(-extents.x, -extents.y, -extents.z);
	vertice[1] = center + glm::vec3(extents.x, -extents.y, -extents.z);
	vertice[2] = center + glm::vec3(extents.x, extents.y, -extents.z);
	vertice[3] = center + glm::vec3(-extents.x, extents.y, -extents.z);
	vertice[4] = center + glm::vec3(-extents.x, -extents.y, extents.z);
	vertice[5] = center + glm::vec3(extents.x, -extents.y, extents.z);
	vertice[6] = center + glm::vec3(extents.x, extents.y, extents.z);
	vertice[7] = center + glm::vec3(-extents.x, extents.y, extents.z);

	return vertice;
}

bool AABB::IsOnOrForwardPlane(const Plane& plane) const
{
	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	const float r = extents.x * std::abs(plane.normal.x) + extents.y * std::abs(plane.normal.y) +
		extents.z * std::abs(plane.normal.z);

	return -r <= plane.GetSignedDistanceToPlane(center);
}

bool AABB::IsOnFrustum(const Frustum camFrustum, const Transform* transform) const
{
	//Get global scale thanks to our transform
	glm::vec3 globalCenter{ transform->m_modelMatrix * glm::vec4(center, 1.f) };

	// Scaled orientation
	 glm::vec3 right = transform->GetRightConst() * extents.x;
	 glm::vec3 up = transform->GetUpConst() * extents.y;
	 glm::vec3 forward = transform->GetForwardConst() * extents.z;

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