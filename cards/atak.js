function Atak(){

}

Atak.prototype.getName = function(){
   return "atak";
};

Atak.prototype.canUse = function(targetCard){
   return true;//FIXME
};

module.exports = Atak;
