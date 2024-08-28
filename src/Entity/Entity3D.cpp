#include "Entity/Entity3D.h"

namespace entity3D
{
	Entity3D::Entity3D(Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation) : Entity(render, newPosition, newScale, newRotation)
	{

	}

	void Entity3D::DrawShape3D(Material* material)
	{
		render->DrawEntity3D(VAO, lightCubeVAO, indexSize, color, model, material);
	}

	void Entity3D::SetColor(Vector4 rgba)
	{
		color = rgba;
	}

	Vector4 Entity3D::GetColor()
	{
		return color;
	}

	Entity3D::~Entity3D()
	{
	
	}
}