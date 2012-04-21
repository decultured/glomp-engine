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

	float r, g, b;

	bool fullscreen;
public:
	Window();
	virtual ~Window();

	int init(int width, int height, int bpp, bool fullscreen);
	int shutdown();

	int width() {return pixel_width;}
	int height() {return pixel_height;}

	bool resize(int width, int height, bool fullscreen);

	void update();

	void clear();
	void set_clear_color(float r, float g, float b);

	void start_2d_projection(float width, float height, float x, float y);
	void stop_2d_projection();
	void translate2d(float x, float y);
};

} /* namespace app */
} /* namespace glomp */
#endif /* Window_H_ */
