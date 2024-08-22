#pragma once
#include "3DImporter/Model.h"
#include "BoundingVolume/BoundingVolume.h"
#include <memory> 

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

		Sphere GenerateSphereBV(const Model& model);

		bool IsOnOrForwardPlane(const Plane& plane) const final;
		bool IsOnFrustum(const Frustum& camFrustum, const Transform& transform) const final;
};

