var Player = require('./player.js');
var Deck = require('./deck.js');

function Game(){
   this.playingState = "waiting_for_players";
   this.players = [];
   this.spectators = [];
   this.cardStack = [];
   this.trashCan = [];
}

function getRandomAvatars(){
   var avs = [];
   for(i=0;i<23;++i){
         avs.push(i);
   }
   shuffle(avs);
   return avs;
}

var usernames = [];

Game.prototype.startGame = function(){
   this.playingState = "playing";
   this.cardStack = Deck.getANewFullDeck();
   var playerStates = [];
   var p,i;
   var avs = getRandomAvatars();
   for(i=0;i<this.players.length;++i){
      p=this.players[i];
      p.id = i;
      p.avatar = avs[i];
      p.username = usernames[avs[i]];
      p.socket.emit('init',{id:p.id,avatar:p.avatar,username:""});
      p.socket.emit('change_game_state',"playing");
      p.dobierz();
      playerStates.push(p.serialize());
      p.socket.emit('update_cards',p.getHandCardNames());
   }
   //console.log(playerStates);
   for(i=0;i<this.players.length;++i){
      p=this.players[i];
      p.socket.emit('update_players',playerStates);
      //console.log(p.getHandCardNames());
   }
};

Game.prototype.getCardFromStack = function(){
   if(this.cardStack.length<1){
      this.cardStack = this.trashCan.splice(this.trashCan.length-10-1,10);
   }
   var rndid = Math.floor(Math.random() * this.cardStack.length);
   return this.cardStack.splice(rndid,1)[0];
};

function shuffle(a) {
   var j, x, i;
   for (i = a.length; i; i -= 1) {
      j = Math.floor(Math.random() * i);
      x = a[i - 1];
      a[i - 1] = a[j];
      a[j] = x;
   }
}

Game.prototype.addPlayer = function(socket){
   if(this.playingState=="waiting_for_players"){
      var pid = this.players.length;
      var p = new Player(socket,this);
      p.init(this.playingState);
      this.players.push(p);
      socket.emit('change_game_state',this.playingState);
      var game = this;
      socket.on('start_game',function(){
         game.startGame();
      });
      socket.on('disconnect',function(){
         var id = game.players.indexOf(p);
         game.players.splice(id,1);
      });
   }
   else{
      //socket.emit('spadaj',"Podglądaczy nie przyjmujemy");//TODO zaimplementować spectatorów
      console.log("Spectators not supported!");
      return -1;
   }
};

module.exports = Game;
