/*
 * Input.cpp
 *
 *  Created on: Apr 17, 2012
 *      Author: jgraves
 */

#include "Input.h"

namespace glomp {
namespace input {

Input::Input() {}

Input::~Input() {}

bool Input::key_state(int key_code) {
	return (glfwGetKey(key_code) == GLFW_PRESS);
}

bool Input::mouse_button_state(int mouse_button) {
	return (glfwGetMouseButton(mouse_button) == GLFW_PRESS);
}

void Input::add_trigger(const char *action, InputTrigger *trigger) {
	this->triggers.insert(std::pair<std::string, InputTrigger *>(action, trigger));
}

void Input::add_listener(const char *action, InputListener *listener) {
	this->listeners.insert(std::pair<std::string, InputListener *>(action, listener));
}

void Input::check_triggers() {
	TriggerMapIter trigger_iter;

	std::string last_key;
	bool was_found = false;
	for (trigger_iter = this->triggers.begin(); trigger_iter != this->triggers.end(); trigger_iter++) {
		if ((*trigger_iter).first != last_key) {
			last_key = (*trigger_iter).first;
			was_found = false;
		} else if (was_found) {
			continue;
		}

		if ((*trigger_iter).second->check(*this)) {
			this->trigger_listeners((*trigger_iter).first.c_str());
			was_found = true;
		}
	}
}

void Input::trigger_listeners(const char *action) {
	ListenerMapIter listener_iter;

	std::pair<ListenerMapIter, ListenerMapIter> range = this->listeners.equal_range(action);

	for (listener_iter = range.first; listener_iter != range.second; listener_iter++) {
		(*listener_iter).second->trigger();
	}
}

}
} /* namespace glomp */
