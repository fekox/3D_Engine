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
		public:

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
			float zoom;
			float zoomSpeed;

			float lastX;
			float lastY;
			bool firstMouse = true;

			Camera();
			void CameraMovement(GLFWwindow* window);
			void UpdateCameraVectors();
			glm::mat4 GetProjection(Window* window);
			glm::mat4 GetView();
			void CheckMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
			void CheckMouseScroll(float yoffset);

			~Camera();

	};
}