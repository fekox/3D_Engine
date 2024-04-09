#pragma once
#include "CoreEngine/Window.h"
#include "Tools/DLL-Exp/dll-Exp-Inp.h"

namespace inputSystem
{
	class EXPORT InputSystem
	{
	private:
		GLFWwindow* window;
	public:
		enum KeyCode
		{
			N0 = GLFW_KEY_0,           
			N1 = GLFW_KEY_1,                
			N2 = GLFW_KEY_2,
			N3 = GLFW_KEY_3,
			N4 = GLFW_KEY_4,
			N5 = GLFW_KEY_5,
			N6 = GLFW_KEY_6,
			N7 = GLFW_KEY_7,
			N8 = GLFW_KEY_8,
			N9 = GLFW_KEY_9,
			q = GLFW_KEY_Q,
			w = GLFW_KEY_W,
			e = GLFW_KEY_E,
			r = GLFW_KEY_R,
			t = GLFW_KEY_T,
			y = GLFW_KEY_Y,
			u = GLFW_KEY_U,
			i = GLFW_KEY_I,
			o = GLFW_KEY_O,
			p = GLFW_KEY_P,
			a = GLFW_KEY_A,
			s = GLFW_KEY_S,
			d = GLFW_KEY_D,
			f = GLFW_KEY_F,
			g = GLFW_KEY_G,
			h = GLFW_KEY_H,
			j = GLFW_KEY_J,
			k = GLFW_KEY_K,
			l = GLFW_KEY_L,
			z = GLFW_KEY_Z,
			x = GLFW_KEY_X,
			c = GLFW_KEY_C,
			v = GLFW_KEY_V,
			b = GLFW_KEY_B,
			n = GLFW_KEY_N,
			m = GLFW_KEY_M,
			upArrow = GLFW_KEY_UP,
			downArrow = GLFW_KEY_DOWN,
			leftArrow = GLFW_KEY_LEFT,
			rightArrow = GLFW_KEY_RIGHT
		};

		enum Action
		{
			Pressed = GLFW_PRESS,
			Reapeated = GLFW_REPEAT,
			Released = GLFW_RELEASE,
		};

		InputSystem(GLFWwindow* window);

		bool getKey(KeyCode key, Action keyAction);
	};
}