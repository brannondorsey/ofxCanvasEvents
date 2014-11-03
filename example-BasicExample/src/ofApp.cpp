#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(255);

//    canvasEvents.registerEvents(this);
//    canvasEvents.registerEvents(this);

    // Launch a browser with the address of the server.
    ofLaunchBrowser(canvasEvents.getServer()->getURL());
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofNotifyMousePressed(150, 150, 1); // this never fires
    
    // neither does this
//    static ofMouseEventArgs mouseEventArgs;
//    
//    mouseEventArgs.x = 150;
//	mouseEventArgs.y = 150;
//	mouseEventArgs.button = 0;
//    mouseEventArgs.type = ofMouseEventArgs::Pressed;
//	ofNotifyEvent( ofEvents().mousePressed, mouseEventArgs);
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofDrawBitmapStringHighlight(message, 15, 30);
}

void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    message = "keyPressed: " + ofToString(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    message = "keyReleased: " + ofToString(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    message = "mouseMoved: " + ofToString(x) + ", " + ofToString(y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    message = "mouseDragged: " + ofToString(x) + ", " + ofToString(y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    message = "mousePressed: " + ofToString(x) + ", " + ofToString(y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    message = "mouseReleased: " + ofToString(x) + ", " + ofToString(y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//void ofApp::onPointerUp(ofx::PointerEventArgs& evt)
//{
//
//}
//
//void ofApp::onPointerDown(ofx::PointerEventArgs& evt)
//{
//
//}
//
//void ofApp::onPointerMove(ofx::PointerEventArgs& evt)
//{
//
//}
//
//void ofApp::onPointerCancel(ofx::PointerEventArgs& evt)
//{
//
//}
//
//// Gesture Events
//void ofApp::onPointerDoublePress(ofx::PointerEventArgs& evt)
//{
//
//}
//
//void ofApp::onPointerPressAndHold(ofx::PointerEventArgs& evt)
//{
//
//}

