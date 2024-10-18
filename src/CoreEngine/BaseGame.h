#pragma once
#include "CoreEngine/Window.h"
#include "CoreEngine/Renderer.h"

#include "Shape/Shape.h"
#include "Shape/Shape3D.h"

#include "Sprite/Sprite.h"

#include "Camera/Camera.h"

#include "Lights/Light.h"
#include "Material/Material.h"

#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include "Tools/Time/Time.h"
#include "Tools/Collision Manager/CollisionManager.h"
#include "InputSystem.h"

using namespace shape;
using namespace shape3D;
using namespace camera;
using namespace light;
using namespace material;
using namespace window;
using namespace renderer;
using namespace sprite;
using namespace collisionManager;
using namespace inputSystem;

namespace baseEngine
{
	/// <summary>
	/// Class BaseGame
	/// </summary>
	class EXPORT BaseGame
	{
	private:

		Renderer* renderer;
		Window* window;
		ErrorLog errorLog;

		void CalculateTargetPlanes();

	public:

		Camera* camera;
		PointLight* pointLight[4];
		DirectionalLight directionaLight[4];
		SpotLight* spotLight[4];
		Material* material;

		float screenRatio;
		
		InputSystem* inputSystem;
		BaseGame(int width, int height, const char* windowName);
		~BaseGame();
		void gameLoop();
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void exit() = 0;
		Renderer* GetRenderer();

		void AddPlaneToBSP(Plane plane);
		void AddPlaneToBSP(glm::vec3 point, glm::vec3 normal);

		Transform* bspTarget;
		vector<Plane> bspPlanes;
		vector<bool> planesToCheck;
	};

	void Mouse_Callback(GLFWwindow* window, double xpos, double ypos);
	void Scroll_Callback(GLFWwindow* window, double xpos, double ypos);
}