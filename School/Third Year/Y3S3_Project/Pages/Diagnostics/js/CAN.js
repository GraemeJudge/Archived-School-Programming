window.addEventListener("load",function(){
	getData();
	setInterval(getData, 2000);
});

var messageBox = document.getElementById("canBox");
var lastID = 0;

function getData(){
		getRequest("php/getCAN.php", function handle(data){
			var messages = data.split(",");
			if(messages[0] != lastID){
				console.log("updating display");
				lastID = messages[0];
				var holder = "";
				for(i = 1; i < messages.length; i++){
					holder+= messages[i] + "\n";
				}
				messageBox.innerHTML = holder;
			}else{
				console.log("No updates");
			}
		});
}


function clearCAN(){
	getRequest("php/clearCAN.php", function handle(){});
	getData();
}

function getRequest(request, func){
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			func(this.responseText);
		}
	};
	xhttp.open("GET", request, true);
	xhttp.send();
}
