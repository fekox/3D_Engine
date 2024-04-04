#include "Entity/Entity3D.h"

namespace entity3D
{
	Entity3D::Entity3D(Vector4 rgba, Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation) : Entity(render, newPosition, newScale, newRotation)
	{
		this->color = rgba;
	}

	void Entity3D::DrawShape3D()
	{
		render->DrawEntity3D(VAO, indexSize, color, model);
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