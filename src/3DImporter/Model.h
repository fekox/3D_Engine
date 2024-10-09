#pragma once
#include "Entity/Entity3D.h"
#include "3DImporter/Mesh.h"
#include "3DImporter/ModelImporter.h"

using namespace entity3D;

class EXPORT Model : public Entity3D
{
public:

	vector<Mesh> meshes;

	string directory;

	Model(Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation, const char* path, bool invertTextures, Transform* parent = nullptr);
	~Model();

	vector<Mesh> GetMeshes();

	AABB GenerateAABB(const Model& model);

	void Draw();
};
