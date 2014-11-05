// =============================================================================
//
// Copyright (c) 2014 Brannon Dorsey <http://brannondorsey.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================

#include "ofxCanvasEvents.h"

namespace ofx {
std::string CanvasEvents::EVENT_METHOD_PREFIX = "HTMLCanvasEvent-";
    
CanvasEvents::CanvasEvents(HTTP::BasicJSONRPCServerSettings settings):
_bMouseOver(false),
_bInterpolateMousePos(true),
_canvasWidth(0),
_canvasHeight(0)
{
    
    _server = HTTP::BasicJSONRPCServer::makeShared(settings);
    
    _server->registerMethod(EVENT_METHOD_PREFIX + "mouseOver",
                            "Returns a random chunk of text to the client.",
                            this,
                            &CanvasEvents::_notifyCanvasEventRecieved);
    
    _server->registerMethod(EVENT_METHOD_PREFIX + "mouseOut",
                            "Returns a random chunk of text to the client.",
                            this,
                            &CanvasEvents::_notifyCanvasEventRecieved);
    
    _server->registerMethod(EVENT_METHOD_PREFIX + "keyPressed",
                           "Returns a random chunk of text to the client.",
                           this,
                           &CanvasEvents::_notifyCanvasEventRecieved);
    
    _server->registerMethod(EVENT_METHOD_PREFIX + "keyReleased",
                           "Sets text from the user.",
                           this,
                           &CanvasEvents::_notifyCanvasEventRecieved);
    
    _server->registerMethod(EVENT_METHOD_PREFIX + "mousePressed",
                           "Send a JSONRPC Ping Notification",
                           this,
                           &CanvasEvents::_notifyCanvasEventRecieved);
    
    _server->registerMethod(EVENT_METHOD_PREFIX + "mouseReleased",
                           "Send a JSONRPC Ping Notification",
                           this,
                           &CanvasEvents::_notifyCanvasEventRecieved);
    
    _server->registerMethod(EVENT_METHOD_PREFIX + "mouseMoved",
                           "Send a JSONRPC Ping Notification",
                           this,
                           &CanvasEvents::_notifyCanvasEventRecieved);
    
    _server->registerMethod(EVENT_METHOD_PREFIX + "mouseDragged",
                           "Send a JSONRPC Ping Notification",
                           this,
                           &CanvasEvents::_notifyCanvasEventRecieved);
    
    _server->registerMethod(EVENT_METHOD_PREFIX + "canvasSize",
                            "Send a JSONRPC Ping Notification",
                            this,
                            &CanvasEvents::_canvasSize);
    
    // Start the server.
    _server->start();
    
}

CanvasEvents::~CanvasEvents()
{
        
}
    
void CanvasEvents::setInterpolateMousePos(bool b)
{
    _bInterpolateMousePos = b;
}
    
bool CanvasEvents::isMouseOver() const
{
    return _bMouseOver;
}
    
bool CanvasEvents::getInterpolateMousePos() const
{
    return _bInterpolateMousePos;
}
    
HTTP::BasicJSONRPCServer::SharedPtr CanvasEvents::getServer()
{
    return _server;
}
    
void CanvasEvents::_canvasSize(ofx::JSONRPC::MethodArgs& args)
{
        
    _canvasWidth = args.params["width"].asInt();
    _canvasHeight = args.params["height"].asInt();
    string aspect = args.params["aspect"].asString();

    float appAspect = (float) ofGetWidth()/ (float) ofGetHeight();
    std::stringstream s;
    s.precision(3);
    s << appAspect;
    
    if (_canvasWidth != ofGetWidth() && _canvasHeight != ofGetHeight()) {
        ofLogNotice() << "ofxCanvas: The size of the HTML canvas does not match"
        << " the size of the app window."
        << " Mouse and touch positions will be interpolated.";
    }

    if (aspect != s.str()) {
        ofLogNotice() << "ofxCanvas: The aspect ratio of the HTML canvas does not"
        << " match the aspect ratio of the app window."
        << " Mouse and touch positions will be interpolated.";
    }
}
    
void CanvasEvents::_interpolateMouse(int& x, int& y, const int& width, const int& height) {
 
    if (width != ofGetWidth()) {
        x = ofMap(x, 0, width, 0, ofGetWidth());
    }
    
    if (height != ofGetHeight()) {
        y = ofMap(y, 0, height, 0, ofGetHeight());
    }
}
    
void CanvasEvents::_notifyCanvasEventRecieved(ofx::JSONRPC::MethodArgs& args)
{
    if (!args.params["type"].empty()) {
        
        std::string type = args.params["type"].asString();

        if (type == "mouseOver") {
            _bMouseOver = true;
        }
        else if (type == "mouseOut")
        {
            _bMouseOver = false;
        }
        else if (type == "keyPressed")
        {

            int keycode = args.params["keycode"].asInt();
            
            ofLogVerbose() << "ofxCanvasEvents: keyPressed event recieved";
            ofNotifyKeyPressed(-1, keycode, -1, -1);
        }
        else if (type == "keyReleased")
        {
            
            int keycode = args.params["keycode"].asInt();
            
            ofLogVerbose() << "ofxCanvasEvents: keyReleased event recieved";
            ofNotifyKeyReleased(-1, keycode, -1, -1);
        }
        else if (type == "mousePressed")
        {

            int button = args.params["button"].asInt();
            int x = args.params["x"].asInt();
            int y = args.params["y"].asInt();
            int width = args.params["w"].asInt();
            int height = args.params["h"].asInt();
            
            if (getInterpolateMousePos())
            {
                _interpolateMouse(x, y, width, height);
            }
            
            ofLogVerbose() << "ofxCanvasEvents: mousePressed event recieved";
            ofNotifyMousePressed(x, y, button);
        }
        else if (type == "mouseReleased")
        {
            
            int button = args.params["button"].asInt();
            int x = args.params["x"].asInt();
            int y = args.params["y"].asInt();
            int width = args.params["w"].asInt();
            int height = args.params["h"].asInt();
            
            if (getInterpolateMousePos())
            {
                _interpolateMouse(x, y, width, height);
            }
            
            ofLogVerbose() << "ofxCanvasEvents: mouseReleased event recieved";
            
//            ofMouseEventArgs args;
//            args.type = ofMouseEventArgs::Released;
//            args.x = x;
//            args.y = y;
//            args.button = button;
//            
//            ofNotifyMouseEvent(args);
            ofNotifyMouseReleased(x, y, button);
        }
        else if (type == "mouseMoved")
        {

            int x = args.params["x"].asInt();
            int y = args.params["y"].asInt();
            int width = args.params["w"].asInt();
            int height = args.params["h"].asInt();
            
            if (getInterpolateMousePos())
            {
                _interpolateMouse(x, y, width, height);
            }
            
            ofLogVerbose() << "ofxCanvasEvents: mouseMoved event recieved";
            ofNotifyMouseMoved(x, y);
        }
        else if (type == "mouseDragged")
        {
            
            int button = args.params["button"].asInt();
            int x = args.params["x"].asInt();
            int y = args.params["y"].asInt();
            int width = args.params["w"].asInt();
            int height = args.params["h"].asInt();
            
            if (getInterpolateMousePos())
            {
                _interpolateMouse(x, y, width, height);
            }
            
            ofLogVerbose() << "ofxCanvasEvents: mouseDragged event recieved";
            ofNotifyMouseDragged(x, y, button);
        }
    }
}
    
};

