/*
 * DefaultStage.h
 *
 *  Created on: Apr 2, 2012
 *      Author: jgraves
 */

#ifndef DEFAULTSTAGE_H_
#define DEFAULTSTAGE_H_

#include "Stage.h"

namespace glomp {

class DefaultStage : public Stage {
public:
	DefaultStage();
	~DefaultStage();

    int run(float time);
};

} /* namespace glomp */
#endif /* DEFAULTSTAGE_H_ */
