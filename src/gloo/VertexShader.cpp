#include "VertexShader.h"

VertexShader::VertexShader(const char* t_source)
	: Shader(GL_VERTEX_SHADER, t_source) { }

VertexShader::VertexShader(const std::string& t_source)
	: Shader(GL_VERTEX_SHADER, t_source) { }
