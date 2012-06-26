#include "testApp.h"
#include "ofAppGlutWindow.h"

#include <iostream>
#include <dirent.h>

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
    lua_State *L = lua_open();
    
    luaL_openlibs(L);
    
    const char* file = "./main.lua";
    
    DIR *Dir;
    struct dirent *DirEntry;
    Dir = opendir("./data");
    
    while((DirEntry=readdir(Dir)))
    {
        cout << DirEntry->d_name << "\n";
    }
    
    std::cerr << "-- Loading file: " << file << std::endl;
    
    int s = luaL_loadfile(L, file);
    
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