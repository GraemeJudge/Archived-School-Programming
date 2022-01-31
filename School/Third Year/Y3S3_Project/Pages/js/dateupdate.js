window.onload = function(){
	copyrightDisplay();
	timedisplay();
	setInterval(timedisplay, 2000);
}
	
	
function copyrightDisplay(){
	var year = new Date().getFullYear();
	var yearList = document.getElementsByClassName("cpyear");
	for(i=0; i<yearList.length; i++){
		var response = "Copyright &copy; " + year + yearList[i].innerHTML;
		yearList[i].innerHTML = response;
	}
}
	
function timedisplay(){		
	var date = new Date();
	var dateList = document.getElementsByClassName("date");
	for(i=0; i<dateList.length; i++){
		dateList[i].innerHTML = date;
	}
}