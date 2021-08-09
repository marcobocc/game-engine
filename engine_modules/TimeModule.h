#ifndef H_TIMEMODULE
#define H_TIMEMODULE

class EngineCore;

class TimeModule {
public:
	EngineCore* const Core;

	TimeModule(EngineCore* core);

	void set_gettime_callback(double (*function_ptr)());

	void reset();

	void update();

	double deltaTime() const;

	double current_time() const;

private:
	double m_deltaTime;
	double m_time_of_last_update;
	double (*m_gettime_callback)();
};

#endif