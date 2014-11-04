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
    
    void setInterpolateMousePos(bool b);
    
    bool getInterpolateMousePos() const;
    bool isMouseOver() const;
    
    HTTP::BasicJSONRPCServer::SharedPtr getServer();
    
protected:

    void _notifyCanvasEventRecieved(ofx::JSONRPC::MethodArgs& args);
    void _canvasSize(ofx::JSONRPC::MethodArgs& args);
    void _interpolateMouse(int& x, int& y, const int& width, const int& height);

    bool _bMouseOver;
    bool _bInterpolateMousePos;
    
    int _canvasWidth;
    int _canvasHeight;
    
    HTTP::BasicJSONRPCServer::SharedPtr _server;

private:

};
    
} // namespace ofx
