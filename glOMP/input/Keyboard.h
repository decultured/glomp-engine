/*
 * Keyboard.h
 *
 *  Created on: Apr 2, 2012
 *      Author: jgraves
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

namespace glomp {
namespace keyboard {

class Keyboard {
private:
	int keystates[];

public:
	Keyboard();
	virtual ~Keyboard();

	bool inputState(int);

	bool keyState(int);
};

}
} /* namespace glomp */
#endif /* KEYBOARD_H_ */
