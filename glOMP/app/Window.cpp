/*
 * Window.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jgraves
 */

#include "Window.h"
#include <GL/glfw.h>
#include <opengl.h>
#include <iostream>

namespace glomp {
namespace app {

Window::Window() {
	// TODO Auto-generated constructor stub
	std::cerr << "Window Created\n";
}

Window::~Window() {
	// TODO Auto-generated destructor stub
	std::cerr << "Window Destroyed\n";
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

bool Window::resize(int width, int height, bool fullscreen) {
	return false;
}

void Window::update() {
	glfwPollEvents();
	this->clear();
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers();
}

void Window::set_clear_color(float r, float g, float b) {
	glClearColor(r, g, b, 1.0);
}

int Window::shutdown() {
	glfwTerminate();
	return 1;
}

} /* namespace app */
} /* namespace glomp */
