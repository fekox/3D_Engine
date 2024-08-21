#include "OcclusionCulling.h"

Camera* OcclusionCulling::camera = nullptr;

Plane OcclusionCulling::up = Plane();
Plane OcclusionCulling::down = Plane();
Plane OcclusionCulling::left = Plane();
Plane OcclusionCulling::right = Plane();
Plane OcclusionCulling::front = Plane();
Plane OcclusionCulling::back = Plane();

OcclusionCulling::OcclusionCulling()
{
	camera = nullptr;

	up = Plane();
	down = Plane();
	left = Plane();
	right = Plane();
	front = Plane();
	back = Plane();
}

OcclusionCulling::~OcclusionCulling()
{
}

void OcclusionCulling::Init(Camera* newCamera)
{
	camera = newCamera;
}

void OcclusionCulling::Update()
{
	float fov = camera->fov;
	float aspect = camera->aspect;
	// float aspect = camera->GetAspect() / 2; --> For check oclussion culling work

	float halfHeight = camera->farPlane * (glm::tan((fov * .5f) * glm::pi<float>() / 180.f));
	float halfWidth = halfHeight * aspect;

	glm::vec3 frontFar = camera->farPlane * camera->cameraFront;

	back.SetPositionAndNormal(camera->cameraPos + camera->nearPlane * camera->cameraFront, camera->cameraFront);
	front.SetPositionAndNormal(camera->cameraPos + frontFar, - camera->cameraFront);
	right.SetPositionAndNormal(camera->cameraPos, glm::cross(camera->cameraUp, frontFar + camera->cameraRight * halfWidth));
	left.SetPositionAndNormal(camera->cameraPos, glm::cross(frontFar - camera->cameraRight * halfWidth, camera->cameraUp));
	up.SetPositionAndNormal(camera->cameraPos, glm::cross(camera->cameraRight, frontFar - camera->cameraUp * halfHeight));
	down.SetPositionAndNormal(camera->cameraPos, glm::cross(frontFar + camera->cameraUp * halfHeight, camera->cameraRight));
}

void OcclusionCulling::SetCamera(Camera* newCamera)
{
	camera = newCamera;
}