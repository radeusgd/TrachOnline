var socket = new Socket('ws://' + document.location.host + '/ws');
var player = [];
var myCards = [];
var me = {};
var targetableList = ['atak', 'przerzut', 'uzdrowienie', 'potezne_uzdrowienie', 'pelna_regeneracja', 'wymiana_kart', 'nowonarodzony','zamiana','rzut','trening','gruboskorny','nadwrazliwy','berserk', 'wampir','superwytrzymaly', 'kot', 'oslabienie','wielka_lapa','mala_lapka'];
var specialCases = {};
var hierarchy = {};
var cardsInCW ={};
/*jshint sub:true */
/*specialCases["zmasowany_atak"] = function(cardId, onCardId){
    socket.emit('playCard',{id:parseInt(cardId),attachTo:parseInt(onCardId),target:0});//target is not really used but for simplicity it's just set to anything, for example 0 (we send it to make card targetable, so that the system knows who's the owner) it may get simplified in the future if we introduce card owner concept (needed for green enhancements anyway)
};*/
var color = "#ffff00";

$(document).ready(function(){
    $(".view").hide();
    show("connecting");
    $("#cardwait").hide();

    $("#openCardwait").click(function(){
      handleCardwait();
    });
});

function show(type){
    $(".view").hide(90);
    $("#"+type).show(200);
}

socket.on('connected',function(){
    $("#loginSubmit").click(function(){
        if($("#nickname").val()==="" || $("#nickname").val()=="???") return;
        socket.emit("login",{nickname:$("#nickname").val()});
        show("waiting");
    });
    $("#startGame").click(function(){
        socket.emit("requestStart");
    });
    show("login");
    var prev="";
    var chatSubmit = function(){
        prev = $("#chatInput").val();
        socket.emit("chatMessage",prev);
        $("#chatInput").val("");
    };
    $("#chatSubmit").click(chatSubmit);
    $("#chatInput").keyup(function(e){
        if(e.keyCode==13){
            chatSubmit();
        }
        if(e.keyCode==38){
            $("#chatInput").val(prev);
        }
    });
    $("#skipper").click(function(){
        socket.emit('skip');
        $("#skipper").hide(100);
    });
});

socket.on('updateUsers',function(update){
    player.length=update.length;
    for(var i=0;i<update.length;i++){
        player[i]={};
        player[i].id=update[i].id;
        player[i].maxHP=update[i].maxHP;
        player[i].HP=update[i].HP;
        player[i].cardsAmount=update[i].cardsAmount;
        player[i].avatar=update[i].avatar;
        player[i].username=update[i].username;
        player[i].tableCards=update[i].cards;
    }
    showPlayerStatistics();
});

socket.on('chatMessage',function(text){
    $("#chatText").append(text+"<br>");
    $("#chatText").scrollTop($("#chatText")[0].scrollHeight);
});



socket.on('error',function(err){
    console.log(err);
    show("connectionLost");
    $("#connectionLostReason").html($("#connectionLostReason").html()+err);
});

socket.on('init', function(init){
    show("playing");
    me.id=init.id;
    me.username=init.username;
    me.avatar=init.avatar;
    showMe();
});
var currentThrower = -1;
socket.on('updateTurn', function(update){
    $(".p"+currentThrower).removeClass("bold");
    currentThrower=update.currentPid;
    refreshThrower();

});

function refreshThrower(){
    $(".p"+currentThrower).addClass("bold");
    if(currentThrower==me.id){
        $("#gameArea").html("");
        $("#gameArea").append("<div id='cardDrop'>TWÓJ RUCH<br>ZAGRAJ KARTĘ TUTAJ</div>");
        $("#cardDrop").droppable(
          {
            drop: function(event, ui){
    console.log("Card dropped on another");
      var thrown = ui.draggable.attr('id');
      var thrownId = parseInt(thrown.substr(5,thrown.length-5));
      var thrownAt = -1;//$(this).attr('id');
//      thrownAt = parseInt(thrownAt.substr(9, thrownAt.length-9));
      if(thrownId>=0){
          handleAction(thrownId,thrownAt);
      }
      else{
          emitHierarchy(thrownAt);
          $("#cardwait").html("");
          $("#cardwait").hide(200);
      }
    }

          }
        );
      }
}

