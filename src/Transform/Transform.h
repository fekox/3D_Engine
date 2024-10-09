#pragma once

#include <list> 
#include "Tools/DLL-Exp/dll-Exp-Inp.h"

#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"

class EXPORT Transform
{
protected:
	//Local space information
	glm::vec3 m_pos;
	glm::vec3 m_eulerRot; //In degrees
	glm::vec3 m_scale;

	//Global space information concatenate in matrix

	//Dirty flag
	bool m_isDirty;

protected:
	glm::mat4 GetLocalModelMatrix();

public:
	glm::mat4 m_modelMatrix;

	std::list<Transform*> children;
	Transform* parent;

	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Transform* parent);
	~Transform();

	void ComputeModelMatrix();
	void ComputeModelMatrix(glm::mat4 parentGlobalModelMatrix);

	void SetLocalPosition(glm::vec3 newPosition);
	void SetLocalRotation(glm::vec3 newRotation);
	void SetLocalScale(glm::vec3 newScale);

	glm::vec3 GetGlobalPosition();
	glm::vec3 GetLocalPosition();
	glm::vec3 GetLocalRotation();
	glm::vec3 GetLocalScale();
	glm::mat4 GetModelMatrix();

	glm::vec3 GetRight();
	glm::vec3 GetUp();
	glm::vec3 GetBackward();
	glm::vec3 GetForward();
	glm::vec3 GetGlobalScale();

	bool IsDirty();

	void AddChild(Transform* newChild);

	void UpdateSelfAndChild();

	void ForceUpdateSelfAndChild();
};

