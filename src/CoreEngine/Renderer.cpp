#include "CoreEngine/Renderer.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) errorLog.GLClearError();\
				x;\
				ASSERT(errorLog.GLLogCall(#x, __FILE__, __LINE__))

namespace renderer
{
	Renderer::Renderer(Window* window, Camera* camera, PointLight* light[])
	{
		this->window = window;
		this->camera = camera;

		for (int i = 0; i < 4; i++)
		{
			this->pointLight[i] = light[i];
		}

		UpdateProjection(camera);
		UpdateView(camera);

		spotLight = new SpotLight(camera);

		ShaderProgramSource source1 = shader.ParseShader("res/Shader/Primitive.Shader");
		primitiveShader = shader.createShader(source1.VertexSource, source1.FragmentSource);

		ShaderProgramSource source2 = shader.ParseShader("res/Shader/Texture.Shader");
		textureShader = shader.createShader(source2.VertexSource, source2.FragmentSource);

		ShaderProgramSource source3 = shader.ParseShader("res/Shader/Light.Shader");
		lightShader = shader.createShader(source3.VertexSource, source3.FragmentSource);

		ShaderProgramSource source4 = shader.ParseShader("res/Shader/MultipleLights.Shader");
		multipleLights = shader.createShader(source4.VertexSource, source4.FragmentSource);

		ShaderProgramSource source5 = shader.ParseShader("res/Shader/Models.Shader");
		models = shader.createShader(source5.VertexSource, source5.FragmentSource);

		glEnable(GL_DEPTH_TEST);

		glDepthFunc(GL_LESS);
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		glEnable(GL_SAMPLE_ALPHA_TO_ONE);
		glFrontFace(GL_CCW);

		glEnable(GL_BLEND); //Transparency
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);
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

	void Renderer::DrawEntity3D(unsigned int VAO, unsigned int lightCubeVAO, int sizeIndex, Vector4 color, glm::mat4x4 model, Material* material)
	{
		glUseProgram(multipleLights);
		glUniformMatrix4fv(glGetUniformLocation(multipleLights, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(multipleLights, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(multipleLights, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glUniform3f(glGetUniformLocation(multipleLights, "viewPos"), camera->cameraPos.x, camera->cameraPos.y, camera->cameraPos.z);

		// material properties
		glUniform3f(glGetUniformLocation(multipleLights, "material.ambient"), material->ambient.x, material->ambient.y, material->ambient.z);
		glUniform3f(glGetUniformLocation(multipleLights, "material.diffuse"), material->diffuse.x, material->diffuse.y, material->diffuse.z);
		glUniform3f(glGetUniformLocation(multipleLights, "material.specular"), material->specular.x, material->specular.y, material->specular.z);
		glUniform1f(glGetUniformLocation(multipleLights, "material.shininess"), material->shininess);

		// Directional light
		glUniform3f(glGetUniformLocation(multipleLights, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(multipleLights, "dirLight.ambient"), 0.3f, 0.24f, 0.14f);
		glUniform3f(glGetUniformLocation(multipleLights, "dirLight.diffuse"), 0.7f, 0.42f, 0.26f);
		glUniform3f(glGetUniformLocation(multipleLights, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

		for (int i = 0; i < 4; i++)
		{
			string baseText = "pointLights[";
			baseText.append(to_string(i));
			baseText.append("].");

			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "position").c_str()), pointLight[i]->lightPos.x, pointLight[i]->lightPos.y, pointLight[i]->lightPos.z);
			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "ambient").c_str()), pointLight[i]->ambient.x * 0.1, pointLight[i]->ambient.y * 0.1, pointLight[i]->ambient.z * 0.1);
			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "diffuse").c_str()), pointLight[i]->diffuse.x, pointLight[i]->diffuse.y, pointLight[i]->diffuse.z);
			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "specular").c_str()), pointLight[i]->specular.x, pointLight[i]->specular.y, pointLight[i]->specular.z);
			glUniform1f(glGetUniformLocation(multipleLights, (baseText + "constant").c_str()), pointLight[i]->constant);
			glUniform1f(glGetUniformLocation(multipleLights, (baseText + "linear").c_str()), pointLight[i]->linear);
			glUniform1f(glGetUniformLocation(multipleLights, (baseText + "quadratic").c_str()), 0.032);
		}

		// SpotLight
		glUniform3f(glGetUniformLocation(multipleLights, "spotLight.position"), camera->cameraPos.x, camera->cameraPos.y, camera->cameraPos.z);
		glUniform3f(glGetUniformLocation(multipleLights, "spotLight.direction"), camera->cameraFront.x, camera->cameraFront.y, camera->cameraFront.z);
		glUniform3f(glGetUniformLocation(multipleLights, "spotLight.ambient"), spotLight->ambient.x, spotLight->ambient.y, spotLight->ambient.z);
		glUniform3f(glGetUniformLocation(multipleLights, "spotLight.diffuse"), spotLight->diffuse.x, spotLight->diffuse.y, spotLight->diffuse.z);
		glUniform3f(glGetUniformLocation(multipleLights, "spotLight.specular"), spotLight->specular.x, spotLight->specular.y, spotLight->specular.z);
		glUniform1f(glGetUniformLocation(multipleLights, "spotLight.constant"), spotLight->constant);
		glUniform1f(glGetUniformLocation(multipleLights, "spotLight.linear"), spotLight->linear);
		glUniform1f(glGetUniformLocation(multipleLights, "spotLight.quadratic"), spotLight->quadratic);
		glUniform1f(glGetUniformLocation(multipleLights, "spotLight.cutOff"), spotLight->cutOff);
		glUniform1f(glGetUniformLocation(multipleLights, "spotLight.outerCutOff"), spotLight->outerCutOff);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, 0);

		glUseProgram(0);
	}

	void Renderer::DrawModel(unsigned int VAO, vector<unsigned int> index, vector<Texture> textures, glm::mat4x4 model)
	{
		glUseProgram(models);
		glUniformMatrix4fv(glGetUniformLocation(models, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(models, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(models, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glUniform3f(glGetUniformLocation(models, "viewPos"), camera->cameraPos.x, camera->cameraPos.y, camera->cameraPos.z);

		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalsNr = 1;
		unsigned int heightNr = 1;
		unsigned int colorNr = 1;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			string number;
			string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normals")
				number = std::to_string(normalsNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);
			else if (name == "texture_baseColor")
				number = std::to_string(colorNr++);

			glUniform1f(glGetUniformLocation(models, ("material." + name + number).c_str()), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		glUniform1f(glGetUniformLocation(models, "material.shininess"), 1.0f);

		// Directional light
		glUniform3f(glGetUniformLocation(models, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(models, "dirLight.ambient"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(models, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(models, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(models, "ambientLightStrength"), 1.0f);

		// Point lights
		for (int i = 0; i < 4; i++)
		{
			string baseText = "pointLights[";
			baseText.append(to_string(i));
			baseText.append("].");

			glUniform3f(glGetUniformLocation(models, (baseText + "position").c_str()), pointLight[i]->lightPos.x, pointLight[i]->lightPos.y, pointLight[i]->lightPos.z);
			glUniform3f(glGetUniformLocation(models, (baseText + "ambient").c_str()), pointLight[i]->ambient.x * 0.1, pointLight[i]->ambient.y * 0.1, pointLight[i]->ambient.z * 0.1);
			glUniform3f(glGetUniformLocation(models, (baseText + "diffuse").c_str()), pointLight[i]->diffuse.x, pointLight[i]->diffuse.y, pointLight[i]->diffuse.z);
			glUniform3f(glGetUniformLocation(models, (baseText + "specular").c_str()), pointLight[i]->specular.x, pointLight[i]->specular.y, pointLight[i]->specular.z);
			glUniform1f(glGetUniformLocation(models, (baseText + "constant").c_str()), pointLight[i]->constant);
			glUniform1f(glGetUniformLocation(models, (baseText + "linear").c_str()), pointLight[i]->linear);
			glUniform1f(glGetUniformLocation(models, (baseText + "quadratic").c_str()), 0.032);
		}

		// SpotLight
		glUniform3f(glGetUniformLocation(models, "spotLight.position"), camera->cameraPos.x, camera->cameraPos.y, camera->cameraPos.z);
		glUniform3f(glGetUniformLocation(models, "spotLight.direction"), camera->cameraFront.x, camera->cameraFront.y, camera->cameraFront.z);
		glUniform3f(glGetUniformLocation(models, "spotLight.ambient"), spotLight->ambient.x, spotLight->ambient.y, spotLight->ambient.z);
		glUniform3f(glGetUniformLocation(models, "spotLight.diffuse"), spotLight->diffuse.x, spotLight->diffuse.y, spotLight->diffuse.z);
		glUniform3f(glGetUniformLocation(models, "spotLight.specular"), spotLight->specular.x, spotLight->specular.y, spotLight->specular.z);
		glUniform1f(glGetUniformLocation(models, "spotLight.constant"), spotLight->constant);
		glUniform1f(glGetUniformLocation(models, "spotLight.linear"), spotLight->linear);
		glUniform1f(glGetUniformLocation(models, "spotLight.quadratic"), spotLight->quadratic);
		glUniform1f(glGetUniformLocation(models, "spotLight.cutOff"), spotLight->cutOff);
		glUniform1f(glGetUniformLocation(models, "spotLight.outerCutOff"), spotLight->outerCutOff);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
		glUseProgram(0);
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

	void Renderer::CreateVBufferNormals(float* positions, int* index, int positionsSize, int atributeNormalSize,
		int atribVertexSize, int indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO, unsigned& lightCubeVAO)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indicesSize, index, GL_STATIC_DRAW);

		glVertexAttribPointer(0, atribVertexSize, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, atributeNormalSize, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glGenVertexArrays(1, &lightCubeVAO);
		glBindVertexArray(lightCubeVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indicesSize, index, GL_STATIC_DRAW);

		glVertexAttribPointer(0, atribVertexSize, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
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

	void Renderer::deleteVertexAndBuffer(unsigned int& lightCubeVAO)
	{
		glDeleteVertexArrays(1, &lightCubeVAO);
	}
}