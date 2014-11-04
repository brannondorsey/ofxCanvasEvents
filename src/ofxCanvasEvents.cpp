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
    
CanvasEvents::CanvasEvents(HTTP::BasicJSONRPCServerSettings settings)
{
    
    server = HTTP::BasicJSONRPCServer::makeShared(settings);
    
    server->registerMethod(EVENT_METHOD_PREFIX + "keyPressed",
                           "Returns a random chunk of text to the client.",
                           this,
                           &CanvasEvents::notifyCanvasEventRecieved);
    
    server->registerMethod(EVENT_METHOD_PREFIX + "keyReleased",
                           "Sets text from the user.",
                           this,
                           &CanvasEvents::notifyCanvasEventRecieved);
    
    server->registerMethod(EVENT_METHOD_PREFIX + "mousePressed",
                           "Send a JSONRPC Ping Notification",
                           this,
                           &CanvasEvents::notifyCanvasEventRecieved);
    
    server->registerMethod(EVENT_METHOD_PREFIX + "mouseReleased",
                           "Send a JSONRPC Ping Notification",
                           this,
                           &CanvasEvents::notifyCanvasEventRecieved);
    
    server->registerMethod(EVENT_METHOD_PREFIX + "mouseMoved",
                           "Send a JSONRPC Ping Notification",
                           this,
                           &CanvasEvents::notifyCanvasEventRecieved);
    
    server->registerMethod(EVENT_METHOD_PREFIX + "mouseDragged",
                           "Send a JSONRPC Ping Notification",
                           this,
                           &CanvasEvents::notifyCanvasEventRecieved);
    
//    server->registerMethod(EVENT_METHOD_PREFIX + "pointerup",
//                           "Send a JSONRPC Pong Notification",
//                           this,
//                           &CanvasEvents::notifyCanvasEventRecieved);
//    
//    server->registerMethod(EVENT_METHOD_PREFIX + "pointerover",
//                           "Returns a random chunk of text to the client.",
//                           this,
//                           &CanvasEvents::notifyCanvasEventRecieved);
//    
//    server->registerMethod(EVENT_METHOD_PREFIX + "pointerout",
//                           "Sets text from the user.",
//                           this,
//                           &CanvasEvents::notifyCanvasEventRecieved);
//    
//    server->registerMethod(EVENT_METHOD_PREFIX + "pointerenter",
//                           "Send a JSONRPC Ping Notification",
//                           this,
//                           &CanvasEvents::notifyCanvasEventRecieved);
//    
//    server->registerMethod(EVENT_METHOD_PREFIX + "pointerleave",
//                           "Send a JSONRPC Pong Notification",
//                           this,
//                           &CanvasEvents::notifyCanvasEventRecieved);
//    
//    server->registerMethod(EVENT_METHOD_PREFIX + "pointercancel",
//                           "Send a JSONRPC Pong Notification",
//                           this,
//                           &CanvasEvents::notifyCanvasEventRecieved);
    
    // Start the server.
    server->start();
    
}

CanvasEvents::~CanvasEvents()
{
        
}
    
void CanvasEvents::notifyCanvasEventRecieved(ofx::JSONRPC::MethodArgs& args)
{
    if (!args.params["type"].empty()) {
        
        std::string type = args.params["type"].asString();

        if (type == "keyPressed")
        {

            int key = args.params["key"].asInt();
            
            ofLogVerbose() << "ofxCanvasEvents: keyPressed event recieved";
            ofNotifyKeyPressed(key);
        }
        else if (type == "keyReleased")
        {
            
            int key = args.params["key"].asInt();
            
            ofLogVerbose() << "ofxCanvasEvents: keyReleased event recieved";
            ofNotifyKeyReleased(key);
        }
        else if (type == "mousePressed")
        {

            cout << args.params.toStyledString() << endl;
            int button = args.params["button"].asInt();
            int x = args.params["x"].asInt();
            int y = args.params["y"].asInt();
            
            ofLogVerbose() << "ofxCanvasEvents: mousePressed event recieved";
            ofNotifyMousePressed(x, y, button);
        }
        else if (type == "mouseReleased")
        {
            
            int button = args.params["button"].asInt();
            int x = args.params["x"].asInt();
            int y = args.params["y"].asInt();
            
            ofLogVerbose() << "ofxCanvasEvents: mouseReleased event recieved";
            ofNotifyMouseReleased(x, y, button);
        }
        else if (type == "mouseMoved")
        {

            int x = args.params["x"].asInt();
            int y = args.params["y"].asInt();
            
            ofLogVerbose() << "ofxCanvasEvents: mouseMoved event recieved";
            ofNotifyMouseMoved(x, y);
        }
        else if (type == "mouseDragged")
        {
            
            int button = args.params["button"].asInt();
            int x = args.params["x"].asInt();
            int y = args.params["y"].asInt();
            
            ofLogVerbose() << "ofxCanvasEvents: mouseDragged event recieved";
            ofNotifyMouseDragged(x, y, button);
        }
    }
}
    
HTTP::BasicJSONRPCServer::SharedPtr CanvasEvents::getServer()
{
    return server;
}

};

