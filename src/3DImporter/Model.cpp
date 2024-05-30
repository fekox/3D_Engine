#include "Model.h"

Model::Model(renderer::Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation, const char* path) : Entity3D(render, newPosition, newScale, newRotation)
{
	ModelImporter::LoadModel(path, directory, meshes);
}

Model::~Model()
{

}

void Model::Draw()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		render->DrawModel(meshes[i].VAO, meshes[i].indices, meshes[i].textures, model);
	}
}
