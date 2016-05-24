function Pustak(){
   this.a="b";
}

Pustak.prototype.getName = function(){
   return "pustak";
};

Pustak.prototype.canUse = function(targetCard){
   return true;//FIXME
};

module.exports = Pustak;
