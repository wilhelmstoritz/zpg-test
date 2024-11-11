#pragma once

#include "Observer.h"

// include the standard C++ headers
#include <vector>
#include <algorithm>
#include <memory>

template <typename Message>
class ObserverSubject {
public:
    void addObserver(Observer<Message>* t_observer);
    void removeObserver(Observer<Message>* t_observer);
    void removeAllObservers();
    void notify(Message* t_message);
    //void addObserver(std::shared_ptr<Observer<Message>> t_observer);
    //void removeObserver(std::shared_ptr<Observer<Message>> t_observer);
    //void notify(Message* t_message);

private:
    std::vector<Observer<Message>*> m_observers;
    //std::vector<std::shared_ptr<Observer<Message>>> m_observers;
};

// --- template implementation -------------------------------------------------
template <typename Message>
void ObserverSubject<Message>::addObserver(Observer<Message>* t_observer) {
//void ObserverSubject<Message>::addObserver(std::shared_ptr<Observer<Message>> t_observer) {
    this->m_observers.push_back(t_observer);
}

template <typename Message>
void ObserverSubject<Message>::removeObserver(Observer<Message>* t_observer) {
//void ObserverSubject<Message>::removeObserver(std::shared_ptr<Observer<Message>> t_observer) {
    this->m_observers.erase(std::remove(this->m_observers.begin(), this->m_observers.end(), t_observer), this->m_observers.end());
}

template <typename Message>
void ObserverSubject<Message>::removeAllObservers() {
	this->m_observers.clear();
}

template <typename Message>
void ObserverSubject<Message>::notify(Message* t_message) {
    for (const auto& observer : this->m_observers) {
        if (observer) {
            observer->addNotifyingSubject(this);
            observer->updateObserver(t_message);
        }
    }
}
