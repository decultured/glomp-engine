/*
 * Image.h
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#ifndef IMAGE_H_
#define IMAGE_H_

// To resolve highlighting bug in eclipse, I explicitly include the framework folders here.
// TODO : find a better fix for this!
#include <GL/glfw.h>
#include <gl.h>

namespace glomp {
namespace graphics {

class Image {
private:
	GLuint texture_id;

public:
	Image();
	virtual ~Image();

	GLuint get_id() {return texture_id;}

	void load(const char *filename);
	void draw();
};

} /* namespace graphics */
} /* namespace glomp */
#endif /* IMAGE_H_ */