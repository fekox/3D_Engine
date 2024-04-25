#pragma once
#include "CoreEngine/Window.h"
#include "CoreEngine/Renderer.h"

#include "Shape/Shape.h"
#include "Shape/Shape3D.h"

#include "Sprite/Sprite.h"

#include "Camera/Camera.h"

#include "Light/Light.h"
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

	public:

		Camera* camera;
		Light* light;
		Material* material;
		
		InputSystem* inputSystem;
		BaseGame(int width, int height, const char* windowName);
		~BaseGame();
		void gameLoop();
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void exit() = 0;
		Renderer* GetRenderer();
	};

	void Mouse_Callback(GLFWwindow* window, double xpos, double ypos);
	void Scroll_Callback(GLFWwindow* window, double xpos, double ypos);
}