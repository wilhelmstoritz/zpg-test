#pragma once

template <typename Message>
class Observer {
public:
	virtual ~Observer() = default;

	virtual void update(Message* t_message) = 0;
};
