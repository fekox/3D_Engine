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

		Window* window;
		ErrorLog errorLog;
		Renderer* renderer;
	public:
		Camera* camera;
		Material* material;

		DirectionalLight directionalLight[4];
		SpotLight* spotLight[4];
		PointLight pointLight[4];
		
		InputSystem* inputSystem;
		BaseGame(int width, int height, const char* windowName);
		~BaseGame();
		void gameLoop();
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void exit() = 0;
		Renderer* GetRenderer();

		void SetDirectionaLight(int lightID, vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular);

		void SetSpotLight(int lightID, vec3 lightPos, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear);

		void SetPointLight(int lightID, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear, float quadratic, int cutOff, int outerCutOff);

		void SetPointLightColor(int lightID, vec3 color);

		void SetPointLightConstant(int lightID, float constant);

		void SetPointLightPosition(int lightID, vec3 position);
	};

	void Mouse_Callback(GLFWwindow* window, double xpos, double ypos);
	void Scroll_Callback(GLFWwindow* window, double xpos, double ypos);
}