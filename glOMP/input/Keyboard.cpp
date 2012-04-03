/*
 * Keyboard.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: jgraves
 */

#include "Keyboard.h"
#include <GL/glfw.h>

namespace glomp {

Keyboard::Keyboard() {
	// TODO Auto-generated constructor stub

}

Keyboard::~Keyboard() {
	// TODO Auto-generated destructor stub
}

int Keyboard::keyState(int key) {
	return glfwGetKey(key);
}

} /* namespace glomp */
