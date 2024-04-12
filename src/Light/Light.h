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

		Light();
		void SetLightPos(glm::vec3 newLightPos);
		void SetAmbientLightStrength(float newAmbientStrength);
		~Light();
	};
}