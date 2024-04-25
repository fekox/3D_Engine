#pragma once
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include "..\libs\glm\include\glm.hpp"

namespace pointLight
{
	class EXPORT PointLight
	{
		public:

		enum PointLightType
		{
			Desert,
			Factory,
			Horror,
			BiochemicalLab
		};

		glm::vec3 lightPos;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float constant;
		float linear;
		float quadratic;

		PointLight(glm::vec3 position, glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular);
		PointLight(glm::vec3 position, glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular, float newConstant, float newLinear, float newQuadratic);
		PointLight(PointLightType pointLightType, glm::vec3 position, glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular);
		void SetPosition(glm::vec3 newPosition);
		void SetLightColor(glm::vec3 newLightColor);
		void SetConstant(float newConstant);
		void SetLinear(float newLinear);
		void SetQuadratic(float newQuadratic);
		~PointLight();
	};
}

