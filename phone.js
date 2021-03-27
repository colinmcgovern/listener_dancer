var socket = io();

var last_x = 0;
var last_y = 0;
var last_z = 0;

var cal_normal = {x: 0, y: 0, z: 0}; 
var cal_left = {x: 0, y: 0, z: 0}; 

function print_cal(val){
	socket.emit("rotate_debug",console.log(val.x + ", " + val.y + ", " + val.z));
}

function simple_degree(val){
	while(val<0){
		val += 360;
	}

	while(val>=360){
		val -= 360;
	}

	return Number(val);
}

$( document ).ready(function() {
	if (
	DeviceMotionEvent &&
	typeof DeviceMotionEvent.requestPermission === "function"
	) {
		DeviceMotionEvent.requestPermission();
	}
});

$( "#calibrate_normal" ).click(function() {
  socket.emit("rotate_debug",last_x+", "+last_y+", "+last_z);
  cal_normal.x = 0 - simple_degree(last_x);
  cal_normal.y = 0 - simple_degree(last_y);
  cal_normal.z = 0 - simple_degree(last_z);
  print_cal(cal_normal);
});

$( "#calibrate_left" ).click(function() {
  socket.emit("rotate_debug",last_x+", "+last_y+", "+last_z);
});

$( "#show_cal" ).click(function() {
  socket.emit("rotate_debug",last_x+", "+last_y+", "+last_z);
});

$( "#show_raw" ).click(function() {
  socket.emit("rotate_debug",Number(event.alpha.toFixed(5))+", "+
  	Number(event.beta.toFixed(5))+", "+
  	Number(event.gamma.toFixed(5)));
});

function handleOrientation(event) {
	last_x = Number(event.alpha.toFixed(5)) + Number(cal_normal.x);
	last_y = Number(event.beta.toFixed(5)) + Number(cal_normal.y);
	last_z = Number(event.gamma.toFixed(5)) + Number(cal_normal.z);
	socket.emit("rotate_update",":"+last_x+":"+last_y+":"+last_z+":");
}



window.addEventListener("deviceorientation", handleOrientation);