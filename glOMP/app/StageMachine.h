/*
 * StageMachine.h
 *
 *  Created on: Apr 2, 2012
 *      Author: jgraves
 */

#ifndef STAGEMACHINE_H_
#define STAGEMACHINE_H_

#include "../common/Timer.h"
#include "../input/Keyboard.h"

namespace glomp {
	class Stage;
	class DefaultStage;

class StageMachine {
private:
    DefaultStage *default_stage;

	Stage *current_stage;
    Timer timer;

    Keyboard keyboard;

public:
	StageMachine();
	virtual ~StageMachine();

    int run();
    int transition_function(int transition_code);

};

} /* namespace glomp */
#endif /* STAGEMACHINE_H_ */
