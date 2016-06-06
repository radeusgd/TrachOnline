### Client to server
* login [{nickname}] - informs player is ready to play, sets selected username
* requestStart - requests starting the round (for now no permissions checked)
* playCard [{id,attachTo,target}] - id (which card from hand), attachTo - cuid of card on table to attach to or -1 if it's the first action card, target (optional) - playerid (or itemid) for targeted cards only

### Server to client
* (connected) - connection established (not actually sent, simulated by the transport)
* error [message] - sends information about disconnection
* updateUsers [list of {id,username,maxHP,HP,cardsAmount,avatar}] - sends an updated user list
* init [{id,username,avatar}] - informs about start of the game (client should switch to playing viewport) and tells the player info
* updateTurn [{currentPid}] - inform about id of the player who is currently having his turn
* updateCards [list of names] - updates the cards the player has in hand

