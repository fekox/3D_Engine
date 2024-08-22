#pragma once
#include "BoundingVolume/BoundingVolume.h"
#include <memory> //std::unique_ptr

using namespace std;

class Sphere : public BoundingVolume
{
	private:

		glm::vec3 center;
		float radius;

	public:

		Sphere();
		Sphere(const glm::vec3& inCenter, float inRadius);
		~Sphere();

		bool IsOnOrForwardPlane(const Plane& plane) const final;
		bool IsOnFrustum(const Frustum& camFrustum, const Transform& transform) const final;
};

