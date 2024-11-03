#include "Transformation.h"

// --- public ------------------------------------------------------------------
Transformation::Transformation() {
	//this->m_transformations.push_back(glm::mat4(1.0f));
}

void Transformation::addTransformation(glm::mat4 t_transformation) {
	this->m_transformations.push_back(t_transformation);
}

glm::mat4* Transformation::getTransformation() {
	this->m_transformation = glm::mat4(1.0f);
	for (const auto& nextTransformation : this->m_transformations)
		this->m_transformation *= nextTransformation;

	return &this->m_transformation;
}

// --- private -----------------------------------------------------------------
