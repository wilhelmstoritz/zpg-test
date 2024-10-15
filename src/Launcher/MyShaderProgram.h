#pragma once

#include "MyVertexShader.h"
#include "MyFragmentShader.h"

class MyShaderProgram {
public:
	MyShaderProgram(const MyShader& t_vertexShader, const MyShader& t_fragmentShader);
	~MyShaderProgram();

	/* for debugging purposes
	GLuint getProgramID() const;
	*/
	void use() const;

private:
	GLuint m_programID;

	void linkProgram(const MyShader& t_vertexShader, const MyShader& t_fragmentShader);
};
