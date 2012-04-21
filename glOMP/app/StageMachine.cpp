/*
 * StageMachine.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: jgraves
 */

#include "Stage.h"
#include "DefaultStage.h"
#include "StageMachine.h"
#include <GL/glfw.h>
#include <gl.h>

namespace glomp {

StageMachine::StageMachine() {
	// TODO Auto-generated constructor stub
	default_stage = new DefaultStage();
	current_stage = default_stage;
}

StageMachine::~StageMachine() {
	delete default_stage;
}

int StageMachine::run() {
    if (!current_stage)
        return 0;

    timer.start();

    float elapsed_time;
    int transition_code = 1;
    while (true) {
    	glClear(GL_COLOR_BUFFER_BIT);
    	elapsed_time = timer.elapsed();
        transition_code = current_stage->run(elapsed_time);
        if (!transition_function(transition_code))
            break;
//        if (keyboard.keyState( GLFW_KEY_ESC ) || !glfwGetWindowParam( GLFW_OPENED ))
//        	break;
        glfwSwapBuffers();
    };

    return 1;
}

int StageMachine::transition_function(int transition_code) {
	return 1;
}

} /* namespace glomp */
