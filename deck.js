var Pustak = require('./cards/pustak.js');
var Atak = require('./cards/atak.js');

module.exports = {getANewFullDeck:function(){
   var deck = [];
   var i;
   for(i=0;i<20;++i) deck.push(new Atak());
   for(i=0;i<20;++i) deck.push(new Pustak());
   
   return deck;
}};
