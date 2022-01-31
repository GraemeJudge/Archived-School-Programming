<?php

	$FirstName = $_POST['fname'];
    $LastName = $_POST['lname']; 

	$username = $_POST['user'];
    $password = $_POST['pass']; 

	$Email = $_POST['email'];
    $Comment = $_POST['requestReason']; 
	
	
	echo "<p><b>New user request with the following details: </b></p>";
	echo "<b>First Name:</b> $FirstName<br>";
	echo "<b>Last Name:</b> $LastName<br>";
	echo "<b>Username:</b> $username<br>";
	echo "<b>Password:</b> $password<br>";
	echo "<b>Email:</b> $Email<br>";
	echo "<b>Reason for requesting:</b> $Comment<br>";
	
	
	
?>

