#include "Transform.h"

Transform::Transform()
{
	glm::vec3 m_pos = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_eulerRot = { 0.0f, 0.0f, 0.0f }; 
	glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

	glm::mat4 m_modelMatrix = glm::mat4(1.0f);

	bool m_isDirty = true;
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

	ComputeModelMatrix();
}

void Transform::SetLocalRotation(glm::vec3 newRotation)
{
	m_eulerRot = newRotation;
	m_isDirty = true;

	ComputeModelMatrix();
}

void Transform::SetLocalScale(glm::vec3 newScale)
{
	m_scale = newScale;
	m_isDirty = true;

	ComputeModelMatrix();
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

glm::vec3 Transform::GetUp()
{
	return m_modelMatrix[1];
}

glm::vec3 Transform::GetBackward()
{
	return m_modelMatrix[2];
}

glm::vec3 Transform::GetForward()
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
