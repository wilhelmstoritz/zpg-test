#pragma once

// include the standard C++ headers
#include <chrono>

class DeltaTime {
public:
	DeltaTime();

	void update();

	float getDeltaSeconds();
	float getDeltaMilliseconds();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;

	float m_deltaSeconds;
};
