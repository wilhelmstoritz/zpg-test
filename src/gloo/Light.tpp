#include "Light.h"

// === template implementation =================================================
// --- public ------------------------------------------------------------------
template <typename T>
void Light::follow() {
	/*if (this->Observer<T>::needsUpdate())
		printf("[light] name %s id %d : follow %s\n", this->getName().c_str(), this->getID(), typeid(T).name());*/

	this->Observer<T>::processAllSubjects();
}
