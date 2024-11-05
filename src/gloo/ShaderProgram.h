#pragma once

#include "VertexShader.h"
#include "FragmentShader.h"
#include "Camera.h"
#include "Observer.h"

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4

class ShaderProgram : public Observer<DefaultCamera> {
public:
	ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader, DefaultCamera* t_camera);
	ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader);
	~ShaderProgram();

	virtual void update(DefaultCamera* t_camera) override;

	/* for debugging purposes
	GLuint getProgramID() const;
	*/
	void use() const;
	void transform(const GLchar* t_matrixName, glm::mat4& t_matrix) const;
	void followCamera();

private:
	GLuint m_programID;
	DefaultCamera* m_camera;
	bool m_cameraUpdate;

	void linkProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader);
};
