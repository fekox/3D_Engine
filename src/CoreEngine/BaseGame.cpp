#include <iostream>
#include "CoreEngine/BaseGame.h"

using namespace std;

namespace baseEngine
{
	Camera* newCamera;
	AABB testAABB = { {0, 0, 0}, {1.f, 1.f, 1.f} };

	BaseGame::BaseGame(int width, int height, const char* windowName)
	{
		errorLog.CheckGlfwInit();

		window = new Window(width, height, windowName, NULL, NULL);

		errorLog.CheckGlewInit();

		camera = new Camera(45.f, width, height);
		newCamera = camera;

		root = new Transform(nullptr, glm::vec3(0), glm::vec3(0), glm::vec3(1));

		screenRatio = window->getWidth() / window->getHeight();

		for (int i = 0; i < 4; i++)
		{
			pointLight[i] = new PointLight();
			directionaLight[i] = DirectionalLight(); 
			spotLight[i] = new SpotLight(camera);
		}

		renderer = new Renderer(window, camera, pointLight, directionaLight, spotLight);

		inputSystem = new InputSystem(window->getWindow());

		bspTarget = camera->cameraPos;

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
			
			CalculateTargetPlanes();
			renderer->StartDraw();
			
			camera->CameraMovement(window->getWindow());

			renderer->UpdateProjection(camera);
			renderer->UpdateView(camera);
			
			update();
			
			frustum = camera->CreateFrustumFromCamera(camera, window->getWidth() / window->getHeight(), camera->zoom, camera->nearPlane, camera->farPlane);
			DrawScene();

			renderer->EndDraw();
		}
	}

	Renderer* BaseGame::GetRenderer()
	{
		return renderer;
	}

	void BaseGame::DrawScene()
	{
		for (auto child : root->children)
		{
			if (child->entity != nullptr)
			{
				Model* entity = dynamic_cast<Model*>(child->entity);
				if (entity != nullptr)
				{
					entity->GenerateAABB();
					entity->DrawWithBSP(bspPlanes, planesToCheck, frustum, false);
				}
			}
		}

		if (showDebug)
		{
			std::vector<glm::vec3> vertices = testAABB.GetVertice();
			renderer->DrawLinesAABB(root->m_modelMatrix, vertices);
			if (!bspPlanes.empty())
			{
				for (Plane plane : bspPlanes)
				{
					renderer->DrawPlane(&plane);
				}
			}
		}
	}

	void BaseGame::CalculateTargetPlanes()
	{
		bspTarget = camera->cameraPos;

		planesToCheck.clear();

		for (int i = 0; i < bspPlanes.size(); ++i)
		{
			bool side = bspPlanes[i].GetSide(bspTarget);
			planesToCheck.push_back(side);
		}
	}

	void BaseGame::AddPlaneToBSP(Plane plane)
	{
		bspPlanes.push_back(plane);
	}

	void BaseGame::AddPlaneToBSP(glm::vec3 point, glm::vec3 normal)
	{
		Plane plane = { point,normal };
		bspPlanes.push_back(plane);
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