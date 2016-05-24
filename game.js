var Player = require('./player.js');
var Deck = require('./deck.js');

function Game(){
   this.playingState = "waiting_for_players";
   this.players = [];
   this.spectators = [];
   this.cardSt1ack = [];
   this.trashCan = [];
   this.currentThrowerId = 0;
}

function shuffle(a) {
   var j, x, i;
   for (i = a.length; i; i -= 1) {
      j = Math.floor(Math.random() * i);
      x = a[i - 1];
      a[i - 1] = a[j];
      a[j] = x;
   }
}
function getRandomAvatars(){
   var avs = [];
   for(i=0;i<23;++i){
         avs.push(i);
   }
   shuffle(avs);
   return avs;
}

var usernames = ["Flapjack","Chojrak","Scooby Doo","Johnny Bravo","Ed","Rabbit Bugs","Jake","Dukey","Ben Ten","Chowder","Samurai Jack","Dexter","Ziggs","Darius","Shaco","Talon","Rengar","Teemo","Varus","Master Yi","Rammus","Dr. Mundo","Draven","Xin Zhao"];

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
      this.preparePlayerForGame(p);
      p.socket.emit('init',{id:p.id,avatar:p.avatar,username:p.username});
      p.socket.emit('change_game_state',"playing");
      p.dobierz();
      playerStates.push(p.serialize());
   }
   this.broadcast('update_players',playerStates);
   this.nextThrower();
};

Game.prototype.broadcast = function(evt,msg){
   for(i=0;i<this.players.length;++i){
      this.players[i].socket.emit(evt,msg);
   }
};

Game.prototype.nextThrower = function(){
   while(this.players[(++this.currentThrowerId)%this.players.length].HP<=0);
   this.broadcast('update_turn',{currentPid:this.currentThrowerId});
};

Game.prototype.getCardFromStack = function(){
   if(this.cardStack.length<1){
      this.cardStack = this.trashCan.splice(this.trashCan.length-10-1,10);
   }
   var rndid = Math.floor(Math.random() * this.cardStack.length);
   return this.cardStack.splice(rndid,1)[0];
};

Game.prototype.preparePlayerForGame = function(player){
   player.socket.on('throw_card',function(data){
      var cardId=parseInt(data.cardId,10);
      if(cardId<0||cardId>=player.handCards) return;
      if(player.handCards[cardId].canUse(data.kartaCelu)){
         player.handCards[cardId].thrown(data.kartaCelu);
         player.handCards.splice(cardId,1);
         player.dobierz();
      }
   });
};

Game.prototype.addPlayer = function(socket){
   if(this.playingState=="waiting_for_players"){
      var pid = this.players.length;
      var p = new Player(socket,this);
      p.init(this.playingState);
      this.players.push(p);
      console.log("a user connected ("+socket.handshake.address+"), there are "+this.players.length+" users");
      socket.emit('change_game_state',this.playingState);
      var game = this;
      socket.on('start_game',function(){
         game.startGame();
      });
      socket.on('disconnect',function(){
         var id = game.players.indexOf(p);
         game.players.splice(id,1);
         console.log("disconnected, users left: "+game.players.length);
      });
   }
   else{
      //socket.emit('spadaj',"Podglądaczy nie przyjmujemy");//TODO zaimplementować spectatorów
      console.log("Spectators not supported!");
      return -1;
   }
};

module.exports = Game;
