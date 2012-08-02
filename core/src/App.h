#pragma once

#include <string>

#include "ofMain.h"
#include "lua/lua_wrapper.h"
#include "util/logging.h"

#include "text_view_event.h"
#include "lua_worker_thread.h"
#include "lua_app.h"
#include "graphic.h"
#include "text.h"
#include <map>

#include "poco/TimedNotificationQueue.h"

#if defined __GNUC__ || defined __APPLE__
#include <ext/hash_map>
#else
#include <hash_map>
#endif

class App : public ofBaseApp{
private:
    glomp::util::Logger logger;
    
    std::string internal_data_folder;
    std::string external_data_folder;
    
    ofTrueTypeFont	console_font;
    std::string console_output;
    
    glomp::Graphic root_graphic;
    glomp::Text log_line;

    Poco::TimedNotificationQueue main_queue;

    glomp::WorkerThread game_thread;
    glomp::LuaApp lua_app;
    
    std::map<string, glomp::Text *> texts;

    unsigned long micros;
    unsigned long elapsed;
    unsigned long start_time_micros;
    double frame_time;
public:
    App() : game_thread(main_queue) {}

    void setup();
    void exit();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void windowEntry(int state);
    
    void textViewEvent(TextViewEvent &args);
};
