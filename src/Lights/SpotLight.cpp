#include "Lights/SpotLight.h"

namespace spotLight
{
	SpotLight::SpotLight(Camera* camera)
	{
		lightPos = camera->cameraPos;
		direction = camera->cameraFront;

		ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		specular = glm::vec3(1.0f, 1.0f, 1.0f);
		constant = 1.0f;
		linear = 0.09;
		quadratic = 0.032;
		cutOff = glm::cos(glm::radians(40.5f));
		outerCutOff = glm::cos(glm::radians(45.0f));
	}

	SpotLight::SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;

		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
		this->cutOff = cutOff;
		this->outerCutOff = outerCutOff;
	}

	SpotLight::SpotLight(SpotLightType spotLightType, Camera* camera)
	{
		switch (spotLightType)
		{
			case spotLight::SpotLight::Desert:

				lightPos = camera->cameraPos;
				direction = camera->cameraFront;

				ambient = glm::vec3(0.0f, 0.0f, 0.0f);
				diffuse = glm::vec3(0.8f, 0.8f, 0.0f);
				specular = glm::vec3(0.8f, 0.8f, 0.0f);

				constant = 1.0f;
				linear = 0.09;
				quadratic = 0.032;
				cutOff = glm::cos(glm::radians(12.5f));
				outerCutOff = glm::cos(glm::radians(13.0f));

			break;

			case spotLight::SpotLight::Factory:

				lightPos = camera->cameraPos;
				direction = camera->cameraFront;

				ambient = glm::vec3(0.0f, 0.0f, 0.0f);
				diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
				specular = glm::vec3(1.0f, 1.0f, 1.0f);

				constant = 1.0f;
				linear = 0.009;
				quadratic = 0.0032;
				cutOff = glm::cos(glm::radians(10.0f));
				outerCutOff = glm::cos(glm::radians(12.5f));

			break;

			case spotLight::SpotLight::Horror:

				lightPos = camera->cameraPos;
				direction = camera->cameraFront;

				ambient = glm::vec3(0.0f, 0.0f, 0.0f);
				diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
				specular = glm::vec3(1.0f, 1.0f, 1.0f);

				constant = 1.0f;
				linear = 0.09;
				quadratic = 0.032;
				cutOff = glm::cos(glm::radians(10.0f));
				outerCutOff = glm::cos(glm::radians(15.0f));

			break;

			case spotLight::SpotLight::BiochemicalLab:

				lightPos = camera->cameraPos;
				direction = camera->cameraFront;

				ambient = glm::vec3(0.0f, 0.0f, 0.0f);
				diffuse = glm::vec3(0.0f, 1.0f, 0.0f);
				specular = glm::vec3(0.0f, 1.0f, 0.0f);

				constant = 1.0f;
				linear = 0.07;
				quadratic = 0.017;
				cutOff = glm::cos(glm::radians(7.0f));
				outerCutOff = glm::cos(glm::radians(10.0f));

			break;
		}
	}

	void SpotLight::SetPosition(glm::vec3 newPosition)
	{
		this->lightPos = newPosition;
	}

	void SpotLight::SetDirection(glm::vec3 newDirection)
	{
		this->direction = newDirection;
	}

	void SpotLight::SetConstant(float newConstant)
	{
		this->constant = newConstant;
	}

	void SpotLight::SetLinear(float newLinear)
	{
		this->linear = newLinear;
	}

	void SpotLight::SetQuadratic(float newQuadratic)
	{
		this->quadratic = newQuadratic;
	}

	void SpotLight::SetCutOff(float newcutOff)
	{
		this->cutOff = newcutOff;
	}

	void SpotLight::SetOuterCutOff(float newOuterCutOff)
	{
		this->outerCutOff = newOuterCutOff;
	}

	SpotLight::~SpotLight()
	{
	
	}
}
