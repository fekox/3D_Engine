#pragma once
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <unordered_map>
#include "Tools/Error Log/ErrorLog.h"
#include "..\libs\glm\include\glm.hpp"

using namespace std;
using namespace errorLog;

struct ShaderProgramSource
{
	string VertexSource;
	string FragmentSource;
};

namespace shader
{
	class Shader
	{
		private:

		ErrorLog errorLog;
		unsigned int IDshader;
		std::unordered_map<std::string, GLint> m_UniformLocationCache;
		GLint GetUniformLocation(const std::string& name);

		public:

		Shader();
		~Shader();
		static ShaderProgramSource ParseShader(const string& filepath);
		static GLuint compileShader(unsigned int type, const string& source);
		static int createShader(const string& vertexShader, const string& fragmentShader);
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetVec2(const std::string& name, const glm::vec2& value);
		void SetVec3(const std::string& name, const glm::vec3& value);
		void SetVec4(const std::string& name, const glm::vec4& value);
		void SetVec4(const std::string& name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(IDshader, name.c_str()), x, y, z, w); }
		void SetMat3(const std::string& name, const glm::mat3& value);
		void SetMat4(const std::string& name, const glm::mat4& value);
	};

}

