var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
app.use(express.static('html'));
var Game = require('./game.js');

var game = new Game();

io.on('connection', function(socket){
  console.log('a user connected');
  game.addPlayer(socket);
});
http.listen(3000, function(){
  console.log('listening on *:3000');
});
