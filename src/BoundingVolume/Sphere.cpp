//#include "Sphere.h"
//
//Sphere::Sphere()
//{
//	center = { 0.f, 0.f, 0.f };
//	radius = { 0.f };
//}
//
//Sphere::Sphere(glm::vec3 inCenter, float inRadius) : BoundingVolume{}, center{ inCenter }, radius{ inRadius }
//{
//}
//
//Sphere::~Sphere()
//{
//}
//
//Sphere Sphere::GenerateSphereBV(Model model)
//{
//	glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
//	glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
//
//	for (auto&& mesh : model.meshes)
//	{
//		for (auto&& vertex : mesh.vertices)
//		{
//			minAABB.x = std::min(minAABB.x, vertex.Position.x);
//			minAABB.y = std::min(minAABB.y, vertex.Position.y);
//			minAABB.z = std::min(minAABB.z, vertex.Position.z);
//
//			maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
//			maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
//			maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
//		}
//	}
//
//	return Sphere((maxAABB + minAABB) * 0.5f, glm::length(minAABB - maxAABB));
//}
//
//bool Sphere::IsOnOrForwardPlane(const Plane plane)
//{
//	return plane.GetSignedDistanceToPlane(center) > -radius;
//}
//
//bool Sphere::IsOnFrustum(Frustum camFrustum,  Transform transform) 
//{
//	//Get global scale thanks to our transform
//	glm::vec3 globalScale = transform.GetGlobalScale();
//
//	//Get our global center with process it with the global model matrix of our transform
//	glm::vec3 globalCenter{ transform.GetModelMatrix() * glm::vec4(center, 1.f) };
//
//	//To wrap correctly our shape, we need the maximum scale scalar.
//	float maxScale = std::max(std::max(globalScale.x, globalScale.y), globalScale.z);
//
//	//Max scale is assuming for the diameter. So, we need the half to apply it to our radius
//	Sphere globalSphere(globalCenter, radius * (maxScale * 0.5f));
//
//	//Check Firstly the result that have the most chance to failure to avoid to call all functions.
//	return (globalSphere.IsOnOrForwardPlane(camFrustum.leftFace) &&
//		globalSphere.IsOnOrForwardPlane(camFrustum.rightFace) &&
//		globalSphere.IsOnOrForwardPlane(camFrustum.farFace) &&
//		globalSphere.IsOnOrForwardPlane(camFrustum.nearFace) &&
//		globalSphere.IsOnOrForwardPlane(camFrustum.topFace) &&
//		globalSphere.IsOnOrForwardPlane(camFrustum.bottomFace));
//}