require('./deck.js');
function Player(socket,gameRef){
   this.id = -1;
   this.avatar = -1;
   this.socket = socket;
   this.maxHP = 5;
   this.HP = 5;
   this.cardLimit = 5;
   this.handCards = [];
   this.tableCards = [];
   this.gameRef = gameRef;
}

Player.prototype.init = function(){

};
Player.prototype.dobierz = function(){
   while(this.handCards.length<this.cardLimit){
      var card=this.gameRef.getCardFromStack();
      this.handCards.push(card);
   }
   this.socket.emit('update_cards',this.getHandCardNames());
};

Player.prototype.serialize = function(){
   return {id:this.id,maxHP:this.maxHP,HP:this.HP,cardsAmount:this.handCards.length,avatar:this.avatar,username:this.username};
};

Player.prototype.getHandCardNames = function(){
   var names = [];
   this.handCards.forEach(function(card){
      //console.log(card);
      names.push(card.getName());
   });
   return names;
};

module.exports = Player;
