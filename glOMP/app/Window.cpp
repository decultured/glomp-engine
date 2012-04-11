/*
 * Window.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jgraves
 */

#include "Window.h"
#include <GL/glfw.h>
#include <opengl.h>

namespace glomp {
namespace app {

Window::Window() {
	// TODO Auto-generated constructor stub

}

Window::~Window() {
	// TODO Auto-generated destructor stub
}

int Window::init(int width, int height, int bpp, bool fullscreen) {
	this->pixel_height = height;
	this->pixel_width = width;

	if(!glfwInit()) {
		return -1;
	}

	glfwOpenWindow(pixel_width, pixel_height, 0,0,0,0,0,0, GLFW_WINDOW );

	return 1;
}

int Window::shutdown() {
	glfwTerminate();
	return 1;
}

} /* namespace app */
} /* namespace glomp */
