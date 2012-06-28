#pragma once

#include <string>
#include <fstream>

#include "ofMain.h"
#include "lua/lua_wrapper.h"
#include "util/logging.h"

class App : public ofBaseApp{
private:
    glomp::lua::LuaWrapper lua_wrap;
    glomp::util::Logger logger;
    
    std::string internal_data_folder;
    std::string external_data_folder;
    
    std::ofstream log_file;
    
public:
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
};
