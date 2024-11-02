#include "ZPGFragmentShader.h"

ZPGFragmentShader::ZPGFragmentShader(const char* t_source)
	: ZPGShader(GL_FRAGMENT_SHADER, t_source) { }

ZPGFragmentShader::ZPGFragmentShader(const std::string& t_source)
	: ZPGShader(GL_FRAGMENT_SHADER, t_source) { }
