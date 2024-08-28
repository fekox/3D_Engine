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

		setRotationX(0);
		setRotationY(0);
		setRotationZ(0);
		setScale({1,1,1});

		setRotationX(newRotation.x);
		setRotationY(newRotation.y);
		setRotationZ(newRotation.z);
		setScale(newScale);

		UpdateTMatrix();
	}

	Entity::~Entity()
	{

	}

	void Entity::setPosition(glm::vec3 newPosition)
	{
		position = mat4(1.0);
		glm::vec3 newPositionSet = { newPosition.x, newPosition.y, newPosition.z };
		position = translate(position, newPositionSet);
		UpdateTMatrix();
	}

	glm::vec3 Entity::getPosition()
	{
		return { position[3][0], position[3][1], position[3][2] };
	}

	void Entity::setScale(glm::vec3 newScale)
	{
		scale = mat4(1.0f);
		scale = glm::scale(scale, glm::vec3(newScale.x, newScale.y, newScale.z));
		UpdateTMatrix();
	}

	glm::vec3 Entity::getScale()
	{
		return { scale[0][0], scale[1][1], scale[2][2] };
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
		glm::mat3 rotationMatrix3x3 = glm::mat3(rotation);

		// Extract Euler angles from the 3x3 rotation matrix
		float pitch, yaw, roll;

		// Extract pitch (X-axis rotation)
		pitch = asin(rotationMatrix3x3[1][2]);

		// Check for gimbal lock
		if (cos(pitch) != 0) 
		{
			// Extract yaw (Y-axis rotation)
			yaw = atan2(-rotationMatrix3x3[0][2], rotationMatrix3x3[2][2]);

			// Extract roll (Z-axis rotation)
			roll = atan2(-rotationMatrix3x3[1][0], rotationMatrix3x3[1][1]);
		}
		
		else 
		{
			// Gimbal lock case
			yaw = 0; // You can set yaw to any value since roll will be zero
			roll = atan2(rotationMatrix3x3[0][1], rotationMatrix3x3[0][0]);
		}

		return { glm::degrees(pitch), glm::degrees(yaw), glm::degrees(roll) };
	}

	void Entity::UpdateTMatrix()
	{
		model = position * rotation * scale;
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