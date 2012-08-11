#include "App.h"
#include "platform.h"

void App::setup(){
    glOMP::platform_init();
    glOMP::platform_builtin_file_path(internal_data_folder, "data");

    ofSetDataPathRoot(internal_data_folder + "/");

    lua_app.init();
    lua_app.set_lua_path(ofToDataPath("lua/", true).c_str());
    lua_app.load_file(ofToDataPath("lua/app_main.lua").c_str());

    game_thread.startThread(true, true);
    ofResetElapsedTimeCounter();
    start_time_micros = ofGetSystemTimeMicros();
}

void App::exit() {
    lua_app.shutdown();
    game_thread.waitForThread(true);
    game_thread.stopThread();
}

void App::update(){
    static int mode = 0;
        
    micros = ofGetSystemTimeMicros();
    elapsed = micros - start_time_micros;

    if (elapsed < 10000) {
        ofSleepMillis(10);
        micros = ofGetSystemTimeMicros();
        elapsed = micros - start_time_micros;
    }
    
    start_time_micros = micros;

    lua_app.update(elapsed * 0.000001);
}

void App::draw(){
    lua_app.draw();
}

void App::keyPressed(int key){
    lua_app.keyPressed(key);
}

void App::keyReleased(int key){
    lua_app.keyReleased(key);
}

void App::mouseMoved(int x, int y){
    lua_app.mouseMoved(x, y);
}

void App::mouseDragged(int x, int y, int button){
    lua_app.mouseDragged(x, y, button);
}

void App::mousePressed(int x, int y, int button){
    lua_app.mousePressed(x, y, button);
}

void App::mouseReleased(int x, int y, int button){
    lua_app.mouseReleased(x, y, button);
}

void App::windowResized(int w, int h){
    lua_app.windowResized(w, h);
}

void App::gotMessage(ofMessage msg){
    lua_app.gotMessage(msg);
}

void App::dragEvent(ofDragInfo dragInfo){
    lua_app.drag_event(dragInfo);
}

void App::windowEntry(int state) {
    lua_app.windowEntry(state);
}