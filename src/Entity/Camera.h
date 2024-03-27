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

			float yaw;
			float pitch;

			float nearPlane;
			float farPlane; 

			float movementSpeed;
			float mouseSensX;
			float mouseSensY;

			float lastX;
			float lastY;
			bool firstMouse = true;

		public:

			Camera();
			void CameraMovement(GLFWwindow* window);
			void UpdateCameraVectors();
			glm::mat4 GetProjection(Window* window);
			glm::mat4 GetView();
			~Camera();

	};
}