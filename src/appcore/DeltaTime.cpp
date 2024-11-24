#include "DeltaTime.h"

// --- public ------------------------------------------------------------------
DeltaTime::DeltaTime() {
	this->m_lastTime = std::chrono::high_resolution_clock::now();

	this->m_deltaSeconds = 0.f;
}

void DeltaTime::update() {
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<float>(currentTime - this->m_lastTime);

	this->m_deltaSeconds = duration.count();
	this->m_lastTime = currentTime;
}

float DeltaTime::getDeltaSeconds() { return this->m_deltaSeconds; }
float DeltaTime::getDeltaMilliseconds() { return this->m_deltaSeconds * 1000.f; }
