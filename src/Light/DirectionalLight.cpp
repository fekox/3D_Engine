#include "Light/DirectionalLight.h"

namespace directionalLight
{
	DirectionalLight::DirectionalLight()
	{
		direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		specular = glm::vec3(0.5f, 0.5f, 0.5f);
	}

	DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->direction = direction;
	}

	DirectionalLight::DirectionalLight(DirectionalLightType directionalLightType)
	{
		switch (directionalLightType)
		{
			case directionalLight::DirectionalLight::Desert:

				direction = glm::vec3(-0.2f, -1.0f, -0.3f);
				ambient = glm::vec3(0.3f, 0.24f, 0.14f);
				diffuse = glm::vec3(0.7f, 0.42f, 0.26f);
				specular = glm::vec3(0.5f, 0.5f, 0.5f);

			break;

			case directionalLight::DirectionalLight::Factory:

				direction = glm::vec3(-0.2f, -1.0f, -0.3f);
				ambient = glm::vec3(0.05f, 0.05f, 0.1f);
				diffuse = glm::vec3(0.2f, 0.2f, 0.7);
				specular = glm::vec3(0.7f, 0.7f, 0.7f);

			break;

			case directionalLight::DirectionalLight::Horror:

				direction = glm::vec3(-0.2f, -1.0f, -0.3f);
				ambient = glm::vec3(0.0f, 0.0f, 0.0f);
				diffuse = glm::vec3(0.05f, 0.05f, 0.05);
				specular = glm::vec3(0.2f, 0.2f, 0.2f);

			break;

			case directionalLight::DirectionalLight::BiochemicalLab:

				direction = glm::vec3(-0.2f, -1.0f, -0.3f);
				ambient = glm::vec3(0.5f, 0.5f, 0.5f);
				diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
				specular = glm::vec3(1.0f, 1.0f, 1.0f);

			break;
		}
	}

	void DirectionalLight::SetDirection(glm::vec3 newDirection)
	{
		this->direction = newDirection;
	}

	void DirectionalLight::SetAmbient(glm::vec3 newAmbient)
	{
		this->ambient = newAmbient;
	}

	void DirectionalLight::SetDiffuse(glm::vec3 newDiffuse)
	{
		this->diffuse = newDiffuse;
	}

	void DirectionalLight::SetSpecular(glm::vec3 newSpecular)
	{
		this->specular = newSpecular;
	}

	DirectionalLight::~DirectionalLight()
	{
	
	}

}
