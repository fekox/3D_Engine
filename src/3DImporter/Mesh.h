#pragma once

#include "..\libs\glm\include\glm.hpp"
#include <string>
#include <vector>


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

private:

	void SetupMesh();
};
