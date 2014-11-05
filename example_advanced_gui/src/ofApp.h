#pragma once

#include "ofMain.h"
#include "ofxHTTP.h"
#include "ofxCanvasEvents.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(ofKeyEventArgs& args);
		void keyReleased(ofKeyEventArgs& args);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void circleResolutionChanged(int & circleResolution);
        void ringButtonPressed();
        
        bool bHide;
        
        ofxFloatSlider radius;
        ofxColorSlider color;
        ofxVec2Slider center;
        ofxIntSlider circleResolution;
        ofxToggle filled;
        ofxButton twoCircles;
        ofxButton ringButton;
        ofxLabel screenSize;
        
        ofxPanel* gui;
        
        ofSoundPlayer ring;
    
        ofImage screenImage;
    
        ofx::HTTP::BasicIPVideoServer::SharedPtr iPServer;
        ofx::CanvasEvents canvasEvents;
};
