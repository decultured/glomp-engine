#include "App.h"
#include "ofAppGlutWindow.h"

int main(int argc, char** argv){

	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new App());

    return 0;
}