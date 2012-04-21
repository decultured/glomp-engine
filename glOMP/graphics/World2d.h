/*
 * World2d.h
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#ifndef WORLD2D_H_
#define WORLD2D_H_

namespace glomp {
namespace graphics {

class World2d {
private:

	float x, y;
	float rotation;

public:
	World2d();
	virtual ~World2d();

	void identity();
	float translate(float x, float y);
	float rotate(float rad);
};

} /* namespace graphics */
} /* namespace glomp */
#endif /* WORLD2D_H_ */
