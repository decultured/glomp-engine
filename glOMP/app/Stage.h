/*
 * Stage.h
 *
 *  Created on: Apr 2, 2012
 *      Author: jgraves
 */

#ifndef STAGE_H_
#define STAGE_H_

namespace glomp {

class Stage {
public:
	Stage();
	virtual ~Stage();

    virtual int enter_state() {return 1;}
    virtual int run(float time) = 0;
    virtual int leave_state() {return 1;}
};

} /* namespace glomp */
#endif /* STAGE_H_ */
