/*
 * Object2d.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#include "Object2d.h"
#include <iostream>
#include <math.h>

namespace glomp {
namespace graphics {

Object2d::Object2d() {
	x = 64.0f;
	y = 64.0f;

	tx = 0.0;
	ty = 0.0;
	tw = 1.0;
	th = 1.0;

	r = 1.0;
	g = 1.0;
	b = 1.0;
	a = 1.0;

	is_polar = false;
	rotation = 0.0f;

	width = 64.0f;
	height = 64.0f;

	center_x = 0.0f;
	center_y = 0.0f;

	scale_x = 1.0f;
	scale_y = 1.0f;
}

Object2d::~Object2d() {}

void Object2d::update(float seconds) {
	if (is_polar && x > 360.0f)
		x = fmod (x, 360.0f);
	else if (is_polar && x < 0.0f)
		x = 360.0f + fmod (x, 360.0f);


	if (rotation > 360.0f)
		rotation = fmod(rotation, 360.0f);
	else if (rotation < 0.0f)
		rotation = 360.0f + fmod(rotation, 360.0f);
}

void Object2d::render() {
	this->apply_transform();
	this->draw();
	this->remove_transform();
}

void Object2d::apply_transform() {
	glPushMatrix();

	if (is_polar) {
		glRotatef(x, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, y, 0.0f);
	} else {
		glTranslatef(x, y, 0.0f);
	}
	glTranslatef(-center_x, -center_y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	glScalef(scale_x, scale_y, 1.0f);
}

void Object2d::draw() {
	glColor4f(r, g, b, a);
	glBindTexture( GL_TEXTURE_2D, texture_id);
	float h_w = width * 0.5f;
	float h_h = height * 0.5f;

	glBegin( GL_QUADS );
		glTexCoord2d(tx, ty);
		glVertex2d(-h_w, -h_h);

		glTexCoord2d(tw + tx, ty);
		glVertex2d(h_w, -h_h);

		glTexCoord2d(tw + tx, th + ty);
		glVertex2d(h_w, h_h);

		glTexCoord2d(tx, th + ty);
		glVertex2d(-h_w, h_h);
	glEnd();
}

void Object2d::remove_transform(){
	glPopMatrix();
}

} /* namespace graphics */
} /* namespace glomp */
