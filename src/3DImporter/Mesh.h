#pragma once

#include "..\libs\glm\include\glm.hpp"
#include <string>
#include <vector>
#include "Sprite/Importer2D.h"


using namespace std;

#define MAX_BONE_INFLUENCE 4
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:

	vector<Vertex> vertices;
	vector<Texture> textures;
	vector<unsigned int> indices;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	unsigned int VAO, VBO, EBO;

	void SetNewTextures(string currentDirectory, string fileName, bool shouldInvertUVs, string type);

private:

	void SetupMesh();
};
