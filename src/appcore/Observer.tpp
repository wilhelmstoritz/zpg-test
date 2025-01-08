#include "Observer.h"

// === templates implementation ================================================
// --- public ------------------------------------------------------------------
template <typename TObserverSubject>
void Observer<TObserverSubject>::addNotifyingSubject(TObserverSubject* t_subject) {
	this->m_notifyingSubjects.insert(t_subject);
}

template <typename TObserverSubject>
void Observer<TObserverSubject>::clearNotifyingSubjects() {
	this->m_notifyingSubjects.clear();
}

// --- protected ---------------------------------------------------------------
template <typename TObserverSubject>
bool Observer<TObserverSubject>::needsUpdate() const {
	return !this->m_notifyingSubjects.empty();
}

/*
template <typename TObserverSubject>
void Observer<TObserverSubject>::processAllSubjects() {
	//if (!this->needsUpdate()) return;

	for (const auto& subject : this->m_notifyingSubjects)
		this->processSubject(*subject);

	this->clearNotifyingSubjects();
}
*/
template <typename TObserverSubject>
void Observer<TObserverSubject>::processAllSubjects() {
	//if (!this->needsUpdate()) return;

	for (auto* subject : this->m_notifyingSubjects)
		this->processSubject(subject);

	this->clearNotifyingSubjects();
}
