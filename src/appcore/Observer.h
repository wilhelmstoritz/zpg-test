#pragma once

template <typename Message>
class Observer {
public:
	virtual void update(Message* t_message) = 0;
	virtual ~Observer() = default;
};
