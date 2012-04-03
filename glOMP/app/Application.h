/*
 * Application.h
 *
 *  Created on: Apr 1, 2012
 *      Author: jgraves
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

namespace glomp {

class Application {
private:
	int pixel_width;
	int pixel_height;

public:
	Application();
	virtual ~Application();

	int width() {return pixel_width;}
	int height() {return pixel_height;}

	bool resize(int width, int height, bool fullscreen);
};

} /* namespace glomp */
#endif /* APPLICATION_H_ */
