#pragma once
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include "..\libs\glm\include\glm.hpp"

using namespace glm;

namespace material
{
	class EXPORT Material
	{
		public:

		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;

		enum MaterialType
		{
			NORMAL,
			EMERALD,
			JADE,
			OBSIDIAN,
			PEARL,
			RUBY,
			TURQUOISE,
			BRASS,
			BRONZE,
			CHROME,
			COPPER,
			GOLD,
			SILVER,
			BLACK_PLASTIC,
			CYAN_PLASTIC,
			GREEN_PLASTIC,
			RED_PLASTIC
		};

		Material();
		void SetMaterial(MaterialType newMaterial);
		~Material();

	};
}