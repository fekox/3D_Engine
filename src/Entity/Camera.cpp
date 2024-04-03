#include "Entity/Camera.h"

namespace camera
{
	Camera::Camera()
	{
		cameraPos = glm::vec3(0.0f, 0.0f, 300.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		cameraWorldUp = cameraUp;

		yaw = -90.0f;
		pitch = 0.0f;

		nearPlane = 0.1f;
		farPlane = 2000.0f;

		previousTargetRotation = glm::vec3(0.0f, 0.0f, 0.0f);

		movementSpeed = 500.0f;
		zoomSpeed = 10.0f;
		mouseSensX = 0.2f;
		mouseSensY = 0.1f;
		firstMouse = true;

		UpdateCameraVectors();
	}

	void Camera::CameraMovement(GLFWwindow* window)
	{
		if (!thirdPerson)
		{
			float deltaTime = 0.0f;
			float lastFrame = 0.0f;
			float currentFrame = Time::GetDeltaTime();

			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				cameraPos += movementSpeed * cameraFront * deltaTime;
			}

			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				cameraPos -= movementSpeed * cameraFront * deltaTime;
			}

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed * deltaTime;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed * deltaTime;
			}

			UpdateCameraVectors();
		
		}
	}

	void Camera::UpdateCameraVectors()
	{
		glm::vec3 direction;

		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		cameraFront = glm::normalize(direction);
		cameraRight = glm::normalize(glm::cross(cameraFront, cameraWorldUp));
		cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
	}

	glm::mat4 Camera::UpdateCameraViewMode()
	{
		switch (viewMode)
		{
			case Camera::CameraMode::FistPerson:
				thirdPerson = false;
				return GetViewFirstPerson();
			break;

			case Camera::CameraMode::ThirdPerson:
				thirdPerson = true;
				return GetViewThirdPerson();
			break;

			case Camera::CameraMode::SpectateObject:
				thirdPerson = false;
				return GetViewToSpectateObject();
			break;
		}
	}

	void Camera::SetCameraMode(CameraMode cameraMode)
	{
		this->viewMode = cameraMode;
	}

	void Camera::ChangeCameraTarget(glm::vec3 target, glm::vec3 rotationEulerAngle)
	{
		if (thirdPerson)
		{
			float distanceToTarget = 500.0f;

			cameraTarget = target;
			cameraPos = target + cameraFront * distanceToTarget;

			float newRotationY = previousTargetRotation.y - rotationEulerAngle.y;

			yaw += newRotationY;
			previousTargetRotation = rotationEulerAngle;
			UpdateCameraVectors();
		}
	}

	glm::mat4 Camera::GetProjection(Window* window)
	{
		return glm::perspective(glm::radians(zoom), window->getWidth() / window->getHeight(), nearPlane, farPlane);
	}

	glm::mat4 Camera::GetViewFirstPerson()
	{
		return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	glm::mat4 Camera::GetViewThirdPerson()
	{
		return lookAt(cameraPos, cameraTarget, cameraUp);
	}

	glm::mat4 Camera::GetViewToSpectateObject()
	{
		const float radius = -300.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		return glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	}

	void Camera::CheckMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
	{
		xoffset *= mouseSensX;
		yoffset *= mouseSensY;

		yaw += xoffset;
		pitch += yoffset;

		if (constrainPitch)
		{
			if (pitch > 89.0f)
			{
				pitch = 89.0f;
			}

			if (pitch < -89.0f)
			{
				pitch = -89.0f;
			}
		}

		UpdateCameraVectors();
	}

	void Camera::CheckMouseScroll(float yoffset)
	{
		float currentZoom = 110.0f;

		zoom -= yoffset * zoomSpeed;

		if (zoom < 1.0f)
		{
			zoom = 1.0f;
		}

		if (zoom > 110.0f)
		{
			zoom = currentZoom;
		}
	}
}