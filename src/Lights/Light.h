#pragma once
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include "..\libs\glm\include\glm.hpp"

namespace light
{
	class EXPORT Light
	{
		public:

		float ambientStrength;
		glm::vec3 lightPos;
		glm::vec3 lightColor;

		Light();
		void SetLightPos(float newLightPosX, float newLightPosY, float newLightPosZ);
		void SetAmbientLightStrength(float newAmbientStrength);
		void SetLightColor(float newLightColorX, float newLightColorY, float newLightColorZ);
		~Light();
	};
}