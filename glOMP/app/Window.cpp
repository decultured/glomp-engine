/*
 * Window.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jgraves
 */

#include "Window.h"
#include <GL/glfw.h>
#include <gl.h>
#include <iostream>

namespace glomp {
namespace app {

Window::Window() {}

Window::~Window() {}

int Window::init(int width, int height, int bpp, bool fullscreen) {
	this->pixel_height = height;
	this->pixel_width = width;

	if(!glfwInit()) {
		return -1;
	}

	glfwOpenWindow(pixel_width, pixel_height, 0,0,0,0,0,0, GLFW_WINDOW );

	glfwSwapInterval(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    glfwSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::set_clear_color(float r, float g, float b) {
	glClearColor(r, g, b, 1.0);
}

void Window::start_2d_projection(float width, float height, float x, float y) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Window::stop_2d_projection() {
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void Window::translate2d(float x, float y) {


}

int Window::shutdown() {
	glfwTerminate();
	return 1;
}

} /* namespace app */
} /* namespace glomp */
