//
//  lua_app.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 7/1/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <cstdlib>
#include "lua_app.h"

namespace glomp {

static int l_terminate(lua_State* L) {
    std::exit(EXIT_SUCCESS);
    return 0;
}

static const struct luaL_reg glomp_app [] = {
    {"__glomp_terminate", l_terminate},
    {NULL, NULL}
};

extern int luaopen_app(lua_State *L) {
    lua_getglobal(L, "_G");
    luaL_register(L, NULL, glomp_app);
    lua_pop(L, 1);
}

}