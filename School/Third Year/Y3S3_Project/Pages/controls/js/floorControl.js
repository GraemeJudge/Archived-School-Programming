var postReqPrefix = "";

function handleForm(floorNum){

	console.log("Floor number was: " + floorNum);
	if(floorNum >= 0){
		clearInterval(handleFormTimer);
		handleFormTimer = setInterval(handleForm,5000, floorNum);
		getRequest(postReqPrefix + "savesettings.php", "Des_Floor",1, function handle(retVal){
			var holder = retVal.split(",");
			console.log(holder[0],floorNum);
			if (holder[0]== floorNum){
				clearInterval(handleFormTimer);
				if(document.getElementById("elevatordir") != null){
					document.getElementById("elevatordir").innerHTML = "Arrived";
				}
				if(document.getElementById("floorDisplay") != null){
					document.getElementById("floorDisplay").innerHTML = holder[0];
				}
			}
			
			else{
				if(document.getElementById("elevatordir") != null){
					document.getElementById("elevatordir").innerHTML = "Moving";
				}
				if(document.getElementById("floorDisplay") != null){
					document.getElementById("floorDisplay").innerHTML = holder[0];
				}
			}
			
			
			switch(floorNum) {
  case 0:
   // document.getElementById('myImage').src='../res/elevatorinopen.jpg';
    break;
  case "1":if (holder[0]== floorNum){
  document.getElementById('myImage').src='../res/elevatorfloor1open.png';}
    break;
	case "2":
   if (holder[0]== floorNum){
  document.getElementById('myImage').src='../res/elevatorfloor2open.png';}
    break;
  case "3":
  if (holder[0]== floorNum){
  document.getElementById('myImage').src='../res/elevatorfloor3open.png';}
    break;
 
} 
		});
	}

}

function goDown(CFL){
	getRequest(postReqPrefix + "floorCall.php", "Des_Floor", CFL, function handle(retVal){});
	if(document.getElementById("elevatordir") != null){
		document.getElementById("elevatordir").innerHTML = "Going Down";
		clearInterval(handleFormTimer);
		handleFormTimer = setInterval(handleForm,5000, floorNum);
	}
}

function goUp(CFL){
	getRequest(postReqPrefix + "floorCall.php", "Des_Floor", CFL, function handle(retVal){});
	if(document.getElementById("elevatordir") != null){	
		document.getElementById("elevatordir").innerHTML = "Going Up";
		clearInterval(handleFormTimer);
		handleFormTimer = setInterval(handleForm,5000, floorNum);
	}
}

function floor(CFL){
	getRequest(postReqPrefix + "floorGoto.php", "Des_Floor", CFL, function handle(retVal){});
	document.getElementById("floorDisplay").innerHTML = CFL;
	clearInterval(handleFormTimer);
	floorNum=CFL;
	handleFormTimer = setInterval(handleForm,5000, floorNum);
}
	
function topFunction() {
	document.body.scrollTop = 0;
	document.documentElement.scrollTop = 0;
}

function colorchange(id, limitSwitch)
{
	var ele = document.getElementById(id);
	var floorlimitswitch = 0;

	if(ele.style.background == "rgb(26, 255, 0)" && limitSwitch == true){
		ele.style.background = "rgb(51,181,229)";
	}else if(ele.style.background != "rgb(26, 255, 0)" && limitSwitch != true){
		ele.style.background = "rgb(26, 255, 0)";
	}
}
	
function getRequest(RQURL, name, value, func){
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			func(this.responseText);
		}
	};
	xhttp.open("POST", RQURL, true);
	xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	xhttp.send(name + "=" + value);	
}

window.addEventListener('load', function() {
	var re = /(?:\.([^.]+))?$/;
	if(re.exec(window.location.pathname)[1] == "php"){
		postReqPrefix = "";
	}else{
		postReqPrefix = "php/";
	}
}, false);


var handleFormTimer;
var floorNum = -1;
window.addEventListener("load",function(){
	const metas = document.getElementsByTagName('meta');
	for (let i = 0; i < metas.length; i++) {
		if (metas[i].getAttribute('name') === 'floorNum') {
			floorNum = (metas[i].getAttribute('content'));
		}
	}
	handleForm(floorNum);
	
});


var SabbathFloor = 2;
var up = true;

function SabbathMove(){
	if(SabbathFloor == 4){
		up = false;
		SabbathFloor = 2;
	}
	if(SabbathFloor == 0){
		up = true;
		SabbathFloor = 2;
	}
	
	if(up){
		console.log("Going up to floor: " + SabbathFloor );
		goUp(SabbathFloor);
		SabbathFloor++;
	}else{
		console.log("Going down to floor: " + SabbathFloor );
		goDown(SabbathFloor);
		SabbathFloor--;
	}

}


var sabbathModeCheck = document.querySelector("input[name=Sabbath]");
var sabbathTimer;

window.addEventListener("load",function(){
	if(sabbathModeCheck != null){
		sabbathModeCheck.addEventListener('change', function() {
			if (this.checked) {
				goDown(1);
				console.log("Starting sabbath mode");
				sabbathTimer = setInterval(SabbathMove, 15000);
			} else {
				clearInterval(sabbathTimer);
				console.log("Stopping sabbath mode");
			}
		});
	}
});