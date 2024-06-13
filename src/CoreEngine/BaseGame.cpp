#include <iostream>
#include "CoreEngine/BaseGame.h"

using namespace std;

namespace baseEngine
{
	Camera* newCamera;

	BaseGame::BaseGame(int width, int height, const char* windowName)
	{
		errorLog.CheckGlfwInit();

		window = new Window(width, height, windowName, NULL, NULL);

		errorLog.CheckGlewInit();

		camera = new Camera();
		newCamera = camera;

		renderer = new Renderer(window, camera);

		for (int i = 0; i < 4; i++)
		{
			directionalLight[i] = renderer->GetDirectionalLight(i);

			pointLight[i] = PointLight();
			pointLight[i] = renderer->GetPointLight(i);

			spotLight[i] = new SpotLight(camera);
			*spotLight[i] = renderer->GetSpotLight(i);
		}

		inputSystem = new InputSystem(window->getWindow());

		//Disable the cursor
		glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(window->getWindow(), Mouse_Callback);
		glfwSetScrollCallback(window->getWindow(), Scroll_Callback);
	}

	BaseGame::~BaseGame()
	{
		delete window;
		delete renderer;
		delete camera;
	}

	void BaseGame::gameLoop()
	{
		while (!glfwWindowShouldClose(window->getWindow()))
		{
			Time::Update(glfwGetTime());
			
			renderer->StartDraw();
			
			camera->CameraMovement(window->getWindow());
			
			renderer->UpdateProjection(camera);
			renderer->UpdateView(camera);
			
			update();
			
			renderer->EndDraw();
		}
	}

	Renderer* BaseGame::GetRenderer()
	{
		return renderer;
	}

	void Mouse_Callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		float xPos = static_cast<float>(xposIn);
		float yPos = static_cast<float>(yposIn);

		if (newCamera->firstMouse)
		{
			newCamera->lastX = xPos;
			newCamera->lastY = yPos;
			newCamera->firstMouse = false;
		}

		float xOffset = xPos - newCamera->lastX;
		float yOffset = newCamera->lastY - yPos;

		newCamera->lastX = xPos;
		newCamera->lastY = yPos;
		newCamera->CheckMouseMovement(xOffset, yOffset);
	}

	void Scroll_Callback(GLFWwindow* window, double xpos, double ypos)
	{
		newCamera->CheckMouseScroll(static_cast<float>(ypos));
	}

	void BaseGame::SetDirectionaLight(int lightID, vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular)
	{
		for (int i = 0; i < 4; i++)
		{
			if (lightID == i)
			{
				directionalLight[i].direction = direction;
				directionalLight[i].ambient = ambient;
				directionalLight[i].diffuse = diffuse;
				directionalLight[i].specular = specular;

				break;
			}
		}
	}

	void BaseGame::SetSpotLight(int lightID, vec3 lightPos, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear)
	{
		for (int i = 0; i < 4; i++)
		{
			if (lightID == i)
			{
				pointLight[i].lightPos = lightPos;
				pointLight[i].ambient = ambient;
				pointLight[i].diffuse = diffuse;
				pointLight[i].specular = specular;
				pointLight[i].constant = constant;
				pointLight[i].linear = linear;

				break;
			}
		}
	}

	void BaseGame::SetPointLight(int lightID, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear, float quadratic, int cutOff, int outerCutOff)
	{
		for (int i = 0; i < 4; i++)
		{
			if (lightID == i)
			{
				spotLight[i]->ambient = ambient;
				spotLight[i]->diffuse = diffuse;
				spotLight[i]->specular = specular;
				spotLight[i]->constant = constant;
				spotLight[i]->linear = linear;
				spotLight[i]->quadratic = quadratic;
				spotLight[i]->cutOff = cutOff;
				spotLight[i]->outerCutOff = outerCutOff;

				break;
			}
		}
	}

	void BaseGame::SetPointLightColor(int lightID, vec3 color)
	{
		for (int i = 0; i < 4; i++)
		{
			if (lightID == i)
			{
				pointLight[i].SetLightColor(color);

				break;
			}
		}
	}

	void BaseGame::SetPointLightConstant(int lightID, float constant)
	{
		for (int i = 0; i < 4; i++)
		{
			if (lightID == i)
			{
				pointLight[i].SetConstant(constant);

				break;
			}
		}
	}

	void BaseGame::SetPointLightPosition(int lightID, vec3 position)
	{
		for (int i = 0; i < 4; i++)
		{
			if (lightID == i)
			{
				pointLight[i].SetPosition(position);

				break;
			}
		}
	}
}