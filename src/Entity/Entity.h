#pragma once
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include "Tools/Vectors/Vectors.h"
#include "CoreEngine/Renderer.h"

#include "Transform/Transform.h"
#include "BoundingVolume/AABB.h"

#include <list> 
#include <memory>

using namespace vectors;
using namespace renderer;

namespace entity
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

	public:

		Entity* parent;
		list<Entity> children;

		Transform transform;

		AABB boundingVolume;

		Entity(Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);
		~Entity();

		void setPosition(Vector3 newPosition);
		Vector3 getPosition();

		Vector3 getScale();
		void setScale(Vector3 newScale);

		void setRotationX(float newRotationX);
		void setRotationY(float newRotationY);
		void setRotationZ(float newRotationZ);

		Vector3 getRotation();

		void UpdateTMatrix();

		AABB GetGlobalAABB();

		void AddChild(Entity newChild);

		void UpdateSelfAndChild();

		void ForceUpdateSelfAndChild();
	};
}