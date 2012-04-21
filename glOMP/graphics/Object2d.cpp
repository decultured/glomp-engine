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

	is_polar = false;
	rotation = 0.0f;

	width = 64.0f;
	height = 64.0f;

	center_x = 0.0f;
	center_y = 0.0f;
}

Object2d::~Object2d() {}

void Object2d::update(float seconds) {
	if (rotation > 360.0f)
		rotation = fmod(rotation, 360.0f);
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
}

void Object2d::draw() {
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

//void Object2d::circle() {
//	glPushMatrix();
//	glTranslatef(x, y, 0.0f);
//	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
//
//
//	float h_w = width * 0.5f;
//	float h_h = height * 0.5f;
//
//	int num = 10;
//
//	glBegin( GL_TRIANGLE_FAN );
//		glVertex2d(0.0, 0.0);
//
//		float angle = 0.0f
//		for (int i = 0; i < num; i++) {
//
//			glVertex2d(0.0, 0.0);
//
////			angle +=
//		}
//	glEnd();
//
//	glPopMatrix();
//}

} /* namespace graphics */
} /* namespace glomp */
