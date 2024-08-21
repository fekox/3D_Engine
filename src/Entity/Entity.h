#pragma once
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include "Tools/Vectors/Vectors.h"
#include "CoreEngine/Renderer.h"

#include "Entity/Transform.h"

#include "Volume/VolumeAABB.h"

#include <list> 
#include <array> 
#include <memory>

using namespace vectors;
using namespace renderer;

namespace Entity
{
	class EXPORT Entity
	{
	protected:
		Renderer* render;
		glm::mat4x4 model;
		glm::mat4 position;
		glm::mat4 scale;
		glm::mat4 rotation;

		Vector3 newPosition;
		Vector3 newScale;
		Vector3 newRotation;

		Entity* parent;
		list<Entity*> childs;

		VolumeAABB* localVolume;
		VolumeAABB* globalVolume;
		bool volumeDirty;
		bool drawVolume;

		bool IsCanDraw();
		void UpdateGlobalVolume();

	public:

		Entity(Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);
		~Entity();

		void setPosition(Vector3 newPosition);
		Vector3 getPosition();

		Vector3 getScale();
		void setScale(Vector3 newScale);

		void setRotationX(float newRotationX);
		void setRotationY(float newRotationY);
		void setRotationZ(float newRotationZ);

		void SetParent(Entity* parent);
		void AddChild(Entity* child);
		void RemoveChild(Entity* node);
		void RemoveChild(int nodeIndex);

		Entity* GetParent();
		list<Entity*> GetChildren();
		Entity* GetChild(int childIndex);

		glm::vec3 GetForward();
		glm::vec3 GetUp();
		glm::vec3 GetRight();

		VolumeAABB* GetGlobalVolume();

		Vector3 getRotation();

		void UpdateTMatrix();
		void UpdateTransform();

		void UpdateChildrenPos();
		void UpdateChildrenRot();
		void UpdateChildrenScale();

		glm::quat EulerToQuat(glm::vec3 euler);
		glm::vec3 QuatToVec(glm::quat quat, glm::vec3 euler);
		glm::quat GetRotationByMatrix(glm::mat4 mat);
		glm::vec3 ToEulerRad(glm::quat rot);
		glm::vec3 NormalizeAngles(glm::vec3 angles);
		float NormalizeAngle(float angle);

		Transform transform;
	};
}