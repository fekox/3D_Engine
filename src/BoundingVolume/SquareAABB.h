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
		SquareAABB(glm::vec3 inCenter, float inExtent);
		~SquareAABB();

		bool IsOnOrForwardPlane(Plane plane) override;
		bool IsOnFrustum(Frustum camFrustum, Transform transform) override;
};

