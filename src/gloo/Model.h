#pragma once

#include "ObserverSubject.h"
#include "Drawable.h"
#include "VAO.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class Model : public ObserverSubject<Model>, public Drawable {
public:
	Model(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);

	ShaderProgram* getShaderProgram();
	Transformation* getTransformation();

	glm::vec3 getDiffuseColor();
	float getKDiffuse();

	virtual bool animate();
	virtual void draw() override;

private:
	ShaderProgram* m_shaderProgram;
	VAO* m_vao;
	GLint m_first;
	GLsizei m_count;

	Transformation m_transformation;
	glm::mat3 m_normalMatrix;

	glm::vec3 m_diffuseColor;
	float m_kDiffuse; // diffuse reflection coefficient

	void updateAndNotify();
};
