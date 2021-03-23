var bytesToSend = [0x50, 0x4f],
    hexVal = new Uint8Array(bytesToSend);
var net = require('net');

var HOST = 'ec2-54-201-26-119.us-west-2.compute.amazonaws.com';
var PORT = 15;

var client = new net.Socket();
client.connect(PORT, HOST, function() {
    console.log('CONNECTED TO: ' + HOST + ':' + PORT);
    client.write("test");

    $(document).ready(function(){
  $("button").click(function(){
    client.write("test");
  });
});
});

// client.on('data', function(data) { // 'data' is an event handler for the client socket, what the server sent

// 	while(1==1){
// 		client.write("test");
// 	}
	
//     console.log('DATA: ' + data);
//     //client.destroy(); // Close the client socket completely

// });



// Add a 'close' event handler for the client socket
client.on('close', function() {
    console.log('Connection closed');
});