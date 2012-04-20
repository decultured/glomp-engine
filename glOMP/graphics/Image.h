/*
 * Image.h
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#ifndef IMAGE_H_
#define IMAGE_H_

namespace glomp {
namespace graphics {

class Image {
public:
	Image();
	virtual ~Image();

	void load(const char *filename);
};

} /* namespace graphics */
} /* namespace glomp */
#endif /* IMAGE_H_ */
