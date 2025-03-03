#pragma once
#include <iostream>
#include <glad/glad.h>

namespace Renderer{

	class ShaderProgram {
	
	private:

		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool _isCompiled = false;
		GLuint _ID = 0;

	public:

		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const { return _isCompiled; }
		void use() const;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator = (ShaderProgram&&);
		ShaderProgram(ShaderProgram&& shaderProgram);

			
	};

}
