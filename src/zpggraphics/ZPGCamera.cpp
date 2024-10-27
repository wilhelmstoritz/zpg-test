#include "ZPGCamera.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// --- public ------------------------------------------------------------------
ZPGCamera::ZPGCamera() {
	// view matrix
	this->m_viewMatrix = glm::mat4(1.0f); // identity matrix (jednotkova matice)

	/*
	poměr okna byste měli upravovat podle rozlišení okna, ve kterém se obsah zobrazuje.
	z_near nastavte na hodnotu 0.1, nepouživejte hodnotu 0.
	*/
	// projection matrix: 60° field of view, 4:3 ratio, display range : 0.1 unit <-> 100 units
	this->m_projectionMatrix = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

glm::mat4 ZPGCamera::getCamera(void) {
	// !!! TBD !!!
	double alpha = 0;
	double fi = 0;

	glm::vec<3, double> eye;

	glm::vec<3, double> target;
	target.x = sin(alpha) * cos(fi);
	target.z = sin(alpha) * sin(fi);
	target.y = cos(alpha);

	glm::vec<3, double> up;

	return glm::lookAt(eye, eye + target, up);
}

// --- protected ---------------------------------------------------------------
