//
//  game_thread.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 7/8/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "game_thread.h"

namespace glomp {

void GameThread::threadedFunction() {
    init();
        
    while(isThreadRunning()) {
        lua_wrap.__update();
        ofSleepMillis(10);
    }

    shutdown();
}

void GameThread::init() {
    lua_wrap.init();

    lua_wrap.set_lua_path(ofToDataPath("", true).c_str());
    lua_wrap.load_file(ofToDataPath("main.lua").c_str());
    
    ofAddListener(ofEvents().keyPressed, this, &GameThread::keyPressed);
    ofAddListener(ofEvents().keyReleased, this, &GameThread::keyReleased);
    ofAddListener(ofEvents().mouseMoved, this, &GameThread::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &GameThread::mouseDragged);
    ofAddListener(ofEvents().mousePressed, this, &GameThread::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &GameThread::mouseReleased);
    ofAddListener(ofEvents().windowResized, this, &GameThread::windowResized);
    //ofAddListener(ofEvents().messageEvent, this, &GameThread::gotMessage);
    ofRegisterGetMessages(this);
}

void GameThread::shutdown() {
    ofRemoveListener(ofEvents().keyPressed, this, &GameThread::keyPressed);
    ofRemoveListener(ofEvents().keyReleased, this, &GameThread::keyReleased);
    ofRemoveListener(ofEvents().mouseMoved, this, &GameThread::mouseMoved);
    ofRemoveListener(ofEvents().mouseDragged, this, &GameThread::mouseDragged);
    ofRemoveListener(ofEvents().mousePressed, this, &GameThread::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &GameThread::mouseReleased);
    ofRemoveListener(ofEvents().windowResized, this, &GameThread::windowResized);
    ofUnregisterGetMessages(this);

    lua_wrap.shutdown();
}

void GameThread::keyPressed(ofKeyEventArgs &args){
    lua_wrap.keyPressed(args.key);
}

void GameThread::keyReleased(ofKeyEventArgs &args){
    lua_wrap.keyReleased(args.key);
}

void GameThread::mouseMoved(ofMouseEventArgs &args){
    lua_wrap.mouseMoved(args.x, args.y);
}

void GameThread::mouseDragged(ofMouseEventArgs &args){
    lua_wrap.mouseDragged(args.x, args.y, args.button);
}

void GameThread::mousePressed(ofMouseEventArgs &args){
    lua_wrap.mousePressed(args.x, args.y, args.button);
}

void GameThread::mouseReleased(ofMouseEventArgs &args){
    lua_wrap.mouseReleased(args.x, args.y, args.button);
}

void GameThread::windowResized(ofResizeEventArgs &args){

}

void GameThread::gotMessage(ofMessage &msg){

}

}