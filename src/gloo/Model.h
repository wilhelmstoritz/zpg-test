#pragma once

#include "Observer.h"
#include "Camera.h"
#include "Drawable.h"
#include "VAO.h"
#include "IBO.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class Model : public Observer<Camera>, public Drawable {
public:
	Model(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	Model(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);
	Model(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	Model(ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);

	std::string getName();

	ShaderProgram* getShaderProgram();
	Transformation* getTransformation();

	glm::vec3 getDiffuseColor();
	glm::vec3 getSpecularColor();
	float getKDiffuse();
	float getKSpecular();

	GLint getTextureID();

	void setDiffuseColor(const glm::vec3& t_diffuseColor);
	void setSpecularColor(const glm::vec3& t_specularColor);
	void setKDiffuse(float t_kDiffuse);
	void setKSpecular(float t_kSpecular);

	void setTextureID(const GLuint t_textureID);

	virtual bool animate();
	virtual void draw() override;

	template<typename T>
	void follow();

protected:
	glm::vec3 m_diffuseColor;
	glm::vec3 m_specularColor;
	float m_kDiffuse; // diffuse reflection coefficient
	float m_kSpecular; // specular reflection coefficient

	GLuint m_textureID; // texture unit

	virtual void processSubject(Camera* t_camera) override;

	virtual void preUpdate();
	virtual void postUpdate();

private:
	std::string m_name;

	ShaderProgram* m_shaderProgram;
	VAO* m_vao; // vertex array object
	IBO* m_ibo; // index buffer object; if it exists
	GLint m_first; // first vertex
	GLsizei m_count; // number of vertices

	Transformation m_transformation;
	glm::mat3 m_normalMatrix;

	void updateAndNotify();
};
