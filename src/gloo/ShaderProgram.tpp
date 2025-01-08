#include "ShaderProgram.h"

// === template implementation =================================================
// --- public ------------------------------------------------------------------
template <typename T>
void ShaderProgram::follow() {
//void ShaderProgram::follow<T>(void* t_anything) { // debugging purposes only
	/*if (this->Observer<T>::needsUpdate())
		printf("[shader program] id %d : follow %s\n", this->m_ID, typeid(T).name());*/

	this->Observer<T>::processAllSubjects();
}
