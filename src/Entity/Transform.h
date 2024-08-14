#pragma once

#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"

class Transform
{
	protected:
	//Local space information
	glm::vec3 m_pos = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_eulerRot = { 0.0f, 0.0f, 0.0f }; //In degrees
	glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

	//Global space information concatenate in matrix
	glm::mat4 m_modelMatrix = glm::mat4(1.0f);

	//Dirty flag
	bool m_isDirty = true;

	public:

	glm::mat4 GetLocalModelMatrix();

	void ComputeModelMatrix();
	void ComputeModelMatrix(const glm::mat4& parentGlobalModelMatrix);
	void SetLocalPosition(const glm::vec3& newPosition);
	void SetLocalRotation(const glm::vec3& newRotation);
	void SetLocalScale(const glm::vec3& newScale);

	const glm::vec3& GetGlobalPosition() const;
	const glm::vec3& GetLocalPosition() const;
	const glm::vec3& GetLocalRotation() const;
	const glm::vec3& GetLocalScale() const;
	const glm::mat4& GetModelMatrix() const;

	glm::vec3 GetRight() const;
	glm::vec3 GetUp() const;
	glm::vec3 GetBackward() const;
	glm::vec3 GetForward() const;
	glm::vec3 GetGlobalScale() const;
	bool IsDirty() const;
};
