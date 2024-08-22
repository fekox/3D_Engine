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

	Model(Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation, const char* path, bool invertTextures);
	~Model();

	vector<Mesh> GetMeshes();

	void Draw();
};
