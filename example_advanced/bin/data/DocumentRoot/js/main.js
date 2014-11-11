var data = {
  "module": "scene",
  "method": "draw",
  "params": {
    "shapes": [{
      "shape": {
        "type": "polyline",
        "geometry": {
          "isClosed": true,
          "rightVector": {
            "x": 100,
            "y": 100,
            "z": 2
          },
          "points": [{
            "x": 500,
            "y": 100,
            "z": 2
          }, {
            "x": 500,
            "y": 500,
            "z": 2
          }, {
            "x": 100,
            "y": 500,
            "z": 2
          }, {
            "x": 100,
            "y": 100,
            "z": 2
          }]
        },
        "style": {
          "fill": {
            "r": 255,
            "g": 80,
            "b": 90,
            "a": 255
          },
          "stroke": {
            "r": 1,
            "g": 2,
            "b": 2,
            "a": 2
          }
        }
      }
    }]
  }
};

var ctx; // defined globally

function websocketMessage(evt) {

	if (evt.module == "scene") {

		if (evt.method == "draw") {

			drawScene(evt.params.shapes, ctx);
		}
	}
}

function drawScene(shapes, context) {

	for (var i = 0; i < shapes.length; i++) {
		drawShape(shapes[i].shape, context);
	}
}

function drawShape(shape, context) {

	var geometry = shape.geometry;
	var type = shape.type;

	console.log(shape);

	var isBeginPath = false;

	switch(type) {

		case 'polyline':

			context.beginPath();
			isBeginPath = true;
			
			var points = geometry.points;
			
			for (var i = 0; i < points.length; i++) {

				var point = points[i];
				
				if (i == 0) context.moveTo(point.x, point.y); 
				else context.lineTo(point.x, point.y);
			}

			if (geometry.isClosed) context.lineTo(points[0].x, points[0].y);

			break;
	}

	// close the path
	if (isBeginPath) context.closePath();

	var style = shape.style;

	if (typeof style.fill !== 'undefined') {
		
		context.fillStyle = getCSSColor(style.fill);
		
		if (type == 'polyline') context.fill();
	}

	if (typeof style.stroke !== 'undefined') {
		
		context.strokeStyle = getCSSColor(style.fill);

		if (type == 'polyline') context.stroke();
	}
}

function getCSSColor(c) {
	return 'rgba(' + c.r + ',' + c.g + ',' + c.b + ',' + c.a + ')';
}

$(document).ready(function(){

	var canvas = document.getElementById('ofxCanvasEvents-canvas');
	ctx = canvas.getContext('2d');

	websocketMessage(data);

});

