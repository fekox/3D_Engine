#include "Entity/Entity.h"

namespace Entity
{
	void Entity::UpdateGlobalVolume()
	{
		//if (globalVolume != nullptr)
		//{
		//	globalVolume->SetGlobalVolume();
		//}
	}

	Entity::Entity(Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation)
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

	void Entity::setPosition(Vector3 newPosition)
	{
		position = mat4(1.0);
		vec3 newPositionSet = { newPosition.x, newPosition.y, newPosition.z };
		position = translate(position, newPositionSet);
		UpdateTMatrix();
	}

	Vector3 Entity::getPosition()
	{
		return { position[3][0], position[3][1], position[3][2] };
	}

	void Entity::setScale(Vector3 newScale)
	{
		scale = mat4(1.0f);
		scale = glm::scale(scale, glm::vec3(newScale.x, newScale.y, newScale.z));
		UpdateTMatrix();
	}

	Vector3 Entity::getScale()
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

	void Entity::SetParent(Entity* parent)
	{
	}

	void Entity::AddChild(Entity* child)
	{
	}

	void Entity::RemoveChild(Entity* child)
	{
	}

	void Entity::RemoveChild(int childIndex)
	{
	}

	Entity* Entity::GetParent()
	{
		return nullptr;
	}

	list<Entity*> Entity::GetChildren()
	{
		return list<Entity*>();
	}

	Entity* Entity::GetChild(int childIndex)
	{
		return nullptr;
	}

	glm::vec3 Entity::GetForward()
	{
		return glm::vec3();
	}

	glm::vec3 Entity::GetUp()
	{
		return glm::vec3();
	}

	glm::vec3 Entity::GetRight()
	{
		return glm::vec3();
	}

	VolumeAABB* Entity::GetGlobalVolume()
	{
		return nullptr;
	}

	Vector3 Entity::getRotation()
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
	void Entity::UpdateTransform()
	{
	}
	
	void Entity::UpdateChildrenPos()
	{
	}
	
	void Entity::UpdateChildrenRot()
	{
	}
	
	void Entity::UpdateChildrenScale()
	{
	}
	
	glm::quat Entity::EulerToQuat(glm::vec3 euler)
	{
		return glm::quat();
	}
	
	glm::vec3 Entity::QuatToVec(glm::quat quat, glm::vec3 euler)
	{
		return glm::vec3();
	}
	
	glm::quat Entity::GetRotationByMatrix(glm::mat4 mat)
	{
		return glm::quat();
	}
	
	glm::vec3 Entity::ToEulerRad(glm::quat rot)
	{
		return glm::vec3();
	}
	
	glm::vec3 Entity::NormalizeAngles(glm::vec3 angles)
	{
		return glm::vec3();
	}
	
	float Entity::NormalizeAngle(float angle)
	{
		return 0.0f;
	}
}