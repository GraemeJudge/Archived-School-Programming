
document.getElementById('requestReason').onkeyup = function () {
  document.getElementById('charCount').innerHTML = "Characters left: " + (180 - this.value.length);
  if(this.value.length > 180){
	  document.getElementById('charCount').innerHTML += '<p class="text-danger">Character count exceeded</p>' ;
  }
};

function validateName() {
	if(document.getElementById('firstName').value.length < 1){
		if(document.getElementById('champ1') == null){
			document.getElementById('names').innerHTML += '<p id="champ1" class="text-danger">Please enter a valid first name</p>';
		}
	}else{
		if(document.getElementById('champ1') != null){
			document.getElementById('champ1').remove();
		}
	}
	if(document.getElementById('secondName').value.length < 1){
		if(document.getElementById('champ2') == null){
			document.getElementById('names').innerHTML += '<p id="champ2" class="text-danger">Please enter a valid last name</p>';
		}
	}else{
		if(document.getElementById('champ2') != null){
			document.getElementById('champ2').remove();
		}
	}
}

function validatePassword() {
	var pass = document.getElementById('userpass').value;
	
	if(pass.length < 7 || !/\d/.test(pass) || !/[A-Z]/.test(pass)){
		if(document.getElementById('champ3') == null){
			document.getElementById('passwordBox').innerHTML += '<p id="champ3" class="text-danger">Please enter a valid password (requires 7 or more characters with at least 1 capital and 1 number)</p>';
		}
	}else{
		if(document.getElementById('champ3') != null){
			document.getElementById('champ3').remove();
		}
	}
}

function validateEmail() {
	var emailID = document.getElementById('userEmail').value;
	atpos = emailID.indexOf("@");
	dotpos = emailID.lastIndexOf(".");

	if (atpos < 1 || ( dotpos - atpos < 2 )) {
		if(document.getElementById('champ4') == null){
			document.getElementById('emailBox').innerHTML += '<p id="champ4" class="text-danger">Please enter a valid email address</p>';
		}
	}else{
		if(document.getElementById('champ4') != null){
			document.getElementById('champ4').remove();
		}
	}
}

function validateUsername() {	
	var uname = document.getElementById('username').value;
	
	if(uname.length < 7 || !/[A-Z]/.test(uname)){
		if(document.getElementById('champ5') == null){
			document.getElementById('uname').innerHTML += '<p id="champ5" class="text-danger">Please enter a valid username (requires 7 or more characters with at least 1 capital)</p>';
		}
	}else{
		if(document.getElementById('champ5') != null){
			document.getElementById('champ5').remove();
		}
	}
}

document.getElementById('userEmail').addEventListener('blur', function() {validateEmail();}, false);

document.getElementById('firstName').addEventListener('blur', function() {validateName();}, false);
document.getElementById('secondName').addEventListener('blur', function() {validateName();}, false);

document.getElementById('userpass').addEventListener('blur', function() {validatePassword();}, false);

document.getElementById('username').addEventListener('blur', function() {validateUsername();}, false);