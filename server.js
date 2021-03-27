var fs = require('fs');
var https = require('https');

var express = require('express');
var app = express();

var options = {
  key: fs.readFileSync('./key.pem'),
  cert: fs.readFileSync('./cert.pem')
};
var serverPort = 8080;

var server = https.createServer(options, app);
var io = require('socket.io')(server);

var net = require("net");

var job_socket;
var job_server = "127.0.0.1";
var job_port = 15;

function connect_job(){

	//TODO figure out how to reset job socket when it is in the error state

	job_socket = net.connect(job_port, job_server);
	
	job_socket.on('error', function(ex) {
		console.log("connection to job server failed");
		throw '';
	});
}

connect_job();

function send_job(msg){
	console.log("send_job");
	
	try{
		job_socket.write(msg);
	}catch(err){
		console.log("Failed to send data to job server");
		connect_job();
	}
	
};

app.use("/", express.static(__dirname + '/'));

app.get('/', function(req, res) {
  res.sendFile(__dirname + '/');
});

io.on('connection', function(socket) {
  console.log("connection");

	socket.on('y_plus', function(msg){

		console.log(msg);
		send_job(msg);
	});

	socket.on('y_minus', function(msg){

		console.log(msg);
		send_job(msg);
	});

	socket.on('rotate_update', function(msg){

		console.log(msg);
		send_job(msg);
	});
});

server.listen(serverPort, function() {
  console.log('server up and running at %s port', serverPort);
});

