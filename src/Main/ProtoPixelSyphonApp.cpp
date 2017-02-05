/*
 *  ProtoPixelSyphonApp.cpp
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */

#include "AppManager.h"

#include "ProtoPixelSyphonApp.h"

//--------------------------------------------------------------
void ProtoPixelSyphonApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::draw(){
    AppManager::getInstance().draw();
}

void ProtoPixelSyphonApp::exit()
{
    ofLogNotice() <<"ProtoPixelSyphonApp::exit";

}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ProtoPixelSyphonApp::dragEvent(ofDragInfo dragInfo){

}
