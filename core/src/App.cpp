#include "App.h"
#include "platform.h"

void App::setup(){
    platform_init();
    lua_wrap.init();
    
    platform_builtin_file_path(internal_data_folder, "data");
    external_data_folder = "/Users/decultured/development/game_dev/of_0071_osx_release/apps/myApps/glOMP/bin/";
    
    std::string temp = internal_data_folder + "/main.lua";
    lua_wrap.load_file(temp.c_str());
}

void App::exit() {
    lua_wrap.shutdown();
    logger.log("Shutting down");
//    logger.print_to_file(external_data_folder + "logs.txt");
}

void App::update(){

}

void App::draw(){

}

void App::keyPressed(int key){

}

void App::keyReleased(int key){

}

void App::mouseMoved(int x, int y){

}

void App::mouseDragged(int x, int y, int button){

}

void App::mousePressed(int x, int y, int button){

}

void App::mouseReleased(int x, int y, int button){

}

void App::windowResized(int w, int h){

}

void App::gotMessage(ofMessage msg){

}

void App::dragEvent(ofDragInfo dragInfo){ 

}