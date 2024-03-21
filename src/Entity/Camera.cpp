#include "Camera.h"

namespace camera
{
	Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraUp, glm::vec3 cameraFront)
	{
		this->cameraPos = cameraPos;
		this->cameraUp = cameraUp;
		this->cameraFront = cameraFront;
	}

	void Camera::SetPosition(glm::vec3 newCameraPos)
	{
		newCameraPos.x = cameraPos.x;
		newCameraPos.y = cameraPos.y;
		newCameraPos.z = cameraPos.z;
	}

	void Camera::CameraMovement()
	{

	}

	glm::vec3 Camera::GetPosition()
	{
		return cameraPos;
	}

	Camera::~Camera()
	{
	
	}
}
