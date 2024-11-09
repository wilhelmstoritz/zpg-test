#pragma once

template <typename Message>
class Observer {
public:
	virtual ~Observer() = default;

	virtual void updateObserver(Message* t_message) = 0;
};
