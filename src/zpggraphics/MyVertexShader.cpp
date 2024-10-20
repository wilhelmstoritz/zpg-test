#include "MyVertexShader.h"

MyVertexShader::MyVertexShader(const char* t_source)
	: MyShader(GL_VERTEX_SHADER, t_source) { }

MyVertexShader::MyVertexShader(const std::string& t_source)
	: MyShader(GL_VERTEX_SHADER, t_source) { }
