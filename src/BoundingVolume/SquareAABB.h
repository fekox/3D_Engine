#pragma once
#include "BoundingVolume/BoundingVolume.h"
#include <memory> 

using namespace std;

class SquareAABB : public BoundingVolume
{
	private:

	glm::vec3 center;
	float extent;

	public:

		SquareAABB();
		SquareAABB(const glm::vec3& inCenter, float inExtent);
		~SquareAABB();
		bool IsOnOrForwardPlane(const Plane& plane) const final;
		bool IsOnFrustum(const Frustum& camFrustum, const Transform& transform) const final;
};

