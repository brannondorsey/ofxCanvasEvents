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

$(document).ready(function() {

    var JSONRPCClient; ///< The core JSONRPC WebSocket client.
    var EVENT_METHOD_PREFIX = 'HTMLCanvasEvent-';

    function addError(error) {
        console.log(error);
    }

    function onWebSocketOpen(ws) {

        var data = {
            width: canvas.width,
            height: canvas.height,
            aspect: (canvas.width/canvas.height).toFixed(2)
        };

        console.log(data);

        JSONRPCClient.call(
            EVENT_METHOD_PREFIX + 'canvasSize',
            data,
            function(result) {
                console.log(result);
            },
            addError
        );
    }

    function onWebSocketMessage(evt) {
        console.log("on message:");
        console.log(evt.data);

        // inside main.js
        websocketMessage(evt);
    }

    function onWebSocketClose() {
        console.log("on close");
    }

    function onWebSocketError() {
        console.log("on error");
    } 

    function sendEventToApp(evt) {
        
        if (evt.type == "mouseup" || 
            evt.type == "mousedown" ||
            evt.type ==  "mousemove") {

            var mouse = {
                x: evt.x - canvas.offsetLeft,
                y: evt.y - canvas.offsetTop,
            };
        }

        var data = {};

        switch (evt.type) {

            case "mouseover":

            data.type = "mouseOver";
            
            break;

            case "mouseout":

            data.type = "mouseOut";

            break;

            case "mousedown":
            
            data.type = "mousePressed";
            data.button = evt.button;
            data.x = mouse.x;
            data.y = canvas.y;
            data.w = canvas.width;
            data.h = canvas.height;

            bMouseDown = true;                     
                               
            break;

            case "mouseup":

            data.type = "mouseReleased";
            data.button = evt.button;
            data.x = mouse.x;
            data.y = mouse.y;
            data.w = canvas.width;
            data.h = canvas.height;

            bMouseDown = false;               
                               
            break;

            case "mousemove":

            data.type = evt.type;
            data.button = evt.button;
            data.x = mouse.x;
            data.y = mouse.y;
            data.w = canvas.width;
            data.h = canvas.height;

            data.type = bMouseDown ? "mouseDragged" : "mouseMoved";                    
                               
            break;

            case "keydown":

            data.type = "keyPressed";
            data.keycode = evt.keyCode || evt.which;
            console.log(evt);

            break;

            case "keyup":

            data.type = "keyReleased";
            data.keycode = evt.keyCode || evt.which;

            break;
        }

        JSONRPCClient.call(
            EVENT_METHOD_PREFIX + data.type,
            data,
            function(result) {

            },
            addError
        );
    }

    var canvas = document.getElementById('ofxCanvasEvents-canvas');
    var context = canvas.getContext('2d');
    
    var events = ['mouseover', 'mouseout', 'mouseup', 'mousedown', 'mousemove', 'keydown', 'keyup'];
    var bMouseDown = false;

    for (var i = 0; i < events.length; i++) {
        canvas.addEventListener(events[i], sendEventToApp);
    }

    // Initialize our JSONRPCClient
    JSONRPCClient = new $.JsonRpcClient({
        ajaxUrl: getDefaultPostURL(),
        socketUrl: getDefaultWebSocketURL(), // get a websocket for the localhost
        onmessage: onWebSocketMessage,
        onopen: onWebSocketOpen,
        onclose: onWebSocketClose,
        onerror: onWebSocketError
    });

});
