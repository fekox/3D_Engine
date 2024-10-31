#include "Entity/Entity.h"

Entity::Entity(Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation, bool turnOffByBSP)
{
	this->render = render;

	model = glm::mat4(1);
	position = glm::mat4(1);
	scale = glm::mat4(1);
	rotation = glm::mat4(1);

	transform = new Transform(this, newPosition, newRotation, newScale);

	this->turnOffByBSP = turnOffByBSP;

	setPosition(newPosition);

	setRotation(newRotation);

	setScale(newScale);

	transform->ForceUpdateSelfAndChild();
}

Entity::Entity(Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation, Transform* parent, bool turnOffByBSP)
{
	this->render = render;

	model = glm::mat4(1);
	position = glm::mat4(1);
	scale = glm::mat4(1);
	rotation = glm::mat4(1);

	if (parent == nullptr)
	{
		transform = new Transform(this, newPosition, newScale, newRotation);
	}

	else
	{
		transform = new Transform(this, newPosition, newScale, newRotation, parent);
	}

	this->turnOffByBSP = turnOffByBSP;

	setPosition(newPosition);

	setRotation(newRotation);

	setScale(newScale);

	transform->ForceUpdateSelfAndChild();
}

Entity::~Entity()
{

}

void Entity::setPosition(glm::vec3 newPosition)
{
	transform->SetLocalPosition(newPosition);
	transform->UpdateSelfAndChild();
}

void Entity::setScale(glm::vec3 newScale)
{
	transform->SetLocalScale(newScale);
	transform->UpdateSelfAndChild();
}

void Entity::setRotation(glm::vec3 newRotation)
{
	transform->SetLocalRotation(newRotation);
	transform->UpdateSelfAndChild();
}

glm::vec3 Entity::getPosition()
{
	return transform->GetLocalPosition();
}

glm::vec3 Entity::getScale()
{
	return transform->GetLocalScale();
}

void Entity::setRotationX(float newRotationX)
{
	rotation = glm::rotate(rotation, glm::radians(newRotationX), glm::vec3(1, 0, 0));
	transform->ComputeModelMatrix();
}

void Entity::setRotationY(float newRotationY)
{
	rotation = glm::rotate(rotation, glm::radians(newRotationY), glm::vec3(0, 1, 0));
	transform->ComputeModelMatrix();
}

void Entity::setRotationZ(float newRotationZ)
{
	rotation = glm::rotate(rotation, glm::radians(newRotationZ), glm::vec3(0, 0, 1));
	transform->ComputeModelMatrix();
}

glm::vec3 Entity::getRotation()
{
	return transform->GetLocalRotation();
}

void Entity::UpdateTMatrix()
{
	model = transform->GetModelMatrix();
}

Renderer* Entity::GetRenderer()
{
	return render;
}
