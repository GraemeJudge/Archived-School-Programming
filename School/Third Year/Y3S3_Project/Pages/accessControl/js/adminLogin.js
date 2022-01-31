var elUsername = document.getElementById('usernameInput');
var elUsernameMsg = document.getElementById('Uinput');

var elPassword = document.getElementById('userPassword');
var elPasswordMsg = document.getElementById('Pinput');

function checkInput(minLength, lengthToCheck, responseMessage) {
    if (lengthToCheck.value.length < minLength) {
			responseMessage.innerHTML += '<p>Input must be ' + minLength + ' or more characters</p>';
	}
}

elUsername.addEventListener('blur', function() {checkInput(7, elUsername, elUsernameMsg);}, false);
elPassword.addEventListener('blur', function() {checkInput(7, elPassword, elPasswordMsg);}, false);

window.addEventListener('load', function() {elUsername.focus();}, false);