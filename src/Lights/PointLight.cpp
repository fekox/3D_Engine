#include "Lights/PointLight.h"

namespace pointLight
{
	PointLight::PointLight()
	{
		lightPos = glm::vec3(0);
		ambient = glm::vec3(1);
		diffuse = glm::vec3(1);
		specular = glm::vec3(1);

		constant = 0.09f;
		linear = 0.032f;
	}

	PointLight::PointLight(glm::vec3 position, glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular)
	{
		lightPos = position;
		ambient = newAmbient;
		diffuse = newDiffuse;
		specular = newSpecular;

		constant = 0.09f;
		linear = 0.032f;
	}

	PointLight::PointLight(glm::vec3 position, glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular, float newConstant, float newLinear, float newQuadratic)
	{
		lightPos = position;
		ambient = newAmbient;
		diffuse = newDiffuse;
		specular = newSpecular;

		constant = newConstant;
		linear = newLinear;
	}

	void PointLight::SetPosition(glm::vec3 newPosition)
	{
		this->lightPos = newPosition;
	}

	void PointLight::SetLightColor(glm::vec3 newLightColor)
	{
		this->ambient = newLightColor * 0.1f;
		this->diffuse = newLightColor;
		this->specular = newLightColor;
	}

	void PointLight::SetConstant(float newConstant)
	{
		this->constant = newConstant;
	}

	void PointLight::SetLinear(float newLinear)
	{
		this->linear = newLinear;
	}

	PointLight::~PointLight()
	{
	
	}
}