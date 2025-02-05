#pragma once

// standard c++ libraries
#include <unordered_set>

template <typename TObserverSubject>
class ObserverSubject; // forward declaration due to cross-reference

template <typename TObserverSubject>
class Observer {
public:
	virtual ~Observer() = default;

	virtual void addNotifyingSubject(TObserverSubject* t_subject);
	void clearNotifyingSubjects();

protected:
	bool needsUpdate() const;
	virtual void processSubject(TObserverSubject* t_subject) = 0; // method that will be processed in a class inheriting from observer
	void processAllSubjects();

private:
	std::unordered_set<TObserverSubject*> m_notifyingSubjects;
};

// === templates implementation ================================================
#include "Observer.tpp"
