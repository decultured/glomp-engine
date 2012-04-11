/*
 * AppBinding.h
 *
 *  Created on: Apr 10, 2012
 *      Author: jgraves
 */

#ifndef APPBINDING_H_
#define APPBINDING_H_

namespace glomp {
namespace app {
	static int omp_window_init(lua_State *L);
	static int omp_window_resize(lua_State *L);
}
} /* namespace glomp */
#endif /* APPBINDING_H_ */
