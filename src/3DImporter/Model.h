#pragma once
#include "Entity/Entity3D.h"
#include "3DImporter/Mesh.h"
#include "3DImporter/ModelImporter.h"

using namespace entity3D;

struct AABB;

class EXPORT Model : public Entity3D
{
public:

	vector<Mesh> meshes;

	string directory;

	unique_ptr<AABB> boundingVolume;

	Model(Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation, const char* path, bool invertTextures, Transform* parent = nullptr, bool turnOffByBSP = false);
	~Model() override;

	vector<Mesh> GetMeshes();

	static AABB GenerateAABB(const Model& model);

	AABB GetGlobalAABB();

	bool IsOnFrustum(Frustum* frustum);

	void Draw() override;
	bool DrawWithFrustum(Frustum* frustum, bool shouldBeDrawn);
};
