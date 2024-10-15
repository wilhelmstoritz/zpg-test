#pragma once

#include "MyShader.h"

class MyFragmentShader : public MyShader {
public:
	MyFragmentShader(const char* t_source);
	MyFragmentShader(const std::string& t_source);
};
