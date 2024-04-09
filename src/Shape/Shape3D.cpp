#include "Shape/Shape3D.h"

namespace shape3D
{
	Shape3D::Shape3D(Shapes3D typeShapes, Vector4 rgba, Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation) : Entity3D(rgba, render, newPosition, newScale, newRotation)
	{
		switch (typeShapes)
		{
			case shape3D::Shape3D::Cube:
			CreateCube();
			break;

			case shape3D::Shape3D::Pyramid:
			CreatePyramid();
			break;

			default:
			break;
		}
	}

	Shape3D::~Shape3D()
	{
		
	}

	void Shape3D::CreateCube()
	{
		vertexSize = 24;

		vertexPositions = new float[vertexSize] 
		{
			0.5f, 0.5f, 0.5f, // top right
			0.5f, -0.5f, 0.5f, // bottom right
			-0.5f, -0.5f, 0.5f, // bottom left
			-0.5f, 0.5f, 0.5f, // top Left
			0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f
		};

		indexSize = 36;

		indexs = new int[indexSize]
		{
			0, 1, 3,
			1, 2, 3,
			4, 5, 7,
			5, 6, 7,
			0, 3, 4,
			3, 4, 7,
			1, 2, 5,
			2, 6, 5,
			1, 0, 5,
			0, 4, 5,
			3, 2, 6,
			3, 7, 6
		};

		atributeVertexSize = 3;
		render->CreateVBuffer(vertexPositions, indexs, vertexSize, indexSize, atributeVertexSize, VAO, VBO, EBO);
	}

	void Shape3D::CreatePyramid()
	{
		vertexSize = 15;
		
		vertexPositions = new float[vertexSize] 
		{
			0.5f, -0.5f, 0.5f, // bottom right
			-0.5f, -0.5f, 0.5f, // bottom left
			0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			0.0f, 0.5f, 0.0f
		};
		
		indexSize = 18;

		indexs = new int[indexSize] 
		{
			0, 1, 3,
				1, 2, 3,
				4, 0, 1,
				4, 0, 2,
				4, 2, 3,
				4, 3, 1
		};
		
		atributeVertexSize = 3;
		render->CreateVBuffer(vertexPositions, indexs, vertexSize, indexSize, atributeVertexSize, VAO, VBO, EBO);
	}

	void Shape3D::Draw()
	{
		DrawShape3D();
	}
}