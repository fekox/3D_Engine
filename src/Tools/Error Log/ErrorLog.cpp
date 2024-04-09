#include "Tools/Error Log/ErrorLog.h"

using namespace std;

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) errorLog.GLClearError();\
				x;\
				ASSERT(errorLog.GLLogCall(#x, __FILE__, __LINE__))

namespace errorLog
{
	int ErrorLog::CheckGlfwInit()
	{
		if (!glfwInit())
		{
			cout << "Error to start glfw" << endl;

			return -1;
		}
		return 0;
	}

	void ErrorLog::CheckGlewInit()
	{
		if (glewInit() != GLEW_OK)
		{
			cout << "Error to start glew." << endl;
		}
	}

	void ErrorLog::ShaderLocationError(int location)
	{
		ASSERT(location != -1);

		if (location == -1)
		{
			cout << "Error in the shader location name." << endl;
		}
	}

	void ErrorLog::GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool ErrorLog::GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << endl;
			return false;
		}
		return true;
	}
}
