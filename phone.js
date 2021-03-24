var socket = io();

$( "#test" ).click(function() {
	console.log("test");
  socket.emit("test");
});