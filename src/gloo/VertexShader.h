#pragma once

#include "Shader.h"

class VertexShader : public Shader {
public:
	VertexShader(const char* t_source);
	VertexShader(const std::string& t_source);
};
