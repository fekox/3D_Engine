#include "CoreEngine/Renderer.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) errorLog.GLClearError();\
				x;\
				ASSERT(errorLog.GLLogCall(#x, __FILE__, __LINE__))

namespace renderer
{
	Renderer::Renderer(Window* window, Camera* camera)
	{
		this->window = window;
		this->camera = camera;

		UpdateProjection(camera);
		UpdateView(camera);

		ShaderProgramSource source1 = shader.ParseShader("res/Shader/Primitive.Shader");
		primitiveShader = shader.createShader(source1.VertexSource, source1.FragmentSource);

		ShaderProgramSource source2 = shader.ParseShader("res/Shader/Texture.Shader");
		textureShader = shader.createShader(source2.VertexSource, source2.FragmentSource);

		ShaderProgramSource source3 = shader.ParseShader("res/Shader/Light.Shader");
		lightShader = shader.createShader(source3.VertexSource, source3.FragmentSource);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::UpdateView(Camera* camera)
	{
		view = camera->UpdateCameraViewMode();
	}

	void Renderer::UpdateProjection(Camera* camera)
	{
		projection = camera->GetProjection(this->window);
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::StartDraw()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::EndDraw()
	{
		GLCall(glfwSwapBuffers(window->getWindow()));
		GLCall(glfwPollEvents());
	}

	void Renderer::Draw2DEntity(unsigned int VAO, int sizeIndex, Vector4 color, glm::mat4x4 model)
	{
		glUseProgram(primitiveShader);

		unsigned int transformLoc = glGetUniformLocation(primitiveShader, "u_MVP");
		mat4 MVP = projection * view * model;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(MVP));

		glBindVertexArray(VAO);
		glUniform4f(glGetUniformLocation(primitiveShader, "u_Color"), color.x, color.y, color.z, color.w);
		glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, nullptr);
		glUseProgram(0);
	}

	void Renderer::DrawTexture(unsigned int VAO, int sizeIndex, Vector4 color, glm::mat4x4 model, unsigned int& idTexture)
	{
		glUseProgram(textureShader);

		unsigned int transformLoc = glGetUniformLocation(textureShader, "MVP");
		mat4 MVP = projection * view * model;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(MVP));

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, idTexture);
		glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, 0);

		glUseProgram(0);
	}

	void Renderer::DrawEntity3D(unsigned int VAO, int sizeIndex, Vector4 color, glm::mat4x4 model)
	{
		glUseProgram(primitiveShader);
		unsigned int transformLoc = glGetUniformLocation(primitiveShader, "u_MVP");

		glm::mat4 MVP = projection * view * model;
		glUniformMatrix4fv(transformLoc, primitiveShader, GL_FALSE, glm::value_ptr(MVP));

		glBindVertexArray(VAO);
		glUniform4f(glGetUniformLocation(primitiveShader, "u_Color"), color.x, color.y, color.z, color.w);
		glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, nullptr);
		glUseProgram(0);

		//glUseProgram(lightShader);
		//glUniformMatrix4fv(glGetUniformLocation(lightShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(glGetUniformLocation(lightShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(glGetUniformLocation(lightShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


		//glUniform3f(glGetUniformLocation(lightShader, "lightPos"), 100, 10, 10);
		//glUniform3f(glGetUniformLocation(lightShader, "viewPos"), camera->cameraPos.x, camera->cameraPos.y, camera->cameraPos.z);
		//glUniform3f(glGetUniformLocation(lightShader, "lightColor"), 1, 1, 1);
		//glUniform3f(glGetUniformLocation(lightShader, "objectColor"), color.x, color.y, color.z);

		//glUseProgram(0);
	}

	void Renderer::CreateVBuffer(float* positions, int* indexs, int positionsSize, int indexSize, int atributeVertexSize, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexSize, indexs, GL_STATIC_DRAW);

		glVertexAttribPointer(0, atributeVertexSize, GL_FLOAT, GL_FALSE, sizeof(float) * atributeVertexSize, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	void Renderer::CreateVBuffer(float* positions, int* indexs, int positionsSize, int indexSize, int atributeVertexSize, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, int aColorSize, int aUVSize)
	{
		deleteVertexAndBuffer(VAO, VBO, EBO);
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexSize, indexs, GL_STATIC_DRAW);

		glVertexAttribPointer(0, atributeVertexSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, aColorSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, aUVSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	void Renderer::BindTexture(const char* textureName, unsigned& textureID)
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(1);

		int width, height, m_BPP;
		unsigned char* localBuffer = textureImporter.GetTexture(textureName, width, height, m_BPP);

		if (m_BPP == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		else if (m_BPP == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
		else if (m_BPP == 2)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
		else if (m_BPP == 1)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);

		if (!localBuffer)
		{
			cout << "Failed to load texture" << endl;

		}

		glGenerateMipmap(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		stbi_image_free(localBuffer);
	}

	void Renderer::deleteVertexAndBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
}