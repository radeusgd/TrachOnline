var Pustak = require('./cards/pustak.js');

module.exports = {getANewFullDeck:function(){
   var deck = [];
   for(var i=0;i<40;++i) deck.push(new Pustak());
   //console.log(deck[0].getName());
   return deck;
}};
