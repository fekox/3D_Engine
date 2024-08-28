#pragma once
#include "Tools/Vectors/Vectors.h"
#include "Entity/Entity.h"

using namespace vectors;
using namespace entity;

namespace Entity2D
{
	class EXPORT Entity2D : public Entity
	{
	protected:
		Vector4 color;
		unsigned int VAO = 0; //Vertex Array Object.

		unsigned int VBO = 0; //Vertex Buffer Object.
		int vertexSize;
		int atributeVertexSize = 3;
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
		Entity2D(Vector4 rgba, Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation);
		~Entity2D();
		
		void DrawShape();
		void DrawTexture(unsigned int& idTexture);

		void setColor(Vector4 rgba);
		Vector4 getColor();
	};
}

