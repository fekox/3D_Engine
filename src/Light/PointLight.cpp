#include "Light/PointLight.h"

namespace pointLight
{
	PointLight::PointLight(glm::vec3 position, glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular)
	{
		lightPos = position;
		ambient = newAmbient;
		diffuse = newDiffuse;
		specular = newSpecular;

		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;
	}

	PointLight::PointLight(glm::vec3 position, glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular, float newConstant, float newLinear, float newQuadratic)
	{
		lightPos = position;
		ambient = newAmbient;
		diffuse = newDiffuse;
		specular = newSpecular;

		constant = newConstant;
		linear = newLinear;
		quadratic = newQuadratic;
	}

	PointLight::PointLight(PointLightType pointLightType, glm::vec3 position, glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular)
	{
		switch (pointLightType)
		{
			case pointLight::PointLight::Desert:

				lightPos = position;
				ambient = newAmbient;
				diffuse = newDiffuse;
				specular = newSpecular;

				constant = 1.0f;
				linear = 0.09;
				quadratic = 0.032;

			break;

			case pointLight::PointLight::Factory:

				lightPos = position;
				ambient = newAmbient;
				diffuse = newDiffuse;
				specular = newSpecular;

				constant = 1.0f;
				linear = 0.09;
				quadratic = 0.032;

			break;

			case pointLight::PointLight::Horror:

				lightPos = position;
				ambient = newAmbient;
				diffuse = newDiffuse;
				specular = newSpecular;

				constant = 1.0f;
				linear = 0.14;
				quadratic = 0.07;

			break;

			case pointLight::PointLight::BiochemicalLab:

				lightPos = position;
				ambient = newAmbient;
				diffuse = newDiffuse;
				specular = newSpecular;

				constant = 1.0f;
				linear = 0.14;
				quadratic = 0.07;

			break;
		}
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

	void PointLight::SetQuadratic(float newQuadratic)
	{
		this->quadratic = newQuadratic;
	}

	PointLight::~PointLight()
	{
	
	}
}