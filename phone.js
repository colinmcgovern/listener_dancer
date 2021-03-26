var socket = io();

// $( "#y_plus" ).click(function() {
// 	console.log("y_plus");
//   socket.emit("y_plus");
// });

// $( "#y_minus" ).click(function() {
// 	console.log("y_minus");
//   socket.emit("y_minus");
// });


function handleOrientation(event) {
	console.log(event.alpha);
	socket.emit("rotate_update",":"+event.alpha+":"+event.beta+":"+event.gamma+":");
}

if (
DeviceMotionEvent &&
typeof DeviceMotionEvent.requestPermission === "function"
) {
	DeviceMotionEvent.requestPermission();
}

window.addEventListener("deviceorientation", handleOrientation);