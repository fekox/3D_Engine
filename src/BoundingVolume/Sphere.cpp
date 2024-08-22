#include "Sphere.h"

Sphere::Sphere()
{
	center = { 0.f, 0.f, 0.f };
	radius = { 0.f };
}

Sphere::Sphere(const glm::vec3& inCenter, float inRadius) : BoundingVolume{}, center{ inCenter }, radius{ inRadius }
{
}

Sphere::~Sphere()
{
}

bool Sphere::IsOnOrForwardPlane(const Plane& plane) const
{
	return plane.GetSignedDistanceToPlane(center) > -radius;
}

bool Sphere::IsOnFrustum(const Frustum& camFrustum, const Transform& transform) const
{
	//Get global scale thanks to our transform
	const glm::vec3 globalScale = transform.GetGlobalScale();

	//Get our global center with process it with the global model matrix of our transform
	const glm::vec3 globalCenter{ transform.GetModelMatrix() * glm::vec4(center, 1.f) };

	//To wrap correctly our shape, we need the maximum scale scalar.
	const float maxScale = std::max(std::max(globalScale.x, globalScale.y), globalScale.z);

	//Max scale is assuming for the diameter. So, we need the half to apply it to our radius
	Sphere globalSphere(globalCenter, radius * (maxScale * 0.5f));

	//Check Firstly the result that have the most chance to failure to avoid to call all functions.
	return (globalSphere.IsOnOrForwardPlane(camFrustum.leftFace) &&
		globalSphere.IsOnOrForwardPlane(camFrustum.rightFace) &&
		globalSphere.IsOnOrForwardPlane(camFrustum.farFace) &&
		globalSphere.IsOnOrForwardPlane(camFrustum.nearFace) &&
		globalSphere.IsOnOrForwardPlane(camFrustum.topFace) &&
		globalSphere.IsOnOrForwardPlane(camFrustum.bottomFace));
}