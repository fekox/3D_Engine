#pragma once

#include <assimp/scene.h>

#include <string>
#include <fstream>
#include <sstream>
#include "3DImporter/Mesh.h"

class Model;

static class ModelImporter
{
	private:

	static string currentDirectory;
	static vector<Texture> textures_loaded;

	static string directory;

	public:

	static void LoadModel(const string& path, string& directory, vector<Mesh>& meshes, Model* model, bool invertTextures, bool turnOffByBSP = false);
	static void ProcessNode(vector<Mesh>& meshes, aiNode* node, const aiScene* scene, Model* model, bool invertTextures, bool turnOffByBSP = false);

	static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, bool invertTextures);

	static vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
	string typeName, bool invertTextures);

	static unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
};