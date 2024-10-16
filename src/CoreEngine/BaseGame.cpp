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

		camera = new Camera(45.f, width, height);
		newCamera = camera;

		screenRatio = window->getWidth() / window->getHeight();

		frustum = new Frustum();

		for (int i = 0; i < 4; i++)
		{
			pointLight[i] = new PointLight();
			directionaLight[i] = DirectionalLight(); 
			spotLight[i] = new SpotLight(camera);
		}

		renderer = new Renderer(window, camera, pointLight, directionaLight, spotLight);

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

		for (int i = 0; i < 4; i++)
		{
			delete pointLight[i];
			delete spotLight[i];
		}
	}

	void BaseGame::gameLoop()
	{
		while (!glfwWindowShouldClose(window->getWindow()))
		{
			Time::Update(glfwGetTime());
			
			renderer->StartDraw();
			
			camera->CameraMovement(window->getWindow());
			frustum = camera->CreateFrustumFromCamera(camera, screenRatio, glm::radians(camera->zoom), camera->nearPlane, camera->farPlane);

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
}