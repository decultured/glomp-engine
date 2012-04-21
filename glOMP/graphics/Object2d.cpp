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

	rotation = 0.0f;

	width = 64.0f;
	height = 64.0f;
}

Object2d::~Object2d() {}

void Object2d::update(float seconds) {
	if (rotation > 360.0f)
		rotation = fmod(rotation, 360.0f);
}

void Object2d::render() {
	glBindTexture( GL_TEXTURE_2D, texture_id);

	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);


	float h_w = width * 0.5f;
	float h_h = height * 0.5f;

	glBegin( GL_QUADS );
		glTexCoord2d(0.0,0.0);
		glVertex2d(-h_w, -h_h);

		glTexCoord2d(1.0,0.0);
		glVertex2d(h_w, -h_h);

		glTexCoord2d(1.0,1.0);
		glVertex2d(h_w, h_h);

		glTexCoord2d(0.0,1.0);
		glVertex2d(-h_w, h_h);
	glEnd();

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
