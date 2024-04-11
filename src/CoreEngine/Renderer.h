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

#pragma once

using namespace window;
using namespace shader;
using namespace camera;
using namespace errorLog;
using namespace vectors;
using namespace glm;
using namespace textureImporter;

namespace renderer
{
	/// <summary>
	/// Class Renderer
	/// </summary>
	class Renderer
	{
	private:

		ErrorLog errorLog;
		Window* window;
		Shader shader;
		Camera* camera;
		TextureImporter textureImporter;
		unsigned int primitiveShader;
		unsigned int textureShader;
		unsigned int lightShader;
		glm::mat4x4 projection;
		glm::mat4x4 view;

	public:

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

		void DrawEntity3D(unsigned int VAO, int sizeIndex, Vector4 color, glm::mat4x4 model);

		void CreateVBuffer(float* positions, int* indexs, int positionsSize, int indexSize, int atributeVertexSize,
			unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

		void CreateVBufferNormals(float* positions, int* index, int positionsSize, int atributeNormalSize,
			int atribVertexSize, int indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO);

		void UpdateProjection(Camera* camera);
		void UpdateView(Camera* camera);

		void CreateVBuffer(float* positions, int* indexs, int positionsSize, int indexSize, int atributeVertexSize,
			unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, int aColorSize, int aUVSize);



		void BindTexture(const char* textureName, unsigned& textureID);
		void deleteVertexAndBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	};
}