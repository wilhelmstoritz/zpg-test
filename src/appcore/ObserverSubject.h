#pragma once

#include "Observer.h"

// include the standard C++ headers
#include <vector>
#include <algorithm>
#include <memory>

template <typename TObserverSubject>
class ObserverSubject {
public:
    virtual ~ObserverSubject() = default; // virtual destructor to make the type polymorphic; because of dynamic_cast

    void addObserver(Observer<TObserverSubject>* t_observer);
    void removeObserver(Observer<TObserverSubject>* t_observer);
    void removeAllObservers();
    //void addObserver(std::shared_ptr<Observer<TObserverSubject>> t_observer);
    //void removeObserver(std::shared_ptr<Observer<TObserverSubject>> t_observer);

protected:
    void notifyObserver(Observer<TObserverSubject>* t_observer, TObserverSubject* t_message);
    void notifyObservers(TObserverSubject* t_message);
    void notifyObservers();

private:
    std::vector<Observer<TObserverSubject>*> m_observers;
    //std::vector<std::shared_ptr<Observer<TObserverSubject>>> m_observers;
};

// === template implementation =================================================
// --- public ------------------------------------------------------------------
template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::addObserver(Observer<TObserverSubject>* t_observer) {
//void ObserverSubject<TObserverSubject>::addObserver(std::shared_ptr<Observer<TObserverSubject>> t_observer) {
    this->m_observers.push_back(t_observer);

    this->notifyObserver(t_observer, dynamic_cast<TObserverSubject*>(this));
}

template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::removeObserver(Observer<TObserverSubject>* t_observer) {
//void ObserverSubject<TObserverSubject>::removeObserver(std::shared_ptr<Observer<TObserverSubject>> t_observer) {
    this->m_observers.erase(std::remove(this->m_observers.begin(), this->m_observers.end(), t_observer), this->m_observers.end());
}

template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::removeAllObservers() {
	this->m_observers.clear();
}

// --- protected ---------------------------------------------------------------
template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::notifyObserver(Observer<TObserverSubject>* t_observer, TObserverSubject* t_message) {
	if (t_observer) {
		t_observer->addNotifyingSubject(t_message);
	}
}

template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::notifyObservers(TObserverSubject* t_message) {
    for (const auto& observer : this->m_observers) {
        this->notifyObserver(observer, t_message);
    }
}

template <typename TObserverSubject>
void ObserverSubject<TObserverSubject>::notifyObservers() {
    this->notifyObservers(dynamic_cast<TObserverSubject*>(this));
}
