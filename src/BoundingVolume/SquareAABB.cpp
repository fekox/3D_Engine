#include "SquareAABB.h"

SquareAABB::SquareAABB(glm::vec3 inCenter, float inExtent) : BoundingVolume{}, center{ inCenter }, extent{ inExtent }
{

}

SquareAABB::~SquareAABB()
{

}

bool SquareAABB::IsOnOrForwardPlane(const Plane& plane) const
{
	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	float r = extent * (std::abs(plane.normal.x) + std::abs(plane.normal.y) + std::abs(plane.normal.z));
	return -r <= plane.GetSignedDistanceToPlane(center);
}

bool SquareAABB::IsOnFrustum(const Frustum camFrustum, const Transform* transform) const
{
	//Get global scale thanks to our transform
	glm::vec3 globalCenter{ transform->m_modelMatrix * glm::vec4(center, 1.f) };

	// Scaled orientation
	glm::vec3 right = transform->GetRightConst() * extent;
	glm::vec3 up = transform->GetUpConst() * extent;
	glm::vec3 forward = transform->GetForwardConst() * extent;

	float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

	float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

	float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

	SquareAABB globalAABB(globalCenter, std::max(std::max(newIi, newIj), newIk));

	return (globalAABB.IsOnOrForwardPlane(camFrustum.leftFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.rightFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.topFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.bottomFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.nearFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.farFace));
}