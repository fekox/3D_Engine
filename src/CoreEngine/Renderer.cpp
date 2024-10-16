#include "CoreEngine/Renderer.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) errorLog.GLClearError();\
				x;\
				ASSERT(errorLog.GLLogCall(#x, __FILE__, __LINE__))

namespace renderer
{
	Renderer::Renderer(Window* window, Camera* camera, PointLight* light[], DirectionalLight directionaLight[], SpotLight* spotLight[])
	{
		this->window = window;
		this->camera = camera;

		for (int i = 0; i < 4; i++)
		{
			this->pointLight[i] = light[i];
			this->directionaLight[i] = directionaLight[i];
			this->spotLight[i] = spotLight[i];
		}

		UpdateProjection(camera);
		UpdateView(camera);

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

		ShaderProgramSource source6 = shader.ParseShader("res/Shader/Line.Shader");
		line = shader.createShader(source6.VertexSource, source6.FragmentSource);

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
		for (int i = 0; i < 1; i++)
		{
			string baseText = "dirLight[";
			baseText.append(to_string(i));
			baseText.append("].");

			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "direction").c_str()), directionaLight[i].direction.x, directionaLight[i].direction.y, directionaLight[i].direction.z);
			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "ambient").c_str()), directionaLight[i].ambient.x, directionaLight[i].ambient.y, directionaLight[i].ambient.z);
			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "diffuse").c_str()), directionaLight[i].diffuse.x, directionaLight[i].diffuse.y, directionaLight[i].diffuse.z);
			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "specular").c_str()), directionaLight[i].specular.x, directionaLight[i].specular.y, directionaLight[i].specular.z);
			glUniform1f(glGetUniformLocation(multipleLights, (baseText + "ambientLightStrength").c_str()), directionaLight[i].ambientStrength);
		}

		//Point light
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
		for (int i = 0; i < 4; i++)
		{
			string baseText = "spotLight[";
			baseText.append(to_string(i));
			baseText.append("].");

			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "position").c_str()), spotLight[i]->lightPos.x, spotLight[i]->lightPos.y, spotLight[i]->lightPos.z);
			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "direction").c_str()), spotLight[i]->direction.x, spotLight[i]->direction.y, spotLight[i]->direction.z);
			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "ambient").c_str()), spotLight[i]->ambient.x, spotLight[i]->ambient.y, spotLight[i]->ambient.z);
			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "diffuse").c_str()), spotLight[i]->diffuse.x, spotLight[i]->diffuse.y, spotLight[i]->diffuse.z);
			glUniform3f(glGetUniformLocation(multipleLights, (baseText + "specular").c_str()), spotLight[i]->specular.x, spotLight[i]->specular.y, spotLight[i]->specular.z);
			glUniform1f(glGetUniformLocation(multipleLights, (baseText + "constant").c_str()), spotLight[i]->constant);
			glUniform1f(glGetUniformLocation(multipleLights, (baseText + "linear").c_str()), spotLight[i]->linear);
			glUniform1f(glGetUniformLocation(multipleLights, (baseText + "quadratic").c_str()), spotLight[i]->quadratic);
			glUniform1f(glGetUniformLocation(multipleLights, (baseText + "cutOff").c_str()), spotLight[i]->cutOff);
			glUniform1f(glGetUniformLocation(multipleLights, (baseText + "outerCutOff").c_str()), spotLight[i]->outerCutOff);
		}

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
		for (int i = 0; i < 1; i++)
		{
			string baseText = "dirLight[";
			baseText.append(to_string(i));
			baseText.append("].");

			glUniform3f(glGetUniformLocation(models, (baseText + "direction").c_str()), directionaLight[i].direction.x, directionaLight[i].direction.y, directionaLight[i].direction.z);
			glUniform3f(glGetUniformLocation(models, (baseText + "ambient").c_str()), directionaLight[i].ambient.x, directionaLight[i].ambient.y, directionaLight[i].ambient.z);
			glUniform3f(glGetUniformLocation(models, (baseText + "diffuse").c_str()), directionaLight[i].diffuse.x, directionaLight[i].diffuse.y, directionaLight[i].diffuse.z);
			glUniform3f(glGetUniformLocation(models, (baseText + "specular").c_str()), directionaLight[i].specular.x, directionaLight[i].specular.y, directionaLight[i].specular.z);
			glUniform1f(glGetUniformLocation(models, (baseText + "ambientLightStrength").c_str()), directionaLight[i].ambientStrength);
		}

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
		for (int i = 0; i < 4; i++)
		{
			string baseText = "spotLight[";
			baseText.append(to_string(i));
			baseText.append("].");

			glUniform3f(glGetUniformLocation(models, (baseText + "position").c_str()), spotLight[i]->lightPos.x, spotLight[i]->lightPos.y, spotLight[i]->lightPos.z);
			glUniform3f(glGetUniformLocation(models, (baseText + "direction").c_str()), spotLight[i]->direction.x, spotLight[i]->direction.y, spotLight[i]->direction.z);
			glUniform3f(glGetUniformLocation(models, (baseText + "ambient").c_str()), spotLight[i]->ambient.x, spotLight[i]->ambient.y, spotLight[i]->ambient.z);
			glUniform3f(glGetUniformLocation(models, (baseText + "diffuse").c_str()), spotLight[i]->diffuse.x, spotLight[i]->diffuse.y, spotLight[i]->diffuse.z);
			glUniform3f(glGetUniformLocation(models, (baseText + "specular").c_str()), spotLight[i]->specular.x, spotLight[i]->specular.y, spotLight[i]->specular.z);
			glUniform1f(glGetUniformLocation(models, (baseText + "constant").c_str()), spotLight[i]->constant);
			glUniform1f(glGetUniformLocation(models, (baseText + "linear").c_str()), spotLight[i]->linear);
			glUniform1f(glGetUniformLocation(models, (baseText + "quadratic").c_str()), spotLight[i]->quadratic);
			glUniform1f(glGetUniformLocation(models, (baseText + "cutOff").c_str()), spotLight[i]->cutOff);
			glUniform1f(glGetUniformLocation(models, (baseText + "outerCutOff").c_str()), spotLight[i]->outerCutOff);
		}

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
		glUseProgram(0);
	}

	void Renderer::DrawLinesAABB(glm::mat4x4 model, std::vector<glm::vec3> vertices)
	{
		const GLuint indices[] = {
	   
			0, 1, 1, 2, 2, 3, 3, 0, // Bottom face
			4, 5, 5, 6, 6, 7, 7, 4, // Top face
			0, 4, 1, 5, 2, 6, 3, 7  // Vertical edges
		
		};

		GLuint VAO, VBO, EBO;
		
		glUseProgram(line);
		glUniformMatrix4fv(glGetUniformLocation(line, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(line, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(line, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// Use the shader program

		// Draw the bounding box as lines
		glDrawElements(GL_LINES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		// Cleanup
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteVertexArrays(1, &VAO);
	}

	void Renderer::DrawFrustum(glm::mat4x4 viewProjectionMatrix, Frustum frustum)
	{
		std::vector<glm::vec3> vertices = {
				
			-frustum.nearFace.normal * frustum.nearFace.distance,  // near bottom left
			frustum.nearFace.normal * frustum.nearFace.distance,   // near bottom right
		   frustum.rightFace.normal * frustum.rightFace.distance,  // near top right
		   -frustum.leftFace.normal * frustum.leftFace.distance,   // near top left
		   -frustum.farFace.normal * frustum.farFace.distance,     // far bottom left
	       frustum.farFace.normal * frustum.farFace.distance,      // far bottom right
	       frustum.rightFace.normal * frustum.rightFace.distance + frustum.farFace.normal * frustum.farFace.distance, // far top right
	      -frustum.leftFace.normal * frustum.leftFace.distance + frustum.farFace.normal * frustum.farFace.distance  // far top left
		};

		// Define indices for drawing the frustum as lines
		const GLuint indices[] = {
			0, 1, 1, 2, 2, 3, 3, 0,  // near plane
			4, 5, 5, 6, 6, 7, 7, 4,  // far plane
			0, 4, 1, 5, 2, 6, 3, 7   // connections between near and far planes
		};

		GLuint VAO, VBO, EBO;

		glUseProgram(line);
		glUniformMatrix4fv(glGetUniformLocation(line, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		glUniformMatrix4fv(glGetUniformLocation(line, "view"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		glUniformMatrix4fv(glGetUniformLocation(line, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Draw the frustum as lines
		glDrawElements(GL_LINES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		// Cleanup
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &EBO);
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