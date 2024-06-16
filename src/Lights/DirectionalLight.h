#pragma once
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include "..\libs\glm\include\glm.hpp"

namespace directionalLight
{
	class EXPORT DirectionalLight
	{
		public:

		enum DirectionalLightType
		{
			Desert,
			Factory,
			Horror,
			BiochemicalLab
		};

		glm::vec3 direction;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float ambientStrength;

		DirectionalLight();
		DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
		DirectionalLight(DirectionalLightType directionalLightType);
		
		void SetLightColor(glm::vec3 newLightColor);
		void SetDirection(glm::vec3 newDirection);
		void SetAmbient(glm::vec3 newAmbient);
		void SetDiffuse(glm::vec3 newDiffuse);
		void SetSpecular(glm::vec3 newSpecular);
		~DirectionalLight();
	};
}

