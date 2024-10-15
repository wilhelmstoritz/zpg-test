#include "MyFragmentShader.h"

MyFragmentShader::MyFragmentShader(const char* t_source)
	: MyShader(GL_FRAGMENT_SHADER, t_source) { }

MyFragmentShader::MyFragmentShader(const std::string& t_source)
	: MyShader(GL_FRAGMENT_SHADER, t_source) { }
