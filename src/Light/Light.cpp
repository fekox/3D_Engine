#include "Light/Light.h"

namespace light
{
	Light::Light()
	{
		SetLightPos(100, 10, 10);
		SetLightColor(1, 1, 1);
		SetAmbientLightStrength(1);
	}

	void Light::SetLightPos(float newLightPosX, float newLightPosY, float newLightPosZ)
	{
		lightPos = glm::vec3(newLightPosX, newLightPosY, newLightPosZ);
	}
	
	void Light::SetAmbientLightStrength(float newAmbientStrength) 
	{
		ambientStrength = glm::clamp(newAmbientStrength, 0.0f, 1.0f);
	}

	void Light::SetLightColor(float newLightColorX, float newLightColorY, float newLightColorZ)
	{
		lightColor = glm::vec3(newLightColorX, newLightColorY, newLightColorZ);
	}

	Light::~Light()
	{
	
	}
}
