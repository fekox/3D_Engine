#include "Entity/Entity.h"

namespace entity
{
	Entity::Entity(Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation)
	{
		this->render = render;

		model = glm::mat4(1);
		position = glm::mat4(1);
		scale = glm::mat4(1);
		rotation = glm::mat4(1);

		transform = new Transform(newPosition, newScale, newRotation);

		setPosition(newPosition);

		setRotation(newRotation);

		setScale(newScale);

		transform->ComputeModelMatrix();
		model = transform->GetModelMatrix();
	}

	Entity::Entity(Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation, Transform* parent)
	{
		this->render = render;

		model = glm::mat4(1);
		position = glm::mat4(1);
		scale = glm::mat4(1);
		rotation = glm::mat4(1);

		if (parent == nullptr)
		{
			transform = new Transform(newPosition, newScale, newRotation);
		}

		else
		{
			transform = new Transform(newPosition, newScale, newRotation, parent);
		}

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

	AABB Entity::GetGlobalAABB()
	{
		//Get global scale thanks to our transform
		glm::vec3 globalCenter{ transform->GetModelMatrix() * glm::vec4(boundingVolume.center, 1.f) };

		// Scaled orientation
		glm::vec3 right = transform->GetRight() * boundingVolume.extents.x;
		glm::vec3 up = transform->GetUp() * boundingVolume.extents.y;
		glm::vec3 forward = transform->GetForward() * boundingVolume.extents.z;

		float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

		float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

		float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

		return AABB(globalCenter, newIi, newIj, newIk);
	}
}