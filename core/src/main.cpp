#include "testApp.h"
#include "ofAppGlutWindow.h"

#include <iostream>
#include <string>

#include "platform.h"
#include "util/logging.h"
#include <unistd.h>

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

glomp::util::Logger logger;

void report_errors(lua_State *L, int status)
{
    if ( status!=0 ) {
        logger.log(lua_tostring(L, -1));
        
        std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // remove error message
    }
}

static int l_print(lua_State* L) {
    int nargs = lua_gettop(L);
    
    for (int i=1; i <= nargs; i++) {
        if (lua_isstring(L, i)) {
            logger.log(lua_tostring(L, i));
        }
        else {
            /* Do something with non-strings? */
        }
    }
    
    return 0;
}

static const struct luaL_reg printlib [] = {
    {"print", l_print},
    {NULL, NULL}
};

extern int luaopen_luaprintlib(lua_State *L)
{
    lua_getglobal(L, "_G");
    luaL_register(L, NULL, printlib);
    lua_pop(L, 1);
}

int main(int argc, char** argv){
    platform_init();
    logger.log("Program started");
    lua_State *L = lua_open();
    luaL_openlibs(L);
    luaopen_luaprintlib(L);
    
    const char* file = "data";
    std::string data_folder;
    std::string filename;
    
    platform_builtin_file_path(data_folder, file);

    filename = data_folder + "/main.lua";
    
    int s = luaL_loadfile(L, filename.c_str());
    
    if ( s==0 ) {
        // execute Lua program
        s = lua_pcall(L, 0, LUA_MULTRET, 0);
    }
    
    
    report_errors(L, s);
    logger.log("running");
    logger.print_to_file("/Users/decultured/development/game_dev/of_0071_osx_release/apps/myApps/glOMP/bin/logs.txt");

	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
    
    lua_close(L);
    
    sleep(1000);
    return 0;
}