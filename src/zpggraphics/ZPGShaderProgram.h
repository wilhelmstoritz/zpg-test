#pragma once

#include "ZPGVertexShader.h"
#include "ZPGFragmentShader.h"

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4

class ZPGCamera; // forward declaration due to cross reference

class ZPGShaderProgram {
public:
	ZPGShaderProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader, ZPGCamera* m_camera);
	ZPGShaderProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader);
	~ZPGShaderProgram();

	/* for debugging purposes
	GLuint getProgramID() const;
	*/
	void use() const;
	void transform(const GLchar* t_matrixName, glm::mat4& t_value) const;

private:
	GLuint m_programID;
	ZPGCamera* m_camera;

	void linkProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader);
};
