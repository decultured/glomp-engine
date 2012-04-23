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
public:
	bool is_polar;

	float x, y;
	float rotation;
	float width, height;
	float tx, ty, tw, th;
	float r, g, b, a;
	float center_x, center_y;
	float scale_x, scale_y;

	Object2d();
	virtual ~Object2d();

	void set_texture_id(GLuint t_id) {texture_id = t_id;}
	GLuint get_texture_id() {return texture_id;}

	void translate(float x, float y) {
		this->x += x;
		this->y += y;
	}
	void rotate(float deg) {
		this->rotation += deg;
	}
	void scale(float x, float y) {
		this->width *= width;
		this->height *= height;
	}

	void update(float seconds);
	void render();

	void apply_transform();
	void draw();
	void remove_transform();
};

} /* namespace graphics */
} /* namespace glomp */
#endif /* OBJECT2D_H_ */
