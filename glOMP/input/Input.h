/*
 * Input.h
 *
 *  Created on: Apr 17, 2012
 *      Author: jgraves
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <list>
#include <string>
#include <map>
#include <GL/glfw.h>
#include "InputTriggers.h"

#define KEY_UP			1
#define KEY_DOWN 		2
#define KEY_IS_DOWN 	3
#define KEY_IS_UP		4
#define MOUSE_UP		10
#define MOUSE_DOWN		11
#define MOUSE_IS_UP		12
#define MOUSE_IS_DOWN	13
#define JOYSTICK_UP		20
#define JOYSTICK_DOWN	21
#define JOYSTICK_IS_UP	22
#define JOYSTICK_IS_DOWN 23

namespace glomp {
namespace input {

class InputListener {
private :
	std::string name;
public :
	InputListener(const char *name) {
		this->name = name;
	}
	virtual void trigger() = 0;
};


typedef std::multimap<std::string, InputTrigger *> TriggerMap;
typedef std::multimap<std::string, InputTrigger *>::iterator TriggerMapIter;

typedef std::multimap<std::string, InputListener *> ListenerMap;
typedef std::multimap<std::string, InputListener *>::iterator ListenerMapIter;


class Input {
private:
	TriggerMap triggers;
	ListenerMap listeners;

public:
	Input();
	virtual ~Input();

	bool key_state(int key_code);
	bool mouse_button_state(int mouse_button);

	void add_trigger(const char *action, InputTrigger *trigger);
	void add_listener(const char *action, InputListener *listener);

	void check_triggers();
	void trigger_listeners(const char *action);
};

}
} /* namespace glomp */
#endif /* INPUT_H_ */
