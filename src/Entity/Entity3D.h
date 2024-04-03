#include "Tools/Vectors.h"
#include "Entity/Entity.h"
#pragma once

using namespace vectors;
using namespace Entity;

namespace entity3D
{
	class EXPORT Entity3D : public Entity
	{
		protected: 

			Vector4 color;

		public:
			
			Entity3D(Vector4 rgba, Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);
			void DrawEntity3D();
			void SetColor(Vector4 rgba);
			Vector4 GetColor();
			~Entity3D();
	};
}