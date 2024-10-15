#pragma once

#include "MyShader.h"

class MyVertexShader : public MyShader {
public:
	MyVertexShader(const char* t_source);
	MyVertexShader(const std::string& t_source);
};
