#pragma once
#include "BoundingVolume/BoundingVolume.h"
#include <memory> 

struct SquareAABB : public BoundingVolume
{
	glm::vec3 center{ 0.f, 0.f, 0.f };
	float extent{ 0.f };

	SquareAABB(const glm::vec3 inCenter, float inExtent);

	~SquareAABB() override;

	bool IsOnOrForwardPlane(const Plane& plane) const final;
	bool IsOnFrustum(const Frustum camFrustum, const Transform* transform)const override;
};

