#include "App.h"
#include "platform.h"

void App::setup(){
    ofBackground(54, 54, 54, 255);
    ofTrueTypeFont::setGlobalDpi(72);

    int test = OF_KEY_BACKSPACE;
    logger.capture_iostream();
    platform_init();
    
    platform_builtin_file_path(internal_data_folder, "data");
    ofSetDataPathRoot(internal_data_folder + "/");

    console_font.loadFont("AnonymousPro-Bold.ttf", 18, true, true);
	console_font.setLineHeight(18.0f);
	console_font.setLetterSpacing(1.037);
    log_line.set_font(&console_font);
    log_line.position(10, 758);
    root_graphic.add_child(&log_line);

    ofAddListener(TextViewEvent::events, this, &App::textViewEvent);

    game_thread.startThread(true, true);
}

void App::exit() {
    game_thread.stopThread();
    logger.release_iostream();
}

void App::update(){
    if (logger.get_buffer().length()) {
        log_line.add_text(logger.get_buffer().c_str());
        logger.clear();
        log_line.position(10, ofGetHeight() - 10 - log_line.height());
    }
    ofSleepMillis(10);
}

void App::draw(){
    ofBackgroundHex(0x042E2A);
    
    
    root_graphic.Render();
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
    log_line.position(10, ofGetHeight() - 10 - log_line.height());
    root_graphic.size(ofGetWidth(), ofGetHeight());
}

void App::gotMessage(ofMessage msg){
    std::cout << msg.message;
}

void App::textViewEvent(TextViewEvent &args) {
    glomp::Text *new_texts;
    
    if (!texts.count(args.name)) {
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