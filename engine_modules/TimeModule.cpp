#include "TimeModule.h"

TimeModule::TimeModule(EngineCore* core) :
	Core(core),
	m_deltaTime(0.0f),
	m_time_of_last_update(0.0f),
	m_gettime_callback(nullptr) {
}

void TimeModule::set_gettime_callback(double (*function_ptr)()) {
	m_gettime_callback = function_ptr;
}

void TimeModule::reset() {
	m_deltaTime = 0.0f;
	m_time_of_last_update = m_gettime_callback();
}

void TimeModule::update() {
	double newtime = 0.0f;
	if (m_gettime_callback) {
		newtime = m_gettime_callback();
	}
	m_deltaTime = (newtime - m_time_of_last_update);
	m_time_of_last_update = newtime;
	/* ...Timer management goes here... */
}

double TimeModule::deltaTime() const {
	return m_deltaTime;
}

double TimeModule::current_time() const {
	return m_time_of_last_update;
}