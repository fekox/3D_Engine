#include "Tools/Vectors/Vectors.h"
#include "Entity/Entity.h"
#include "Material/Material.h"
#pragma once

using namespace vectors;
using namespace entity;
using namespace material;

namespace entity3D
{
	class EXPORT Entity3D : public Entity
	{
		protected: 

			Vector4 color;
			unsigned int VAO = 0; //Vertex Array Object.
			unsigned int lightCubeVAO = 0;

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
			
			Entity3D(Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation);
			void DrawShape3D(Material* material);
			void SetColor(Vector4 rgba);
			Vector4 GetColor();
			~Entity3D();
	};
}