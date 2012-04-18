/*
 * Keyboard.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: jgraves
 */

#include "Keyboard.h"
#include <GL/glfw.h>

namespace glomp {
namespace keyboard {

Keyboard::Keyboard() {}
Keyboard::~Keyboard() {}

bool Keyboard::keyState(int key) {
	return (glfwGetKey(key) == GLFW_PRESS);
}

}
} /* namespace glomp */
