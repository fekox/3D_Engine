#include "Camera.h"
#include "iostream"

namespace camera
{
	Camera::Camera(glm::vec3 newCameraPos, glm::vec3 newCameraUp, glm::vec3 newCameraFront, float newYaw, float newPitch, float newMovementSpeed)
	{
		this->cameraPos = newCameraPos;
		this->cameraUp = newCameraUp;
		this->cameraFront = newCameraFront;
		this->yaw = newYaw;
		this->pitch = newPitch;
		this->movementSpeed = newMovementSpeed;
	}

	void Camera::CameraMovement(GLFWwindow* window)
	{
		float currentTime = Time::GetDeltaTime();

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			cameraPos += movementSpeed * cameraFront * currentTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			cameraPos -= movementSpeed * cameraFront * currentTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraFront * currentTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraFront * currentTime;
		}
		
		cameraPos.y = 0.0f;
	}

	glm::mat4 Camera::GetProjection(Window* window)
	{
		return glm::perspective(glm::radians(45.0f), window->getWidth() / window->getHeight(), nearPlane, farPlane);
	}

	glm::mat4 Camera::GetView()
	{
		return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	Camera::~Camera()
	{
	
	}
}
