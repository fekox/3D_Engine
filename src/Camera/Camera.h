#include "CoreEngine/Window.h"
#include "Tools/Time/Time.h"
#include <GLFW/glfw3.h>
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#pragma once

using namespace window;

namespace camera
{
	class EXPORT Camera
	{
		public:

			enum class CameraMode
			{
				FistPerson,
				ThirdPerson,
				SpectateObject,
				Last
			};

			glm::vec3 cameraPos;
			glm::vec3 cameraUp;
			glm::vec3 cameraRight;
			glm::vec3 cameraFront;
			glm::vec3 cameraWorldUp;

			glm::vec3 cameraTarget;
			glm::vec3 previousTargetRotation;
			glm::vec3 cameraDirection;

			CameraMode viewMode;

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
			bool thirdPerson = false;

			Camera();
			void CameraMovement(GLFWwindow* window);
			void UpdateCameraVectors();
			glm::mat4 UpdateCameraViewMode();
			void SetCameraMode(CameraMode cameraMode);
			void ChangeCameraTarget(glm::vec3 target, glm::vec3 rotationEulerAngle);
			glm::mat4 GetProjection(Window* window);
			glm::mat4 GetViewFirstPerson();
			glm::mat4 GetViewThirdPerson();
			glm::mat4 GetViewToSpectateObject();
			void CheckMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
			void CheckMouseScroll(float yoffset);
	};
}