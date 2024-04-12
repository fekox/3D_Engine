#include "Light.h"

namespace light
{
	Light::Light()
	{
	
	}

	void Light::SetLightPos(glm::vec3 newLightPos) 
	{
		lightPos = glm::vec3(newLightPos.x, newLightPos.y, newLightPos.z);
	}
	
	void Light::SetAmbientLightStrength(float newAmbientStrength) 
	{
		ambientStrength = glm::clamp(newAmbientStrength, 0.0f, 1.0f);
	}

	Light::~Light()
	{
	
	}
}
