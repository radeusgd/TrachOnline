var Socket = function(url){
	this.ws = new WebSocket(url);
	this.onerror = function(){};
	this.onconn = function(){};
	this.handlers = {};
	
	var sock = this;
	this.ws.onopen = function () {
		sock.onconn();
	};
	this.ws.onclose = function () {
		sock.onerror("Connection lost");
	};
	this.ws.onmessage = function (msg) {
		var message = JSON.parse(msg.data);
		if(!message.name) return;//error!
		var handler = sock.handlers[message.name];
		if(handler){
			handler(message.data);
		}
	};
	this.ws.onerror = function (error) {
		sock.onerror(error);
	};
}

Socket.prototype.on = function(name, callback){
	if(name=='error') this.onerror = callback;
	if(name=='connected') this.onconn = callback;
	else this.handlers[name] = callback;
};

Socket.prototype.emit = function(name, data){
	var msg = {name:name,data:data};
	this.ws.send(JSON.stringify(msg));
};
