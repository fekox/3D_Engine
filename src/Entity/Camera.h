#include "CoreEngine/Window.h"
#include "Tools/Time.h"
#include <GLFW/glfw3.h>
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#pragma once

using namespace window;

namespace camera
{
	class Camera
	{
		private:

			glm::vec3 cameraPos;
			glm::vec3 cameraUp;
			glm::vec3 cameraRight;
			glm::vec3 cameraFront;
			glm::vec3 cameraWorldUp;

			float yaw = -90.0f;
			float pitch = 0.0f;

			const float nearPlane = 0.1f;
			const float farPlane = 2000.0f; 

			float movementSpeed;
			float mouseSensX;
			float mouseSensY;

			float lastX;
			float lastY;
			bool firstMouse = true;

		public:

			Camera(glm::vec3 newCameraPos, glm::vec3 newCameraUp, glm::vec3 newCameraFront, float newYaw, float newPitch);
			void CameraMovement(GLFWwindow* window);
			glm::mat4 GetProjection(Window* window);
			glm::mat4 GetView();
			~Camera();

	};
}