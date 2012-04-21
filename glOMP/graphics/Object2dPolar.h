/*
 * Object2dPolar.h
 *
 *  Created on: Apr 21, 2012
 *      Author: jgraves
 */

#ifndef OBJECT2DPOLAR_H_
#define OBJECT2DPOLAR_H_

// To resolve highlighting bug in eclipse, I explicitly include the framework folders here.
// TODO : find a better fix for this!
#include <GL/glfw.h>
#include <gl.h>

namespace glomp {
namespace graphics {

class Object2dPolar {
private:
	GLuint texture_id;
public:
	float angle;
	float distance;

	float rotation;

	float width;
	float height;

	Object2dPolar();
	virtual ~Object2dPolar();

	void set_texture_id(GLuint t_id) {texture_id = t_id;}

	void translate(float angle, float distance) {
		this->angle += angle;
		this->distance += distance;
	}
	void rotate(float deg) {
		this->rotation += deg;
	}
	void scale(float x, float y) {
		this->width = width;
		this->height = height;
	}

	void update(float seconds);
	void render();
};

} /* namespace graphics */
} /* namespace glomp */
#endif /* OBJECT2DPOLAR_H_ */
