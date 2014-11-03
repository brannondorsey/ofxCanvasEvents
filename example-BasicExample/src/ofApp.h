#pragma once

#include "ofMain.h"
#include "ofxCanvasEvents.h"

class ofApp : public ofBaseApp{

	public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void gotMessage(ofMessage msg);
    void dragEvent(ofDragInfo dragInfo);
    
    // Pointer Events
//    void onPointerUp(ofx::PointerEventArgs& evt);
//    void onPointerDown(ofx::PointerEventArgs& evt);
//    void onPointerMove(ofx::PointerEventArgs& evt);
//    void onPointerCancel(ofx::PointerEventArgs& evt);
//    
//    // Gesture Events
//    void onPointerDoublePress(ofx::PointerEventArgs& evt);
//    void onPointerPressAndHold(ofx::PointerEventArgs& evt);
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    std::string message;
    ofx::CanvasEvents canvasEvents;
		
};
