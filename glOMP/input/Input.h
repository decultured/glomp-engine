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

namespace glomp {
namespace input {

class InputListener {
private :
public :
	virtual ~InputListener() {}
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