function preparePlayerForChoosing(i,cardId,onCardId,at){
    var p = player[i];
    $("#player"+i).unbind('click');
    $("#player"+i).click(function(){
        console.log("Directing at ",p.id);
        if(onCardId!==null) socket.emit('playCard',{id:parseInt(cardId),attachTo:parseInt(onCardId),target:p.id});
        else {
          cardId.to = p.id;
          addToHierarchy(cardId,at);
        }
        $("#chosePlayerModal").modal('hide');
    });
}

function handleAction(cardId,onCardId){
    console.log("classic action");
  var special = specialCases[myCards[cardId]];
  if(special!==undefined){
    special(cardId,onCardId);
    return;
  }
  var targetable = checkTargetable(myCards[cardId]);
  if(targetable){
    $("#chosePlayerModal").modal('show');
    $('#chosePlayerModal').modal({backdrop: 'static', keyboard: false});
    for(var i=0;i<player.length;i++){
        preparePlayerForChoosing(i,cardId,onCardId);
    }
  }
  else{
    socket.emit('playCard',{id:parseInt(cardId),attachTo:parseInt(onCardId)});
  }
}

function checkTargetable(card){
  for(var i=0;i<targetableList.length;i++){
    if(card==targetableList[i]) return true;
  }
  return false;
}

socket.on('updateCards', function(update){
    myCards=update;
    console.log("karty");
    console.log(myCards);
    showCards();
});

function showPlayerStatistics(){
    var innerPlayerList ="";
    var i;
    for(i=0;i<player.length;i++){
        innerPlayerList +='<li class="list-group-item p'+player[i].id+'"><div class = "playerStats"><div><img class="img-thumbnail playerImages" src="/avatars/'+player[i].avatar+'.jpg"></div>';
        innerPlayerList +=' <div class="stats"> '+player[i].username+'<br>HP='+player[i].HP+'/'+player[i].maxHP+'<br>';
        innerPlayerList +='KnR='+player[i].cardsAmount;
        innerPlayerList +='</div></div><div class="playerTableCardContainer">';
        if(player[i].tableCards !== undefined){
            for(var j=0; j<player[i].tableCards.length;j++){
                innerPlayerList += "<a href='/cards/"+player[i].tableCards[j]+".jpg' data-lightbox = 'image-1'><img src='/cards/"+player[i].tableCards[j]+".jpg' class='playerTableCardImages'></a>";
            }
        }
        innerPlayerList +='</div></li>';
    }
    $(".playerList").html(innerPlayerList);
    refreshThrower();

    var innerChosePlayer = '';
    for(i=0;i<player.length;i++){
      innerChosePlayer += '<li class="list-group-item"><img id="player'+i+'" class="img-thumbnail" src="/avatars/'+player[i].avatar+'.jpg">'+player[i].username+'</li>';
    }
    $("#chosePlayer").html(innerChosePlayer);
}

function showCards(){
    var innerCards='';
    for(var i=0;i<myCards.length;i++){
        innerCards+="<a href='/cards/"+myCards[i]+".jpg' data-lightbox = 'image-1'><img  id = 'karta"+i+"' src='/cards/"+myCards[i]+".jpg' class='cardImages'></a>";
      }
    $("#cards").html(innerCards);
    $(".cardImages").draggable({
      revert: true,
      containment: "body",
      appendTo: 'body',
      scroll: false,
    });
}

function showMe(){
    var innerMe='';
    innerMe+='<img src="/avatars/'+me.avatar+'.jpg"> '+me.username;
    $("#me").html(innerMe);
}

function getPlayerById(idd){
  for(var i=0;i<player.length;i++){
    if(player[i].id == idd){
       return player[i];
     }
   }
  return;
}
socket.on('updateTurnTable',function(cards){
    $("#skipper").show(300);
  $("#gameArea").html("");
  color = "#ffff00";
  for(var i=0;i<cards.length;i++){
    var parent = $("#gameArea");
    handleCard(cards[i],parent);
  }

});

function LightenDarkenColor(col, amt) {

    var usePound = false;

    if (col[0] == "#") {
        col = col.slice(1);
        usePound = true;
    }

    var num = parseInt(col,16);

    var r = (num >> 16) + amt;

    if (r > 255) r = 255;
    else if  (r < 0) r = 0;

    var b = ((num >> 8) & 0x00FF) + amt;

    if (b > 255) b = 255;
    else if  (b < 0) b = 0;

    var g = (num & 0x0000FF) + amt;

    if (g > 255) g = 255;
    else if (g < 0) g = 0;

    return (usePound?"#":"") + (g | (b << 8) | (r << 16)).toString(16);

}


