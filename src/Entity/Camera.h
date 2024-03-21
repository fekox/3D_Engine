#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"

#pragma once

namespace camera
{
	class Camera
	{
		private:

			glm::vec3 cameraPos;
			glm::vec3 cameraUp;
			glm::vec3 cameraFront;

		public:

			Camera(glm::vec3 cameraPos, glm::vec3 cameraUp, glm::vec3 cameraFront);
			void SetPosition(glm::vec3 newCameraPos);
			void CameraMovement();
			glm::vec3 GetPosition();
			~Camera();

	};
}