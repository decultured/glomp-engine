/*
 * DefaultStage.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: jgraves
 */

#include "DefaultStage.h"
#include <cstdlib>
#include <GL/glfw.h>

namespace glomp {

DefaultStage::DefaultStage() {
	// TODO Auto-generated constructor stub

}

DefaultStage::~DefaultStage() {
	// TODO Auto-generated destructor stub
}

int DefaultStage::run(float time) {
	float r = rand() % 1000 * 0.001;
	float g = rand() % 1000 * 0.001;
	float b = rand() % 1000 * 0.001;

	glClearColor(r, g, b, 1.0);

	return 1;
}

} /* namespace glomp */
