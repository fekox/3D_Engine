#include "Shader.h"
#include "Camera/Camera.h"
#include "CoreEngine/Window.h"
#include "Tools/Vectors/Vectors.h"
#include "Tools/Error Log/ErrorLog.h"
#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"
#include "Tools/Texture Importer/TextureImporter.h"
#include "Lights/Light.h"
#include "Material/Material.h"
#include "Lights/DirectionalLight.h"
#include <Lights/PointLight.h>
#include <Lights/SpotLight.h>
#include "3DImporter/Mesh.h"

#pragma once

using namespace window;
using namespace shader;
using namespace camera;
using namespace errorLog;
using namespace vectors;
using namespace glm;
using namespace textureImporter;
using namespace light;
using namespace material;
using namespace directionalLight;
using namespace pointLight;
using namespace spotLight;

namespace renderer
{
	/// <summary>
	/// Class Renderer
	/// </summary>
	class EXPORT Renderer
	{
		private:

		ErrorLog errorLog;
		Window* window;
		Shader shader;
		Camera* camera;
		TextureImporter textureImporter;

		DirectionalLight directionaLight[4];
		SpotLight* spotLight[4];
		PointLight* pointLight[4];

		public:

		glm::mat4x4 projection;
		glm::mat4x4 view;

		unsigned int primitiveShader;
		unsigned int textureShader;
		unsigned int lightShader;
		unsigned int lightCubeShader;
		unsigned int multipleLights;
		unsigned int models;
		unsigned int line;

		Renderer(Window* window, Camera* camera, PointLight* light[], DirectionalLight directionaLight[], SpotLight* spotLight[]);
		Renderer(Window* window, Camera* camera);
		~Renderer();
		/// <summary>
		/// Clear screen
		/// </summary>
		void StartDraw();
		/// <summary>
		/// Swap the front and back buffer of the specified window.
		/// </summary>
		/// <param name="window">Screen reference</param>
		void EndDraw();
		/// <summary>
		/// Processes all pending events.
		/// </summary>
		void Draw2DEntity(unsigned int VAO, int sizeIndex, Vector4 color, glm::mat4x4 model);

		void DrawTexture(unsigned int VAO, int sizeIndex, Vector4 color, glm::mat4x4 model, unsigned int& idTexture);

		void DrawEntity3D(unsigned int VAO, unsigned int lightCubeVAO, int sizeIndex, Vector4 color, glm::mat4x4 model, Material* material);

		void DrawModel(unsigned int VAO, vector<unsigned int> index, vector<Texture> textures, glm::mat4x4 model);

		void DrawLinesAABB(glm::mat4x4 model, std::vector<glm::vec3> vertices);

		void DrawPlane(Plane* plane);


		void CreateVBuffer(float* positions, int* indexs, int positionsSize, int indexSize, int atributeVertexSize,
			unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

		void CreateVBufferNormals(float* positions, int* index, int positionsSize, int atributeNormalSize,
			int atribVertexSize, int indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO, unsigned& lightCubeVAO);

		void UpdateProjection(Camera* camera);
		void UpdateView(Camera* camera);

		void CreateVBuffer(float* positions, int* indexs, int positionsSize, int indexSize, int atributeVertexSize,
			unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, int aColorSize, int aUVSize);



		void BindTexture(const char* textureName, unsigned& textureID);
		void deleteVertexAndBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void deleteVertexAndBuffer(unsigned int& lightCubeVAO);

	};
}