#pragma once
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include "..\libs\glm\include\glm.hpp"
#include "Camera/Camera.h"

using namespace camera;

namespace spotLight
{
	class EXPORT SpotLight
	{
		public:

		enum SpotLightType
		{
			Desert,
			Factory,
			Horror,
			BiochemicalLab
		};

		glm::vec3 lightPos;
		glm::vec3 direction;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float constant;
		float linear;
		float quadratic;
		float cutOff;
		float outerCutOff;

		SpotLight(Camera* camera);
		SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff);
		SpotLight(SpotLightType spotLightType, Camera* camera);

		void SetPosition(glm::vec3 newPosition);
		void SetDirection(glm::vec3 newDirection);
		void SetLightColor(glm::vec3 newLightColor);
		void SetConstant(float newConstant);
		void SetLinear(float newLinear);
		void SetQuadratic(float newQuadratic);
		void SetCutOff(float newcutOff);
		void SetOuterCutOff(float newouterCutOff);

		~SpotLight();
	};
}
