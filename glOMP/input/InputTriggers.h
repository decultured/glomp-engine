/*
 * InputTriggers.h
 *
 *  Created on: Apr 18, 2012
 *      Author: jgraves
 */

#ifndef INPUTTRIGGERS_H_
#define INPUTTRIGGERS_H_

#include <GL/glfw.h>

namespace glomp {
namespace input {

class Input;

class InputTrigger {
public:
	virtual ~InputTrigger() {}
	virtual bool check(Input &input) {
		return false;
	}
};

class KeyUpTrigger : public InputTrigger{
	int key_code;
	bool prev_state;
public:
	KeyUpTrigger(int key_code);
	bool check(Input &input);
};

class KeyDownTrigger : public InputTrigger{
	int key_code;
	bool prev_state;
public:
	KeyDownTrigger(int key_code);
	bool check(Input &input);
};

class KeyIsUpTrigger : public InputTrigger{
	int key_code;
public:
	KeyIsUpTrigger(int key_code);
	bool check(Input &input);
};

class KeyIsDownTrigger : public InputTrigger{
	int key_code;
public:
	KeyIsDownTrigger(int key_code);
	bool check(Input &input);
};

}
} /* namespace glomp */
#endif /* INPUTTRIGGERS_H_ */
