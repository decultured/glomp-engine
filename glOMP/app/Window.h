/*
 * Window.h
 *
 *  Created on: Apr 1, 2012
 *      Author: jgraves
 */

#ifndef Window_H_
#define Window_H_

namespace glomp {
namespace app {

class Window {
private:
	int pixel_width;
	int pixel_height;

	bool fullscreen;
public:
	Window();
	virtual ~Window();

	int init(int width, int height, int bpp, bool fullscreen);
	int shutdown();

	int width() {return pixel_width;}
	int height() {return pixel_height;}

	bool resize(int width, int height, bool fullscreen);
};

} /* namespace app */
} /* namespace glomp */
#endif /* Window_H_ */
