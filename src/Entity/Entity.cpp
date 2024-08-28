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

		setPosition(newPosition);

		setRotation(newRotation);

		setScale(newScale);

		transform.ComputeModelMatrix();
	}

	Entity::~Entity()
	{

	}

	void Entity::setPosition(glm::vec3 newPosition)
	{
		transform.SetLocalPosition(newPosition);
		UpdateTMatrix();
	}

	glm::vec3 Entity::getPosition()
	{
		return transform.GetLocalPosition();
	}

	void Entity::setScale(glm::vec3 newScale)
	{
		transform.SetLocalScale(newScale);
		UpdateTMatrix();
	}

	void Entity::setRotation(glm::vec3 newRotation)
	{
		transform.SetLocalRotation(newRotation);

		UpdateTMatrix();
	}

	glm::vec3 Entity::getScale()
	{
		return transform.GetLocalScale();
	}

	void Entity::setRotationX(float newRotationX)
	{
		rotation = glm::rotate(rotation, glm::radians(newRotationX), glm::vec3(1, 0, 0));
		UpdateTMatrix();
	}

	void Entity::setRotationY(float newRotationY)
	{
		rotation = glm::rotate(rotation, glm::radians(newRotationY), glm::vec3(0, 1, 0));
		UpdateTMatrix();
	}

	void Entity::setRotationZ(float newRotationZ)
	{
		rotation = glm::rotate(rotation, glm::radians(newRotationZ), glm::vec3(0, 0, 1));
		UpdateTMatrix();
	}

	glm::vec3 Entity::getRotation()
	{
		return transform.GetLocalRotation();
	}

	void Entity::UpdateTMatrix()
	{
		model = transform.GetModelMatrix();
	}

	AABB Entity::GetGlobalAABB()
	{
		//Get global scale thanks to our transform
		glm::vec3 globalCenter{ transform.GetModelMatrix() * glm::vec4(boundingVolume.center, 1.f) };

		// Scaled orientation
		glm::vec3 right = transform.GetRight() * boundingVolume.extents.x;
		glm::vec3 up = transform.GetUp() * boundingVolume.extents.y;
		glm::vec3 forward = transform.GetForward() * boundingVolume.extents.z;

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
	
	void Entity::AddChild(Entity newChild)
	{
		children.push_back(newChild);
		children.back().parent = this;
	}
	
	void Entity::UpdateSelfAndChild()
	{
		if (transform.IsDirty()) 
		{
			ForceUpdateSelfAndChild();
			return;
		}

		for (auto&& child : children)
		{
			child.UpdateSelfAndChild();
		}
	}
	
	void Entity::ForceUpdateSelfAndChild()
	{
		if (parent)
			transform.ComputeModelMatrix(parent->transform.GetModelMatrix());
		else
			transform.ComputeModelMatrix();

		for (auto&& child : children)
		{
			child.ForceUpdateSelfAndChild();
		}
	}
}