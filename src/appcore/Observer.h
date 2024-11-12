#pragma once

// include the standard C++ headers
#include <unordered_set>

template <typename TObserverSubject>
class ObserverSubject; // forward declaration

template <typename TObserverSubject>
class Observer {
public:
	virtual ~Observer() = default;

	void addNotifyingSubject(TObserverSubject* t_subject);
	void clearNotifyingSubjects();

protected:
	bool needsUpdate() const;
	void processAllSubjects();

protected:
	std::unordered_set<TObserverSubject*> m_notifyingSubjects;

	virtual void processSubject(TObserverSubject* t_subject) = 0; // method that will be processed in a class inheriting from observer
};

// === template implementation =================================================
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

	for (const auto& subject : this->m_notifyingSubjects) {
		this->processSubject(*subject);
	}

	this->clearNotifyingSubjects();
}
*/
template <typename TObserverSubject>
void Observer<TObserverSubject>::processAllSubjects() {
	//if (!this->needsUpdate()) return;

	for (auto* subject : this->m_notifyingSubjects) {
		this->processSubject(subject);
	}

	this->clearNotifyingSubjects();
}
