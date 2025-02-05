#pragma once

#include "Observer.h"

// standard c++ libraries
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
    std::unordered_set<Observer<TObserverSubject>*> m_observers;
    //std::unordered_set<std::shared_ptr<Observer<TObserverSubject>>> m_observers;
};

// === templates implementation ================================================
#include "ObserverSubject.tpp"
