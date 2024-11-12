#pragma once

// include the standard C++ headers
#include <unordered_set>

template <typename Message>
class ObserverSubject; // forward declaration

template <typename Message>
class Observer {
public:
	virtual ~Observer() = default;

	virtual void updateObserver(Message* t_message) = 0;

	void addNotifyingSubject(Message* t_subject);
	void clearNotifyingSubjects();

protected:
	bool needsUpdate() const;
	void processAllSubjects();

protected:
	std::unordered_set<Message*> m_notifyingSubjects;

	virtual void processSubject(Message* t_subject) = 0; // method that will be processed in a class inheriting from observer
};

// === template implementation =================================================
// --- public ------------------------------------------------------------------
template <typename Message>
void Observer<Message>::addNotifyingSubject(Message* t_subject) {
	this->m_notifyingSubjects.insert(t_subject);
}

template <typename Message>
void Observer<Message>::clearNotifyingSubjects() {
	this->m_notifyingSubjects.clear();
}

// --- protected ---------------------------------------------------------------
template <typename Message>
bool Observer<Message>::needsUpdate() const {
	return !this->m_notifyingSubjects.empty();
}

/*
template <typename Message>
void Observer<Message>::processAllSubjects() {
	for (const auto& subject : this->m_notifyingSubjects) {
		this->processSubject(*subject);
	}

	this->clearNotifyingSubjects();
}
*/
template <typename Message>
void Observer<Message>::processAllSubjects() {
	for (const auto* subject : this->m_notifyingSubjects) {
		this->processSubject(subject);
	}

	this->clearNotifyingSubjects();
}
