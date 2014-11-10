#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofSetWindowShape(500, 350);
    
    ofSetLogLevel(OF_LOG_VERBOSE);

	// we add this listener before setting up so the initial circle resolution is correct
	circleResolution.addListener(this, &ofApp::circleResolutionChanged);
	ringButton.addListener(this,&ofApp::ringButtonPressed);
    
    gui = new ofxPanel();
    
	gui->setup(); // most of the time you don't need a name
	gui->add(filled.setup("fill", true));
	gui->add(radius.setup( "radius", 140, 10, 300 ));
	gui->add(center.setup("center",ofVec2f(ofGetWidth()*.5,ofGetHeight()*.5),ofVec2f(0,0),ofVec2f(ofGetWidth(),ofGetHeight())));
	gui->add(color.setup("color",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
	gui->add(circleResolution.setup("circle res", 5, 3, 90));
	gui->add(twoCircles.setup("two circles"));
	gui->add(ringButton.setup("ring"));
	gui->add(screenSize.setup("screen size", ""));
    
	bHide = true;
    bDrawing = false;
    
	ring.loadSound("ring.wav");
    
    ofx::HTTP::BasicIPVideoServerSettings settings;
    
    // Many other settings are available.
    settings.setPort(7890);
    
    // The default maximum number of client connections is 5.
    // settings.setMaxClientConnections(10);
    
    // Apply the settings.
    iPServer = ofx::HTTP::BasicIPVideoServer::makeShared(settings);
    
    // Start the server.
    iPServer->start();
    
#if !defined(TARGET_LINUX_ARM)
    // Launch a browser with the address of the server.
    ofLaunchBrowser(canvasEvents.getServer()->getURL());
#endif

    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    
	if( filled ){
		ofFill();
	}else{
		ofNoFill();
	}
    
	ofSetColor(color);
	if(twoCircles){
		ofCircle(center->x-radius*.5, center->y, radius );
		ofCircle(center->x+radius*.5, center->y, radius );
	}else{
		ofCircle((ofVec2f)center, radius );
	}
	
	// auto draw?
	// should the gui control hiding?
	if( bHide ){
		gui->draw();
	}
    
    if (bDrawing){
        
        ofSetColor(255, 0, 0);
//        ofCircle(mouse.x, mouse.y, 10);
        ofCircle(ofGetMouseX(), ofGetMouseY(), 10);
    }
    
    screenImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
    // This can be any kind of pixels.
    iPServer->send(screenImage.getPixelsRef());
}

//--------------------------------------------------------------
void ofApp::exit(){
    
	ringButton.removeListener(this,&ofApp::ringButtonPressed);
    delete gui;
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int & circleResolution){
	ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::ringButtonPressed(){
	ring.play();
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs& args){

}

//--------------------------------------------------------------
void ofApp::keyReleased(ofKeyEventArgs& args){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
//    ofMouseEventArgs args(ofMouseEventArgs::Moved, x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    mouse.set(x, y);
//    ofMouseEventArgs args(ofMouseEventArgs::Dragged, x, y, button);
//    gui->mouseDragged(args);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    bDrawing = true;
//    ofMouseEventArgs args(ofMouseEventArgs::Pressed, x, y, button);
//    gui->mousePressed(args);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    bDrawing = false;
//    ofMouseEventArgs args(ofMouseEventArgs::Released, x, y, button);
//    gui->mouseReleased(args);
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
