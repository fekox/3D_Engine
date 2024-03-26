#include "Camera.h"

namespace camera
{
	Camera::Camera(glm::vec3 newCameraPos, glm::vec3 newCameraUp, glm::vec3 newCameraFront, float newYaw, float newPitch)
	{
		this->cameraPos = newCameraPos;
		this->cameraUp = newCameraUp;
		this->cameraFront = newCameraFront;
		this->yaw = newYaw;
		this->pitch = newPitch;
	}

	void Camera::CameraMovement(GLFWwindow* window)
	{
		float currentTime = Time::GetDeltaTime();

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			cameraPos += movementSpeed * cameraFront * currentTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			cameraPos -= movementSpeed * cameraFront * currentTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraFront * currentTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
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
