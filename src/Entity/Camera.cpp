#include "Camera.h"
#include "iostream"

namespace camera
{
	Camera::Camera()
	{
		cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		yaw = -90.0f;
		pitch = 0.0f;
		movementSpeed = 500.0f;

		nearPlane = 0.1f;
		farPlane = 2000.0f;

		UpdateCameraVectors();
	}

	void Camera::CameraMovement(GLFWwindow* window)
	{
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float currentFrame = Time::GetDeltaTime();

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			cameraPos += movementSpeed * cameraFront * deltaTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			cameraPos -= movementSpeed * cameraFront * deltaTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed * deltaTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed * deltaTime;
		}
		
		cameraPos.y = 0.0f;
		UpdateCameraVectors();
	}

	void Camera::UpdateCameraVectors()
	{
		glm::vec3 direction;
		yaw = -90.0f;

		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		cameraFront = glm::normalize(direction);
		cameraRight = glm::normalize(glm::cross(cameraFront, cameraWorldUp));
		cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
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
