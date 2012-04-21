/*
 * Object2d.h
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#ifndef OBJECT2D_H_
#define OBJECT2D_H_

// To resolve highlighting bug in eclipse, I explicitly include the framework folders here.
// TODO : find a better fix for this!
#include <GL/glfw.h>
#include <gl.h>

namespace glomp {
namespace graphics {

class Object2d {
private:
	GLuint texture_id;

	float x;
	float y;

	float rotation;

	float width;
	float height;

public:
	Object2d();
	virtual ~Object2d();

	void set_texture_id(GLuint t_id) {texture_id = t_id;}

	void translate(float x, float y);
	void rotate(float rad);
	void scale(float rad);
	void size(float width, float height);

	void update(float seconds);
	void render();

};

} /* namespace graphics */
} /* namespace glomp */
#endif /* OBJECT2D_H_ */
