// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
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

var JSONRPCClient; ///< The core JSONRPC WebSocket client.
var EVENT_METHOD_PREFIX = 'HTMLCanvasEvent-';

function addError(error) {
    console.log(error);
}

function onWebSocketOpen(ws) {
    console.log("on open");
    console.log(ws);
}

function onWebSocketMessage(evt) {
    console.log("on message:");
    console.log(evt.data);
}

function onWebSocketClose() {
    console.log("on close");
}

function onWebSocketError() {
    console.log("on error");
}  

$(document).ready(function() {

    // Initialize our JSONRPCClient
    JSONRPCClient = new $.JsonRpcClient({
        ajaxUrl: getDefaultPostURL(),
        socketUrl: getDefaultWebSocketURL(), // get a websocket for the localhost
        onmessage: onWebSocketMessage,
        onopen: onWebSocketOpen,
        onclose: onWebSocketClose,
        onerror: onWebSocketError
    });

    var canvasWrapper = document.getElementById('canvas-wrapper');
    var canvas = document.getElementById('ofxCanvasEvents-canvas');
    var context = canvas.getContext('2d');

    // canvas.addEventListener('pointerdown',   sendEventToApp);
    // canvas.addEventListener('pointerup',     sendEventToApp);
    // canvas.addEventListener('pointermove',   sendEventToApp);
    // canvas.addEventListener('pointerover',   sendEventToApp);
    // canvas.addEventListener('pointerout',    sendEventToApp);
    // canvas.addEventListener('pointerenter',  sendEventToApp);
    // canvas.addEventListener('pointerleave',  sendEventToApp);
    // canvas.addEventListener('pointercancel', sendEventToApp);
    
    var events = ['mouseup', 'mousedown', 'mousemove', 'keydown', 'keyup'];
    var bMouseDown = false;

    for (var i = 0; i < events.length; i++) {
        canvas.addEventListener(events[i], sendEventToApp);
    }

    function sendEventToApp(evt) {
        
        if (evt.type == "mouseup" || 
            evt.type == "mousedown" ||
            evt.type ==  "mousemove") {

            var mouse = {
                x: evt.x - canvas.offsetLeft,
                y: evt.y - canvas.offsetTop
            };
        }

        var data = {};
        
        switch (evt.type) {

            case "mousedown":
            
            data.type = "mousePressed";
            data.button = evt.button;
            data.x = mouse.x;
            data.y = mouse.y;

            bMouseDown = true;                     
                               
            break;

            case "mouseup":

            data.type = "mouseReleased";
            data.button = evt.button;
            data.x = mouse.x;
            data.y = mouse.y;

            bMouseDown = false;               
                               
            break;

            case "mousemove":

            data.type = evt.type;
            data.button = evt.button;
            data.x = mouse.x;
            data.y = mouse.y;

            data.type = bMouseDown ? "mouseDragged" : "mouseMoved";                    
                               
            break;

            case "keydown":

            data.type = "keyPressed";
            data.key = evt.keyCode || evt.which;

            break;

            case "keyup":

            data.type = "keyReleased";
            data.key = evt.keyCode || evt.which;

            break;
        }


        JSONRPCClient.call(
            EVENT_METHOD_PREFIX + data.type,
            data,
            function(result) { console.log(result) },
            function(error) { console.error(error) });
    }

});