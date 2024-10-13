#pragma once

#include "BoundingVolume/BoundingVolume.h"
#include <array> 

struct AABB : public BoundingVolume
{
	glm::vec3 center{ 0.f, 0.f, 0.f };
	glm::vec3 extents{ 0.f, 0.f, 0.f };

	AABB(const glm::vec3& min, const glm::vec3& max) : BoundingVolume{}, center{ (max + min) * 0.5f },
		extents{ max.x - center.x, max.y - center.y, max.z - center.z }
	{
	}

	AABB(const glm::vec3& inCenter, float iI, float iJ, float iK) : BoundingVolume{}, center{ inCenter },
		extents{ iI, iJ, iK }
	{

	}

	~AABB();

	std::array<glm::vec3, 8> GetVertice();

	bool IsOnOrForwardPlane(const Plane& plane) const final;

	bool IsOnFrustum(const Frustum camFrustum, const Transform* transform) const override;
};

