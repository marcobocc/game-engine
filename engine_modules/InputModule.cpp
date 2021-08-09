#include "InputModule.h"

InputModule::InputModule(EngineCore* core) :
	Core(core) {
}

void InputModule::handle_input(int key, int scancode, int action, int mods) {
	/* TO-DO: Implement input handling as a Publisher/Subscriber model */
	/* PLACEHOLDER: */
	// 1. Hash the key, scancode, action, mods
	// 2. Access the keymap and execute the action
	// m_keymap.find(hash)->second();
}

void InputModule::subscribe(int key, int scancode, int action, int mods) {
	// 1. Insert function as m_keymap index
}