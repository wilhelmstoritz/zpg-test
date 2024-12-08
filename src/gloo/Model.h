#pragma once

#include "ObserverSubject.h"
#include "Drawable.h"
#include "VAO.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class Model : public ObserverSubject<Model>, public Drawable {
public:
	Model(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);

	std::string getName();

	ShaderProgram* getShaderProgram();
	Transformation* getTransformation();

	glm::vec3 getDiffuseColor();
	float getKDiffuse();

	void setDiffuseColor(const glm::vec3& t_diffuseColor);
	void setKDiffuse(float t_kDiffuse);

	virtual bool animate();
	virtual void draw() override;

protected:
	glm::vec3 m_diffuseColor;
	float m_kDiffuse; // diffuse reflection coefficient

private:
	std::string m_name;

	ShaderProgram* m_shaderProgram;
	VAO* m_vao;
	GLint m_first;
	GLsizei m_count;

	Transformation m_transformation;
	glm::mat3 m_normalMatrix;

	void updateAndNotify();
};