function handleCard(card,parent){
  var innerCard = '';
  var fromAvatar = "";
  var toAvatar = "";
  if(card.from !== undefined){
    fromAvatar = getPlayerById(card.from).avatar;
  }
  if(card.to !== undefined){
      toAvatar = getPlayerById(card.to).avatar;
  }
  if(fromAvatar!==""){
      fromAvatar="<img  src='/avatars/"+fromAvatar+".jpg'>";
  }
  if(toAvatar!==""){
      toAvatar="<img  src='/avatars/"+toAvatar+".jpg'>";
  }
  innerCard = "<div class='tableContainerClass' id = 'tableContainer"+card.id+"'>"+fromAvatar+"<img class='tableCardClass' id='tableCard"+card.id+"'src='/cards/"+card.name+".jpg'>"+toAvatar+"</div>";

  parent.append(innerCard);
  console.log(parent);

  if(parent.attr("id")=="cardwait"){
    console.log("takkk");
    $("#tableCard"+card.id).draggable();
  }


  $("#tableCard"+card.id).droppable({
    drop: function(event, ui){
    console.log("Card dropped on another");
      var thrown = ui.draggable.attr('id');
      var thrownId = parseInt(thrown.substr(5,thrown.length-5));
      var thrownAt = $(this).attr('id');
      thrownAt = parseInt(thrownAt.substr(9, thrownAt.length-9));
      if(card.id>=0) {
        if(thrownId>=0){
          handleAction(thrownId,thrownAt);
        }
        else{
          emitHierarchy(thrownAt);
          $("#cardwait").html("");
          $("#cardwait").hide(200);
        }
      }
      else {
        ui.draggable.hide();
        handleCardwaitAction(hierarchy, thrownId,thrownAt);
      }
    }
  });
  $("#tableContainer"+card.id).css("background-color",color);

  if(card.attached.length>0){
    color = LightenDarkenColor(color,-40);
    $("#tableContainer"+card.id).append("<hr><div id='childrenContainer"+card.id+"'></div>");
    var childrenContainer = $("#childrenContainer"+card.id);
    for(var x=0;x<card.attached.length;x++){
      handleCard(card.attached[x],childrenContainer);
      if(x===card.attached.length-1){

      }
    }
    color = LightenDarkenColor(color,40);
  }

}

socket.on('updateTiming',function(seconds){
  $("#timer").html("Do końca tury zostało "+seconds+" sekund");
});

function handleCardwait(){
  $("#cardwait").show(500);
  console.log($("#cardwait"));
  if($("#cardwait").hasClass('ui-droppable')){
      $("#cardwait").droppable('enable');
  }
  $("#cardwait").droppable({
    drop: function( event, ui ) {
      $(this).droppable('disable');
      ui.draggable.hide();
      var thrown = ui.draggable.attr('id');
      var thrownId = thrown.substr(5,thrown.length-5);
      hierarchy ={};
      cardsInCW = {};
      handleCardwaitAction(hierarchy, thrownId, null);


    },
  });
}

function handleCardwaitAction(hierarchy, thrown, at){
  var card = {};
  card.id = - thrown - 1;
  card.name = myCards[thrown];
  card.attached =[];
  cardsInCW[card.id] = card;
  at = cardsInCW[at];
  console.log(at);
  console.log("DD",cardsInCW);

  //console.log(card.name);


  if(checkTargetable(card.name)){
      $("#chosePlayerModal").modal('show');
      $('#chosePlayerModal').modal({backdrop: 'static', keyboard: false});
      card.from = me.id;
      for(var i=0;i<player.length;i++){
          preparePlayerForChoosing(i,card,null,at);
      }

  }
  else addToHierarchy(card,at);
  //console.log(hierarchy);
}

function addToHierarchy(card,at){
  if(at===undefined) {
    console.log("NULL");
    hierarchy = card;
    card = hierarchy;
  }
  else at.attached.push(card);
  $("#cardwait").html("");
  handleCard(hierarchy, $("#cardwait"));
}

function emitHierarchy(at){
  hierarchy.attachTo = at;
  console.log("A",hierarchy);
  prepareHierarchy(hierarchy);
  console.log("B",hierarchy);
  socket.emit("playCard",hierarchy);
}

function prepareHierarchy(card){
  card.id = - card.id - 1;
  card.target = card.to;
  delete card.name;
  delete card.from;
  delete card.to;
  for(var i=0;i<card.attached.length;i++){
    prepareHierarchy(card.attached[i]);
  }
}
