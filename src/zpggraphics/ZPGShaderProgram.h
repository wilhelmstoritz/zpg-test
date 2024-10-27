#pragma once

#include "ZPGVertexShader.h"
#include "ZPGFragmentShader.h"

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4

class ZPGShaderProgram {
public:
	ZPGShaderProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader);
	~ZPGShaderProgram();

	/* for debugging purposes
	GLuint getProgramID() const;
	*/
	void use() const;
	void transform(const GLchar* t_matrixName, glm::mat4& t_value);

private:
	GLuint m_programID;

	void linkProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader);
};
