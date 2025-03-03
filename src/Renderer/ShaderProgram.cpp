#include <iostream>
#include "ShaderProgram.h"

namespace Renderer {

	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {

		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {

			std::cerr << "Vertex shader compile-time error" << std::endl;
			return;

		}

		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {

			std::cerr << "Fragment shader compile-time error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;

		}

		_ID = glCreateProgram();
		glAttachShader(_ID, vertexShaderID);
		glAttachShader(_ID, fragmentShaderID);
		glLinkProgram(_ID);

		GLint success;
		glGetProgramiv(_ID, GL_LINK_STATUS, &success);
		if (!success) {

			GLchar infoLog[1024];
			glGetShaderInfoLog(_ID, 1024, nullptr, infoLog);
			std::cerr << "Error::Shader: Linking-time error:\n" << infoLog << std::endl;

		}
		else {

			_isCompiled = true;

		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID) {

		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {

			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "Error::Shader: Compile-time error:\n" << infoLog << std::endl;
			return false;

		}
		return true;

	}

	ShaderProgram::~ShaderProgram() {

		glDeleteProgram(_ID);

	}

	void ShaderProgram::use() const {

		glUseProgram(_ID);

	}

	ShaderProgram& ShaderProgram::operator = (ShaderProgram&& shaderProgram) {

		glDeleteProgram(_ID);
		_ID = shaderProgram._ID;
		_isCompiled = shaderProgram._isCompiled;

		shaderProgram._ID = 0;
		shaderProgram._isCompiled = false;
		return *this;

	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) {

		_ID = shaderProgram._ID;
		_isCompiled = shaderProgram._isCompiled;

		shaderProgram._ID = 0;
		shaderProgram._isCompiled = false;


	}

}