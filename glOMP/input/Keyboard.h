/*
 * Keyboard.h
 *
 *  Created on: Apr 2, 2012
 *      Author: jgraves
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

namespace glomp {

class Keyboard {
public:
	Keyboard();
	virtual ~Keyboard();

	int keyState(int);
};

} /* namespace glomp */
#endif /* KEYBOARD_H_ */
