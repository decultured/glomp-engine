#include "App.h"
#include "platform.h"

void App::setup(){
    ofBackground(54, 54, 54, 255);
    ofTrueTypeFont::setGlobalDpi(72);

    int test = OF_KEY_BACKSPACE;
    platform_init();
    
    platform_builtin_file_path(internal_data_folder, "data");
    ofSetDataPathRoot(internal_data_folder + "/");

    console_font.loadFont("assets/fonts/AnonymousPro-Bold.ttf", 18, true, true);
	console_font.setLineHeight(18.0f);
	console_font.setLetterSpacing(1.037);
    log_line.set_font(&console_font);
    log_line.position(10, 758);
    root_graphic.add_child(&log_line);

    ofAddListener(TextViewEvent::events, this, &App::textViewEvent);

    lua_app.init();
    lua_app.set_lua_path(ofToDataPath("lua/", true).c_str());
    lua_app.load_file(ofToDataPath("lua/app_main.lua").c_str());

    game_thread.startThread(true, true);
}

void App::exit() {
    game_thread.stopThread();
    lua_app.shutdown();
}

void App::update(){
    ofSleepMillis(10);
    lua_app.update();
}

void App::draw(){
    ofBackgroundHex(0x042E2A);
    
    
    root_graphic.Render();
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
    log_line.position(10, ofGetHeight() - 10 - log_line.height());
    root_graphic.size(ofGetWidth(), ofGetHeight());
    lua_app.windowResized(w, h);
}

void App::gotMessage(ofMessage msg){
    std::cout << msg.message;
//    lua_app.gotMessage(msg);
}

void App::textViewEvent(TextViewEvent &args) {
    glomp::Text *new_texts;
    
    if (!texts.count(args.name)) {
        std::cout << args.name << std::endl;
        texts[args.name] = new_texts = new glomp::Text();
        new_texts->set_font(&console_font);
        root_graphic.add_child(new_texts);
    } else {
        new_texts = texts[args.name];
    }
    
    new_texts->position(args.x, args.y);
    new_texts->set_text(args.text.c_str());
}

void App::dragEvent(ofDragInfo dragInfo){ 

}