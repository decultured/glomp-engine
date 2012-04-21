/*
 * Image.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#include "Image.h"
#include <iostream>

namespace glomp {
namespace graphics {

Image::Image() {
	// TODO Auto-generated constructor stub

}

Image::~Image() {
	// TODO Auto-generated destructor stub
}

void Image::load(const char *filename) {

	// allocate a texture name
	glGenTextures( 1, &texture_id);

	// select our current texture
	glBindTexture( GL_TEXTURE_2D, texture_id);

	// Load texture from file, and build all mipmap levels
	glfwLoadTexture2D(filename, GLFW_BUILD_MIPMAPS_BIT );

//	// Use trilinear interpolation for minification
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	// Use bilinear interpolation for magnification
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// the texture wraps over at the edges (repeat)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	// Enable texturing
	glEnable( GL_TEXTURE_2D );
}

void Image::draw() {
	glBindTexture( GL_TEXTURE_2D, texture_id);

	glBegin( GL_QUADS );
	glTexCoord2d(0.0,0.0); glVertex2d(0.0,0.0);
	glTexCoord2d(1.0,0.0); glVertex2d(1.0,0.0);
	glTexCoord2d(1.0,1.0); glVertex2d(1.0,1.0);
	glTexCoord2d(0.0,1.0); glVertex2d(0.0,1.0);
	glEnd();
}

} /* namespace graphics */
} /* namespace glomp */
