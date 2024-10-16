#include "Model.h"

Model::Model(renderer::Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation, const char* path, bool invertTextures, Transform* parent) : Entity3D(render, newPosition, newScale, newRotation, parent)
{
	ModelImporter::LoadModel(path, directory, meshes, invertTextures);
	boundingVolume = make_unique<AABB>(GenerateAABB(*this));
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

AABB Model::GetGlobalAABB()
{
	//Get global scale thanks to our transform
	const glm::vec3 globalCenter{ this->transform->GetModelMatrix() * glm::vec4(boundingVolume->center, 1.f)};

	// Scaled orientation
	glm::vec3 right = transform->GetRight() * boundingVolume->extents.x;
	glm::vec3 up = transform->GetUp() * boundingVolume->extents.y;
	glm::vec3 forward = transform->GetForward() * boundingVolume->extents.z;

	const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

	const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

	const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

	return AABB(globalCenter, newIi, newIj, newIk);
}

bool Model::IsOnFrustum(Frustum* frustum)
{
	return boundingVolume->IsOnOrForwardPlane(frustum->leftFace) &&
		boundingVolume->IsOnOrForwardPlane(frustum->rightFace) &&
		boundingVolume->IsOnOrForwardPlane(frustum->topFace) &&
		boundingVolume->IsOnOrForwardPlane(frustum->bottomFace) &&
		boundingVolume->IsOnOrForwardPlane(frustum->nearFace) &&
		boundingVolume->IsOnOrForwardPlane(frustum->farFace);
}

void Model::Draw()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		render->DrawModel(meshes[i].VAO, meshes[i].indices, meshes[i].textures, transform->m_modelMatrix);
	}
}

bool Model::DrawWithFrustum(Frustum* frustum, bool shouldBeDrawn)
{
	for (auto child : transform->children)
	{
		if (child->entity != nullptr && dynamic_cast<Model*>(child->entity))
		{
			bool isObjectBehindDraw = dynamic_cast<Model*>(child->entity)->DrawWithFrustum(frustum, shouldBeDrawn);
			if (isObjectBehindDraw)
			{
				shouldBeDrawn = true;
			}
		}
	}

	std::vector<glm::vec3> vertices = boundingVolume->GetVertice();

	render->DrawLinesAABB(transform->m_modelMatrix, vertices);

	if (IsOnFrustum(frustum) || shouldBeDrawn)
	{
		Draw();
		return true;
	}

	return shouldBeDrawn;
}
