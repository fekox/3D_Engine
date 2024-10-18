#include "Model.h"

Model::Model(renderer::Renderer* render, glm::vec3 newPosition, glm::vec3 newScale, glm::vec3 newRotation, const char* path, bool invertTextures, Transform* parent, bool turnOffByBSP) : Entity3D(render, newPosition, newScale, newRotation, parent, turnOffByBSP)
{
	ModelImporter::LoadModel(path, directory, meshes, invertTextures, turnOffByBSP);
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

void Model::SetMinMaxBoundingVolume(glm::vec3& minAABB, glm::vec3& maxAABB, const glm::mat4& transformMatrix)
{
	for (const Mesh& mesh : meshes)
	{
		for (const Vertex& vertex : mesh.vertices)
		{
			glm::vec3 worldPosition = glm::vec3(transformMatrix * glm::vec4(vertex.Position, 1.0f));

			minAABB.x = std::min(minAABB.x, worldPosition.x);
			minAABB.y = std::min(minAABB.y, worldPosition.y);
			minAABB.z = std::min(minAABB.z, worldPosition.z);

			maxAABB.x = std::max(maxAABB.x, worldPosition.x);
			maxAABB.y = std::max(maxAABB.y, worldPosition.y);
			maxAABB.z = std::max(maxAABB.z, worldPosition.z);
		}
	}
}

void Model::RecursiveAABB(glm::vec3& minAABB, glm::vec3& maxAABB, const glm::mat4& parentTransformMatrix)
{
	glm::vec3 localMin = minAABB;
	glm::vec3 localMax = maxAABB;

	for (auto child : transform->children)
	{
		Model* entity = dynamic_cast<Model*>(child->entity);
		if (entity)
		{
			glm::mat4 childTransformMatrix = parentTransformMatrix * child->GetModelMatrix();

			// Calculate local min and max for the current entity
			glm::vec3 childMin = localMin;
			glm::vec3 childMax = localMax;
			entity->RecursiveAABB(childMin, childMax, childTransformMatrix);
			entity->SetMinMaxBoundingVolume(childMin, childMax, childTransformMatrix);

			*entity->boundingVolume = AABB(childMin, childMax);
			minAABB = glm::min(minAABB, childMin);
			maxAABB = glm::max(maxAABB, childMax);
		}
	}
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

	if (!transform->children.empty())
	{
		for (auto child : transform->children)
		{
			if (child->entity != nullptr)
			{
				if (child->entity)
				{
					child->entity->Draw();
				}
			}
		}
	}
}

bool Model::DrawWithFrustum(Frustum* frustum, bool shouldBeDrawn)
{
	transform->ForceUpdateSelfAndChild();

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

bool Model::DrawWithBSP(std::vector<Plane>& bspPlanes, std::vector<bool>& cameraPlanes, Frustum* frustum, bool shouldBeDrawn)
{
	transform->ForceUpdateSelfAndChild();

	for (int i = 0; i < bspPlanes.size(); ++i)
	{
		if (bspPlanes[i].GetSide(transform->GetGlobalPosition()) != cameraPlanes[i])
		{
			return false;
		}
	}
	bool isDrawn = false;
	for (auto child : transform->children)
	{
		if (child->entity != nullptr && dynamic_cast<Model*>(child->entity))
		{
			bool isChildDrawn = dynamic_cast<Model*>(child->entity)->DrawWithBSP(
				bspPlanes, cameraPlanes, frustum, shouldBeDrawn);
			if (isChildDrawn)
			{
				isDrawn = true;
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
	return isDrawn;

}
