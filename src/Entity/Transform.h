#pragma once

#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"

struct Transform
{
	glm::vec3 position;
	glm::vec3 eulerAngles; 
	glm::vec3 scale;
	glm::quat rotation;

	//Local space information
	glm::vec3 localPosition;
	glm::vec3 localEulerAngles;
	glm::vec3 localScale;
	glm::quat localRotation;

	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;;
};
