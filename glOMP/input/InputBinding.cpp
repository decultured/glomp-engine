/*
 * InputBinding.cpp
 *
 *  Created on: Apr 18, 2012
 *      Author: jgraves
 */

#include "InputBinding.h"
#include "Input.h"
#include <iostream>

namespace glomp {
namespace input {

#define glomp_checkinput(L, N) *(Input **)luaL_checkudata(L, N, "glomp.input")

class LuaInputListener : public InputListener {
private :
	lua_State *L;
	int resource;
public :
	LuaInputListener(lua_State *l, int resource) {
		this->L = l;
		this->resource = resource;
	}
	~LuaInputListener() {}
	void trigger() {
		lua_rawgeti(L, LUA_REGISTRYINDEX, resource);
		lua_pcall(L, 0, 0, 0);
	}
};

int glomp_input_new(lua_State *L) {
	Input **new_in = (Input **)lua_newuserdata(L, sizeof(Input *));
	luaL_getmetatable(L, "glomp.input");
	lua_setmetatable(L, -2);

	*new_in = new Input();

	return 1;
}

int glomp_input_gc(lua_State *L) {
	Input *in = glomp_checkinput(L, 1);
	delete in;
	return 0;
}

int glomp_input_key_state(lua_State *L) {
	Input *in = glomp_checkinput(L, 1);
	int key = luaL_checknumber(L, 2);
	lua_pushnumber(L, (in->key_state(key)) ? 1 : 0);
	return 1;
}

int glomp_input_mouse_button_state(lua_State *L) {
	Input *in = glomp_checkinput(L, 1);
	int button = luaL_checknumber(L, 2);
	lua_pushnumber(L, (in->mouse_button_state(button)) ? 1 : 0);

	return 1;
}

int glomp_input_add_trigger(lua_State *L) {
	Input *in = glomp_checkinput(L, 1);
	const char *action = luaL_checkstring(L, 2);
	const char *activity = luaL_checkstring(L, 3);
	int key = luaL_checknumber(L, 4);

	InputTrigger *new_trigger = 0;
	if (!strcmp(activity, "key_down")) {
		new_trigger = new KeyDownTrigger(key);
	} else if (!strcmp(activity, "key_up")) {
		new_trigger = new KeyUpTrigger(key);
	} else if (!strcmp(activity, "key_is_down")) {
		new_trigger = new KeyIsDownTrigger(key);
	} else if (!strcmp(activity, "key_is_up")) {
		new_trigger = new KeyIsUpTrigger(key);
	}

	if (new_trigger) {
		in->add_trigger(action, new_trigger);
	} else {
		std::cerr << "Unrecognized input action: " << activity << "\n";
	}

	return 0;
}

int glomp_input_add_listener(lua_State *L) {
	Input *in = glomp_checkinput(L, 1);

	const char *action = luaL_checkstring(L, 2);

	if (!lua_isfunction(L, 3)) {
		// TODO : Real errors
		std::cerr << "nope!";
		return 0;
	}

	lua_pushvalue(L, 3);
	int func = luaL_ref(L, LUA_REGISTRYINDEX);

	//	int key = luaL_checknumber(L, 3);
	LuaInputListener *new_listener = new LuaInputListener(L, func);
	in->add_listener(action, new_listener);
	return 0;
}

int glomp_input_update(lua_State *L) {
	Input *in = glomp_checkinput(L, 1);
	in->check_triggers();

	return 0;
}

static const struct luaL_Reg glomp_input_main [] = {
		{"new", glomp_input_new},
		{NULL, NULL}
};

static const struct luaL_Reg glomp_input_funcs [] = {
	{"get_key", glomp_input_key_state},
	{"get_mouse_button", glomp_input_mouse_button_state},
	{"bind", glomp_input_add_trigger},
	{"on", glomp_input_add_listener},
	{"update", glomp_input_update},
	{"__gc", glomp_input_gc},
	{NULL, NULL}
};

int luaopen_input (lua_State *L) {
	luaL_newmetatable(L, "glomp.input");

	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	luaL_setfuncs(L, glomp_input_funcs, 0);

	luaL_newlib(L, glomp_input_main);
	lua_setglobal(L, "input");
	return 1;
}

}
} /* namespace glomp */
