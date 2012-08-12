//
//  lua_util.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/11/12.
//
//

#ifndef glOMP_lua_util_h
#define glOMP_lua_util_h

extern "C" {
#include "lua.h"
#include "luaconf.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace glOMP {

    void register_metatable(lua_State *L, const char *metatable_name, const luaL_Reg *l) {
        luaL_newmetatable(L, metatable_name);
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        luaL_register(L, NULL, l);
    }

    void register_module(lua_State *L, const char *module_name, const luaL_Reg *l) {
        lua_getglobal(L, "glOMP");
        if (!lua_istable(L, -1)) {
            lua_pop(L, 1);
            lua_newtable(L);
        }
        
        lua_newtable(L);
        
        for (; l->name; l++) {
            lua_pushcclosure(L, l->func, 0);
            lua_setfield(L, -2, l->name);
            std::cout << l->name;
        }
        
        lua_setfield(L, -2, module_name);
        lua_setglobal(L, "glOMP");
        
        return 0;
    }
    
    void lua_print(lua_State * L, const char *message) {
        lua_getglobal(L, "print");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushstring(L, message);
        
        if (lua_pcall(L, 1, 0, 0) != 0) {
            // TODO: threadsafe logging
            // std::cout << "error calling lua print: %s\n" << lua_tostring(L, -1) << std::endl;
            return;
        }
    }
    
    void lua_print(lua_State * L, std::string &message) {
        lua_print(L, message.c_str());
    }
    
    void lua_report_errors(lua_State *L, const char *message)
    {
        std::ostringstream str_stream;
        str_stream << "Error: " << message << ":" << std::endl
        << "     " << lua_tostring(L, -1);
        
        lua_print(L, str_stream.str().c_str());
    }
    
    int lua_set_path(lua_State *L, const char* path)
    {
        std::string new_path;
        lua_getglobal(L, "package");
        lua_getfield(L, -1, "path"); // get field "path" from table at top of stack (-1)
        new_path = lua_tostring( L, -1 ); // grab path string from top of stack
        new_path = new_path + ";"; // do your path magic here
        new_path = new_path + path;
        new_path = new_path + "?.lua";
        lua_pop( L, 1 ); // get rid of the string on the stack we just pushed on line 5
        lua_pushstring( L, new_path.c_str()); // push the new one
        lua_setfield( L, -2, "path" ); // set the field "path" in table at -2 with value at top of stack
        lua_pop( L, 1 ); // get rid of package table from top of stack
        lua_pushstring(L, path);
        lua_setglobal(L, "LUA_PATH");
        return 0; // all done!
    }
    
    bool lua_load_file(lua_State *L, const char *filename) {
        // TODO : Change to direct lua dofile call?
        // Would have to wrap dofile from c at that point
        if (luaL_loadfile(L, filename) || lua_pcall(L, 0, LUA_MULTRET, 0)) {
            lua_pop(L, 1);
            return false;
        }
        return true;
    }

}

#endif
