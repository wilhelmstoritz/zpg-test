#pragma once

#include "ZPGShader.h"

class ZPGVertexShader : public ZPGShader {
public:
	ZPGVertexShader(const char* t_source);
	ZPGVertexShader(const std::string& t_source);
};
