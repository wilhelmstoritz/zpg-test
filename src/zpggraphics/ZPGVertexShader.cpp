#include "ZPGVertexShader.h"

ZPGVertexShader::ZPGVertexShader(const char* t_source)
	: ZPGShader(GL_VERTEX_SHADER, t_source) { }

ZPGVertexShader::ZPGVertexShader(const std::string& t_source)
	: ZPGShader(GL_VERTEX_SHADER, t_source) { }
