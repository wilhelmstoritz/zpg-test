#pragma once

#include "ZPGShader.h"

class ZPGFragmentShader : public ZPGShader {
public:
	ZPGFragmentShader(const char* t_source);
	ZPGFragmentShader(const std::string& t_source);
};
