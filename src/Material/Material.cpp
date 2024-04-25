#include "Material/Material.h"

namespace material
{
	Material::Material(vec3 ambient, vec3 diffuseV3, vec3 specularV3, float shininess)
	{
		this->ambient = ambient;
		this->diffuseV3 = diffuseV3;
		this->specularV3 = specularV3;
		this->shininess = shininess;
	}

	Material::Material(int diffuseINT, int specularINT, float shininess)
	{
		this->diffuseINT = diffuseINT;
		this->specularINT = specularINT;
		this->shininess = shininess;
	}

	void Material::SetMaterial(MaterialType newMaterial)
	{
		switch (newMaterial)
		{
			case MaterialType::NORMAL:

			ambient = glm::vec3(1.0f, 0.5f, 0.31f);
			diffuseV3 = glm::vec3(1.0f, 0.5f, 0.31f);
			specularV3 = glm::vec3(0.5f, 0.5f, 0.5f);
			shininess = 32.0f;

			break;

			case MaterialType::EMERALD:

			ambient = glm::vec3(0.0215, 0.1745, 0.0215);
			diffuseV3 = glm::vec3(0.07568, 0.61424, 0.07568);
			specularV3 = glm::vec3(0.633, 0.727811, 0.633);
			shininess = 0.6;

			break;

			case MaterialType::JADE:

			ambient = glm::vec3(0.135, 0.2225, 0.1575);
			diffuseV3 = glm::vec3(0.54, 0.89, 0.63);
			specularV3 = glm::vec3(0.316228, 0.316228, 0.316228);
			shininess = 0.1;

			break;

			case MaterialType::OBSIDIAN:

			ambient = glm::vec3(0.05375, 0.05, 0.06625);
			diffuseV3 = glm::vec3(0.18275, 0.17, 0.22525);
			specularV3 = glm::vec3(0.332741, 0.328634, 0.346435);
			shininess = 0.3;

			break;

			case MaterialType::PEARL:

			ambient = glm::vec3(0.25, 0.20725, 0.20725);
			diffuseV3 = glm::vec3(1, 0.829, 0.829);
			specularV3 = glm::vec3(0.296648, 0.296648, 0.296648);
			shininess = 0.088;

			break;

			case MaterialType::RUBY:

			ambient = glm::vec3(0.1745, 0.01175, 0.01175);
			diffuseV3 = glm::vec3(0.61424, 0.04136, 0.04136);
			specularV3 = glm::vec3(0.727811, 0.626959, 0.626959);
			shininess = 0.6;

			break;

			case MaterialType::TURQUOISE:

			ambient = glm::vec3(0.1, 0.18725, 0.1745);
			diffuseV3 = glm::vec3(0.396, 0.74151, 0.69102);
			specularV3 = glm::vec3(0.297254, 0.30829, 0.306678);
			shininess = 0.1;

			break;

			case MaterialType::BRASS:

			ambient = glm::vec3(0.329412, 0.223529, 0.027451); 
			diffuseV3 = glm::vec3(0.780392, 0.568627, 0.113725);
			specularV3 = glm::vec3(0.992157, 0.941176, 0.807843);
			shininess = 0.21794872;
		
			break;

			case MaterialType::BRONZE:

			ambient = glm::vec3(0.2125, 0.1275, 0.054);
			diffuseV3 = glm::vec3(0.714, 0.4284, 0.18144);
			specularV3 = glm::vec3(0.393548, 0.271906, 0.166721);
			shininess = 0.2;
	
			break;

			case MaterialType::CHROME:

			ambient = glm::vec3(0.25, 0.25, 0.25);
			diffuseV3 = glm::vec3(0.4, 0.4, 0.4);
			specularV3 = glm::vec3(0.774597, 0.774597, 0.774597);
			shininess = 0.6;

			break;

			case MaterialType::COPPER:

			ambient = glm::vec3(0.19125, 0.0735, 0.0225);
			diffuseV3 = glm::vec3(0.7038, 0.27048, 0.0828);
			specularV3 = glm::vec3(0.256777, 0.137622, 0.086014);
			shininess = 0.1;

			break;

			case MaterialType::GOLD:

			ambient = glm::vec3(0.24725, 0.1995, 0.0745);
			diffuseV3 = glm::vec3(0.75164, 0.60648, 0.22648);
			specularV3 = glm::vec3(0.628281, 0.555802, 0.366065);
			shininess = 0.4;

			break;

			case MaterialType::SILVER:

			ambient = glm::vec3(0.19225, 0.19225, 0.19225);
			diffuseV3 = glm::vec3(0.50754, 0.50754, 0.50754);
			specularV3 = glm::vec3(0.508273, 0.508273, 0.508273);
			shininess = 0.4;

			break;

			case MaterialType::BLACK_PLASTIC:

			ambient = glm::vec3(0.0, 0.0, 0.0);
			diffuseV3 = glm::vec3(0.01, 0.01, 0.01);
			specularV3 = glm::vec3(0.50, 0.50, 0.50);
			shininess = 0.25;

			break;

			case MaterialType::CYAN_PLASTIC:

			ambient = glm::vec3(0.0, 0.1, 0.06);
			diffuseV3 = glm::vec3(0.0, 0.50980392, 0.50980392);
			specularV3 = glm::vec3(0.50196078, 0.50196078, 0.50196078);
			shininess = 0.25;

			break;

			case MaterialType::GREEN_PLASTIC:

			ambient = glm::vec3(0.0, 0.0, 0.0);
			diffuseV3 = glm::vec3(0.1, 0.35, 0.1);
			specularV3 = glm::vec3(0.45, 0.55, 0.45);
			shininess = 0.25;

			break;

			case MaterialType::RED_PLASTIC:

			ambient = glm::vec3(0.0, 0.0, 0.0);
			diffuseV3 = glm::vec3(0.5, 0.0, 0.0);
			specularV3 = glm::vec3(0.7, 0.6, 0.6);
			shininess = 0.25;

			break;
		}
	}

	Material::~Material()
	{

	}
}

