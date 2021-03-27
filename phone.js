var socket = io();

// $( "#y_plus" ).click(function() {
// 	console.log("y_plus");
//   socket.emit("y_plus");
// });

// var adjust_x = 0;
// var adjust_y = 0;
// var adjust_z = 0;

// var last_x = 0;
// var last_y = 0;
// var last_z = 0;

// $( "#calibrate" ).click(function() {
// 	adjust_x = -1 * last_x;
// 	adjust_y = -1 * last_y;
// 	adjust_z = -1 * last_z;
//   //socket.emit("rotate_update",":90:0:0:");
// });

$( document ).ready(function() {
	if (
	DeviceMotionEvent &&
	typeof DeviceMotionEvent.requestPermission === "function"
	) {
		DeviceMotionEvent.requestPermission();
	}
});


$( "#custom" ).click(function() {
  socket.emit("rotate_update",":"+$("#x").val()+":"+$("#y").val()+":"+$("#z").val()+":");
});

function handleOrientation(event) {

	socket.emit("rotate_update",":"+event.alpha.toFixed(5)+":"+event.beta.toFixed(5)+":"+event.gamma.toFixed(5)+":");
	// last_x = event.alpha.toFixed(2);
	// last_y = event.beta.toFixed(2);
	// last_z = event.gamma.toFixed(2);
}



window.addEventListener("deviceorientation", handleOrientation);