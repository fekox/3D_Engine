#include "Tools/Vectors/Vectors.h"
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
			unsigned int VAO = 0; //Vertex Array Object.

			unsigned int VBO = 0; //Vertex Buffer Object.
			int vertexSize;
			int atributeVertexSize = 3;
			int atributePosSize = 3;
			int aColorSize = 4;
			float* vertexPositions = 0;

			unsigned int EBO = 0; //Element Buffer Object.
			int indexSize = 0;
			int* indexs = 0;

			unsigned int textureId; //texture
			int uvSize;
			int aUvSize = 2;
			float* uvPos;

		public:
			
			Entity3D(Vector4 rgba, Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);
			void DrawShape3D();
			void SetColor(Vector4 rgba);
			Vector4 GetColor();
			~Entity3D();
	};
}