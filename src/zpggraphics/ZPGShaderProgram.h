#pragma once

#include "ZPGVertexShader.h"
#include "ZPGFragmentShader.h"

class ZPGShaderProgram {
public:
	ZPGShaderProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader);
	~ZPGShaderProgram();

	/* for debugging purposes
	GLuint getProgramID() const;
	*/
	void use() const;

private:
	GLuint m_programID;

	void linkProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader);
};
