var socket = io();

$( "#y_plus" ).click(function() {
	console.log("y_plus");
  socket.emit("y_plus");
});

$( "#y_minus" ).click(function() {
	console.log("y_minus");
  socket.emit("y_minus");
});