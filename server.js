var app = require('express')();
var express = require('express'); 
var http = require('http').Server(app);
var io = require('socket.io')(http);
var port = process.env.PORT || 8080;

//Creating the Grid Array 
var grid = new Array(GRID_SIZE);

for (var i = 0; i < GRID_SIZE; i++) {
	grid[i] = new Array(GRID_SIZE);
}

for(var i = 0; i < GRID_SIZE; i++){
	for(var j = 0; j < GRID_SIZE; j++){
		grid[i][j] = 1;
	}
}

app.use("/", express.static(__dirname + '/'));

app.get('/', function(req, res){
  res.sendFile(__dirname + '/');
});

http.listen(port, function(){
  console.log('listening on *:' + port);
});