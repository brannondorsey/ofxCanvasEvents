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

#pragma once

#include "ofMain.h"
#include "ofxPointer.h"
#include "ofxJSONRPC.h"
#include "ofxHTTP.h"

namespace ofx
{

class CanvasEvents
{
public:
    
    static std::string EVENT_METHOD_PREFIX;
    
    CanvasEvents(HTTP::BasicJSONRPCServerSettings settings = HTTP::BasicJSONRPCServerSettings());
    virtual ~CanvasEvents();
    
    void notifyCanvasEventRecieved(ofx::JSONRPC::MethodArgs& args);
    
    HTTP::BasicJSONRPCServer::SharedPtr getServer();
    
//template<class ListenerClass>
//void registerEvents(ListenerClass* listener,
//                    int prio = OF_EVENT_ORDER_AFTER_APP)
//{
//    ofAddListener(PointerEvents().onPointerDown, listener, &ListenerClass::onPointerDown, prio);
//    ofAddListener(PointerEvents().onPointerUp, listener, &ListenerClass::onPointerUp, prio);
//    ofAddListener(PointerEvents().onPointerMove, listener, &ListenerClass::onPointerMove, prio);
//    ofAddListener(PointerEvents().onPointerCancel, listener, &ListenerClass::onPointerCancel, prio);
//    
//    ofAddListener(ofEvents().keyPressed, listener, &ListenerClass::keyPressed, prio);
//    ofAddListener(ofEvents().keyReleased, listener, &ListenerClass::keyReleased, prio);
//    
//}


//template<class ListenerClass>
//void unRegisterEvents(ListenerClass* listener,
//                      int prio = OF_EVENT_ORDER_AFTER_APP)
//{
//    ofRemoveListener(PointerEvents().onPointerDown, listener, &ListenerClass::onPointerDown);
//    ofRemoveListener(PointerEvents().onPointerUp, listener, &ListenerClass::onPointerUp);
//    ofRemoveListener(PointerEvents().onPointerMove, listener, &ListenerClass::onPointerMove);
//    ofRemoveListener(PointerEvents().onPointerCancel, listener, &ListenerClass::onPointerCancel);
//    ofRemoveListener(ofEvents().keyPressed, listener, &ListenerClass::keyPressed, prio);
//    ofRemoveListener(ofEvents().keyReleased, listener, &ListenerClass::keyReleased, prio);
//
//}


//template<class ListenerClass>
//void registerGestureEvents(ListenerClass* listener,
//                           int prio = OF_EVENT_ORDER_AFTER_APP)
//{
//    ofAddListener(PointerGestureEvents().onPointerDoublePress, listener, &ListenerClass::onPointerDoublePress, prio);
//    ofAddListener(PointerGestureEvents().onPointerPressAndHold, listener, &ListenerClass::onPointerPressAndHold, prio);
//}
//
//
//template<class ListenerClass>
//void unRegisterGestureEvents(ListenerClass* listener,
//                             int prio = OF_EVENT_ORDER_AFTER_APP)
//{
//    ofRemoveListener(PointerGestureEvents().onPointerDoublePress, listener, &ListenerClass::onPointerDoublePress, prio);
//    ofRemoveListener(PointerGestureEvents().onPointerPressAndHold, listener, &ListenerClass::onPointerPressAndHold, prio);
//}

protected:
    
    HTTP::BasicJSONRPCServer::SharedPtr server;

private:

};
    
} // namespace ofx
