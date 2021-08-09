#ifndef H_INPUTMODULE
#define H_INPUTMODULE

class EngineCore;

class InputModule {
public:
	EngineCore* const Core;

	InputModule(EngineCore* core);

	void handle_input(int key, int scancode, int action, int mods);

	void subscribe(int key, int scancode, int action, int mods);

private:
	// std::map<..., function> m_keymap;
};

#endif