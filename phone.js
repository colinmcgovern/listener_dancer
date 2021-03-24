
	var socket = io();

	$( "#test" ).click(function() {
		console.log("test");
	  socket.emit("test");
	});

	// function deviceOrientationListener(event) {
	// 	$("#debug").text(event.alpha+' '+event.beta+' '+event.gamma);
	// }

	// deviceOrientationListener(deviceOrientationListener);

	// if (window.DeviceOrientationEvent) {
	// window.addEventListener("deviceorientation", deviceOrientationListener);
	// } else {
	// alert("Sorry, your browser doesn't support Device Orientation");
	// }


window.addEventListener('deviceorientation', function(event) {

  var a = event.alpha;
  var b = event.beta;
  var g = event.gamma;

  $("#debug").text(a+' '+b+' '+g);

  console.log( g.toString() ); // Better to use a non-blocking method like console.log to display results.

}, false);
