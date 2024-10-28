#include "ZPGCamera.h"
#include "ZPGShaderProgram.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// --- public ------------------------------------------------------------------
//ZPGCamera::ZPGCamera(ZPGShaderProgram* t_shaderProgram) { }

ZPGCamera::ZPGCamera() {
	this->m_shaderProgram = nullptr;
	//this->m_shaderProgram = t_shaderProgram;

	// view matrix
	this->m_viewMatrix = glm::mat4(1.0f); // identity matrix (jednotkova matice)

	/*
	poměr okna byste měli upravovat podle rozlišení okna, ve kterém se obsah zobrazuje.
	z_near nastavte na hodnotu 0.1, nepouživejte hodnotu 0.
	*/
	// projection matrix: 60° field of view, 4:3 ratio, display range : 0.1 unit <-> 100 units
	this->m_projectionMatrix = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// projection matrix: 45° field of view, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//this->m_projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

glm::mat4 ZPGCamera::getView(void) {
	// !!! TBD !!!
	double alpha = 0;
	double fi = 0;

	glm::vec<3, double> eye = glm::vec3(5.0f, 0.0f, 0.0f);

	glm::vec<3, double> target = glm::vec3(0.f, 0.f, 0.f); // glm::vec3(0.f, 0.f, 0.f)
	//target.x = sin(alpha) * cos(fi);
	//target.z = sin(alpha) * sin(fi);
	//target.y = cos(alpha);

	glm::vec<3, double> up = glm::vec3(0.f, 1.f, 0.f);

	//return glm::lookAt(eye, eye + target, up);
	return glm::lookAt(eye, target, up);
}

glm::mat4 ZPGCamera::getProjection(void) {
	return this->m_projectionMatrix;
}

// --- private -----------------------------------------------------------------
