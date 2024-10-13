#include "Model.h"

Model::Model(renderer::Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation, const char* path, bool invertTextures, Transform* parent) : Entity3D(render, newPosition, newScale, newRotation, parent)
{
	ModelImporter::LoadModel(path, directory, meshes, invertTextures);
}

Model::~Model()
{

}

vector<Mesh> Model::GetMeshes()
{
	return meshes;
}

AABB Model::GenerateAABB(const Model& model)
{
	glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
	glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

	for (const Mesh& mesh : model.meshes)
	{
		for (const Vertex& vertex : mesh.vertices)
		{
			minAABB.x = std::min(minAABB.x, vertex.Position.x);
			minAABB.y = std::min(minAABB.y, vertex.Position.y);
			minAABB.z = std::min(minAABB.z, vertex.Position.z);

			maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
			maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
			maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
		}
	}

	return AABB(minAABB, maxAABB);
}

void Model::Draw()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		render->DrawModel(meshes[i].VAO, meshes[i].indices, meshes[i].textures, transform->m_modelMatrix);
	}
}
