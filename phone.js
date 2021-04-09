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
	// while(val<0){
	// 	val += 360;
	// }

	// while(val>=360){
	// 	val -= 360;
	// }

	return Number(val);
}

function pad(val){

	var width = 128;

	val = String(val);
	while(val.length != width){
		val = val+"!";
	}

	return val;
}

$( "#calibrate_normal" ).click(function() {

if (
    DeviceMotionEvent &&
    typeof DeviceMotionEvent.requestPermission === "function"
  ) {
    DeviceMotionEvent.requestPermission();
  }

	
  socket.emit("rotate_debug",last_x+", "+last_y+", "+last_z);
  cal_normal.x = 0 - simple_degree(last_x);
  cal_normal.y = 0 - simple_degree(last_y);
  cal_normal.z = 0 - simple_degree(last_z);
  print_cal(cal_normal);
});

$( "#show_raw" ).click(function() {
  socket.emit("rotate_debug",Number(event.alpha.toFixed(5))+", "+
  	Number(event.beta.toFixed(5))+", "+
  	Number(event.gamma.toFixed(5)));
});

function handleOrientation(event) {
	
	last_x = simple_degree((Number(event.alpha) + Number(cal_normal.x))).toFixed(5);
	last_y = simple_degree((Number(event.beta) + Number(cal_normal.y))).toFixed(5);
	last_z = simple_degree((Number(event.gamma) + Number(cal_normal.z))).toFixed(5);
	socket.emit("rotate_update",pad("x:"+last_x+":"+last_x+":"));
	socket.emit("rotate_update",pad("y:"+last_y+":"+last_y+":"));
	socket.emit("rotate_update",pad("z:"+last_z+":"+last_z+":"));
}


window.addEventListener("deviceorientation", handleOrientation);

