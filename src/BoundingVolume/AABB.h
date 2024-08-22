#pragma once

#include "BoundingVolume/BoundingVolume.h"
#include <array> //std::array

class AABB : public BoundingVolume
{
	private:

		glm::vec3 center;
		glm::vec3 extents;

	public:

		AABB();
		AABB(const glm::vec3& min, const glm::vec3& max);
		AABB(const glm::vec3& inCenter, float iI, float iJ, float iK);

		std::array<glm::vec3, 8> GetVertice() const;

		bool IsOnOrForwardPlane(const Plane& plane) const final;
		bool IsOnFrustum(const Frustum& camFrustum, const Transform& transform) const final;
};

