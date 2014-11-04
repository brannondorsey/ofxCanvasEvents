#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    message = "";
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapStringHighlight(message, 15, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << "keyPressed Fired" << endl;
    message = "keyPressed: " + ofToString(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    cout << "keyReleased Fired" << endl;
    message = "keyReleased: " + ofToString(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    cout << "mouseMoved Fired" << endl;
    message = "mouseMoved: " + ofToString(x) + ", " + ofToString(y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    cout << "mouseDragged Fired" << endl;
    message = "mouseDragged: " + ofToString(x) + ", " + ofToString(y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    cout << "mousePressed Fired" << endl;
//    message = "mousePressed: " + ofToString(x) + ", " + ofToString(y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    cout << "mouseReleased Fired" << endl;
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
