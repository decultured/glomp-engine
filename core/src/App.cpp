#include "App.h"
#include "platform.h"

void App::setup(){
    ofBackground(54, 54, 54, 255);
    ofTrueTypeFont::setGlobalDpi(72);

    logger.capture_iostream();
    platform_init();
    lua_wrap.init();
    
    log_file.open("/Users/decultured/development/game_dev/of_0071_osx_release/apps/myApps/glOMP/bin/log.txt");

    platform_builtin_file_path(internal_data_folder, "data");
    ofSetDataPathRoot(internal_data_folder + "/");
    external_data_folder = "/Users/decultured/development/game_dev/of_0071_osx_release/apps/myApps/glOMP/bin/";
    std::cout << ofToDataPath("Inconsolata-Regular.ttf");

    console_font.loadFont("AnonymousPro-Bold.ttf", 18, true, true);
	console_font.setLineHeight(18.0f);
	console_font.setLetterSpacing(1.037);
    log_line.set_font(&console_font);
    log_line.position(10, 20);
    root_graphic.add_child(&log_line);

    lua_wrap.load_file(ofToDataPath("main.lua").c_str());
}

void App::exit() {
    lua_wrap.shutdown();
    logger.release_iostream();
    log_file.flush();
    log_file.close();
}

void App::update(){

    if (logger.get_buffer().length()) {
        lua_wrap.print(logger.get_buffer().c_str());
        log_line.set_text(logger.get_buffer().c_str());
        log_file << logger.get_buffer();
        logger.clear();
    }
}

void App::draw(){
    ofBackgroundHex(0x042E2A);
    ofSetHexColor(0x67E09D);
    
    root_graphic.Render();
//    console_font.drawString(console_output, 10, 25);
}

void App::keyPressed(int key){
    lua_wrap.keyPressed(key);
}

void App::keyReleased(int key){
    lua_wrap.keyReleased(key);
}

void App::mouseMoved(int x, int y){
    lua_wrap.mouseMoved(x, y);
}

void App::mouseDragged(int x, int y, int button){
    lua_wrap.mouseDragged(x, y, button);
}

void App::mousePressed(int x, int y, int button){
    lua_wrap.mousePressed(x, y, button);
}

void App::mouseReleased(int x, int y, int button){
    lua_wrap.mouseReleased(x, y, button);
}

void App::windowResized(int w, int h){
    lua_wrap.windowResized(w, h);
}

void App::gotMessage(ofMessage msg){

}

void App::dragEvent(ofDragInfo dragInfo){ 

}