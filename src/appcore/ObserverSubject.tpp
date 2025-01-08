#include "ObserverSubject.h"

// === templates implementation ================================================
// --- public ------------------------------------------------------------------
template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::addObserver(Observer<TObserverSubject>* t_observer) {
	//void ObserverSubject<TObserverSubject>::addObserver(std::shared_ptr<Observer<TObserverSubject>> t_observer) {
	this->m_observers.insert(t_observer);

	this->notifyObserver(t_observer, dynamic_cast<TObserverSubject*>(this));
}

template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::removeObserver(Observer<TObserverSubject>* t_observer) {
	//void ObserverSubject<TObserverSubject>::removeObserver(std::shared_ptr<Observer<TObserverSubject>> t_observer) {
	this->m_observers.erase(t_observer);
}

template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::removeAllObservers() {
	this->m_observers.clear();
}

// --- protected ---------------------------------------------------------------
template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::notifyObserver(Observer<TObserverSubject>* t_observer, TObserverSubject* t_message) {
	if (t_observer)
		t_observer->addNotifyingSubject(t_message);
}

template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::notifyObservers(TObserverSubject* t_message) {
	for (const auto& observer : this->m_observers)
		this->notifyObserver(observer, t_message);
}

template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::notifyObservers() {
	this->notifyObservers(dynamic_cast<TObserverSubject*>(this));
}
