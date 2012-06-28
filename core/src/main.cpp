#include "App.h"
#include "ofAppGlutWindow.h"

//#include <iostream>
//#include <string>
//
//#include "platform.h"
//#include "util/logging.h"
//#include <unistd.h>
//
//extern "C" {
//    #include "lua.h"
//    #include "lualib.h"
//    #include "lauxlib.h"
//}


int main(int argc, char** argv){
//    luaopen_luaprintlib(L);

	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new App()); // start the app

    return 0;
}