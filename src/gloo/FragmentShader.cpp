#include "FragmentShader.h"

FragmentShader::FragmentShader(const char* t_source)
	: Shader(GL_FRAGMENT_SHADER, t_source) { }

FragmentShader::FragmentShader(const std::string& t_source)
	: Shader(GL_FRAGMENT_SHADER, t_source) { }
