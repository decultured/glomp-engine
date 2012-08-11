#include "App.h"
#include "platform.h"

void App::setup(){
    glOMP::platform_init();
    glOMP::platform_builtin_file_path(internal_data_folder, "data");

    ofSetDataPathRoot(internal_data_folder + "/");

    L = glOMP::lua_core_init();
    glOMP::lua_set_path(L, ofToDataPath("lua/", true).c_str());
    glOMP::lua_load_file(L, ofToDataPath("lua/app_main.lua").c_str());

    game_thread.startThread(true, true);
    ofResetElapsedTimeCounter();
    start_time_micros = ofGetSystemTimeMicros();
}

void App::exit() {
    if (L) {
        glOMP::lua_core_shutdown(L);
        L = NULL;
    }
    
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

    glOMP::lua_core_callback_update(L, elapsed * 0.000001);
}

void App::draw(){
    glOMP::lua_core_callback_draw(L);
}

void App::keyPressed(int key){
    glOMP::lua_core_callback_key_pressed(L, key);
}

void App::keyReleased(int key){
    glOMP::lua_core_callback_key_released(L, key);
}

void App::mouseMoved(int x, int y){
    glOMP::lua_core_callback_mouse_moved(L, x, y);
}

void App::mouseDragged(int x, int y, int button){
    glOMP::lua_core_callback_mouse_dragged(L, x, y, button);
}

void App::mousePressed(int x, int y, int button){
    glOMP::lua_core_callback_mouse_pressed(L, x, y, button);
}

void App::mouseReleased(int x, int y, int button){
    glOMP::lua_core_callback_mouse_released(L, x, y, button);
}

void App::windowResized(int w, int h){
    glOMP::lua_core_callback_window_resized(L, w, h);
}

void App::gotMessage(ofMessage msg){
    glOMP::lua_core_callback_got_message(L, msg);
}

void App::dragEvent(ofDragInfo dragInfo){
    glOMP::lua_core_callback_drag_event(L, dragInfo);
}

void App::windowEntry(int state) {
    glOMP::lua_core_callback_window_entry(L, state);
}