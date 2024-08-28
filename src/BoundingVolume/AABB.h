#pragma once

#include "BoundingVolume/BoundingVolume.h"
#include <array> 

class AABB : public BoundingVolume
{
	public:

		glm::vec3 center;
		glm::vec3 extents;

		AABB();
		AABB( glm::vec3& min,  glm::vec3& max);
		AABB( glm::vec3& inCenter, float iI, float iJ, float iK);

		std::array<glm::vec3, 8> GetVertice() ;

		bool IsOnOrForwardPlane(Plane plane) override;
		bool IsOnFrustum(Frustum camFrustum, Transform transform) override;
};

