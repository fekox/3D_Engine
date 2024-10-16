#include "Transform.h"

Transform::Transform(Entity* newEntity) : Component(newEntity)
{
	this->m_pos = glm::vec3(1.0f);
	this->m_eulerRot = glm::vec3(1.0f);
	this->m_scale = glm::vec3(1.0f);

	m_modelMatrix = glm::mat4(1.0f);

	m_isDirty = true;

	UpdateSelfAndChild();
}

Transform::Transform(Entity* newEntity, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Component(newEntity)
{
	this->m_pos = position;
	this->m_eulerRot = rotation;
	this->m_scale = scale;

	m_modelMatrix = glm::mat4(1.0f);

	m_isDirty = true;

	UpdateSelfAndChild();
}

Transform::Transform(Entity* newEntity, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Transform* parent) : Component(newEntity)
{
	this->m_pos = position;
	this->m_eulerRot = rotation;
	this->m_scale = scale;

	this->parent = parent;
	parent->children.push_back(this);

	m_modelMatrix = glm::mat4(1.0f);

	m_isDirty = true;

	UpdateSelfAndChild();
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetLocalModelMatrix()
{
	const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(m_eulerRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(m_eulerRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_eulerRot.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// Y * X * Z
	const glm::mat4 rotationMatrix = transformY * transformX * transformZ;

	// translation * rotation * scale (also know as TRS matrix)
	return glm::translate(glm::mat4(1.0f), m_pos) * rotationMatrix * glm::scale(glm::mat4(1.0f), m_scale);
}

glm::mat4 Transform::GetLocalModelMatrixConst() const
{
	const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(m_eulerRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(m_eulerRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_eulerRot.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// Y * X * Z
	const glm::mat4 rotationMatrix = transformY * transformX * transformZ;

	// translation * rotation * scale (also know as TRS matrix)
	return glm::translate(glm::mat4(1.0f), m_pos) * rotationMatrix * glm::scale(glm::mat4(1.0f), m_scale);
}

void Transform::ComputeModelMatrix()
{
	m_modelMatrix = GetLocalModelMatrix();
	m_isDirty = false;
}

void Transform::ComputeModelMatrix(glm::mat4 parentGlobalModelMatrix)
{
	m_modelMatrix = parentGlobalModelMatrix * GetLocalModelMatrix();
	m_isDirty = false;
}

void Transform::SetLocalPosition(glm::vec3 newPosition)
{
	m_pos = newPosition;
	m_isDirty = true;
}

void Transform::SetLocalRotation(glm::vec3 newRotation)
{
	m_eulerRot = newRotation;
	m_isDirty = true;
}

void Transform::SetLocalScale(glm::vec3 newScale)
{
	m_scale = newScale;
	m_isDirty = true;
}

glm::vec3 Transform::GetGlobalPosition()
{
	return m_modelMatrix[3];
}

glm::vec3 Transform::GetLocalPosition()
{
	return m_pos;
}

glm::vec3 Transform::GetLocalRotation() 
{
	return m_eulerRot;
}

glm::vec3 Transform::GetLocalScale()
{
	return m_scale;
}

glm::mat4 Transform::GetModelMatrix()
{
	return m_modelMatrix;
}

glm::vec3 Transform::GetRight() 
{
	return m_modelMatrix[0];
}

glm::vec3 Transform::GetRightConst() const
{
	return m_modelMatrix[0];
}

glm::vec3 Transform::GetUp()
{
	return m_modelMatrix[1];
}

glm::vec3 Transform::GetUpConst() const
{
	return m_modelMatrix[1];
}

glm::vec3 Transform::GetBackward()
{
	return m_modelMatrix[2];
}

glm::vec3 Transform::GetBackwardConst() const
{
	return m_modelMatrix[2];
}

glm::vec3 Transform::GetForward()
{
	return -m_modelMatrix[2];
}

glm::vec3 Transform::GetForwardConst() const
{
	return -m_modelMatrix[2];
}

glm::vec3 Transform::GetGlobalScale()
{
	return { glm::length(GetRight()), glm::length(GetUp()), glm::length(GetBackward()) };
}

bool Transform::IsDirty()
{
	return m_isDirty;
}

void Transform::AddChild(Transform* newChild)
{
	children.push_back(newChild);
	children.back()->parent = this;
}

void Transform::UpdateSelfAndChild()
{
	m_modelMatrix = GetModelMatrix();

	if (IsDirty())
	{
		ForceUpdateSelfAndChild();
		return;
	}

	for (auto&& child : children)
	{
		child->UpdateSelfAndChild();
	}
}

void Transform::ForceUpdateSelfAndChild()
{
	if (parent != nullptr)
		ComputeModelMatrix(parent->GetModelMatrix());
	else
		ComputeModelMatrix();

	for (auto&& child : children)
	{
		child->ForceUpdateSelfAndChild();
	}
}