#include "testApp.h"
#include "ofAppGlutWindow.h"

#include <iostream>
#include <string>

#include "platform.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

void report_errors(lua_State *L, int status)
{
    if ( status!=0 ) {
        std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // remove error message
    }
}

int main(int argc, char** argv){
    platform_init();
    
    lua_State *L = lua_open();
    
    luaL_openlibs(L);
    
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

	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
    
    lua_close(L);
    std::cerr << std::endl;
    return 0;
}