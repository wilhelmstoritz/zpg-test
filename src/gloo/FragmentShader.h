#pragma once

#include "Shader.h"

class FragmentShader : public Shader {
public:
	FragmentShader(const char* t_source);
	FragmentShader(const std::string& t_source);
};
