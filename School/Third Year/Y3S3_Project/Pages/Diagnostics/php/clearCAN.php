<?php

	$dbhost = "localhost";
	$dbusername ="root";
	$dbpassword = "";
	$dbname = "project6";

	$mysqli = new mysqli($dbhost, $dbusername, $dbpassword, $dbname);
	
	$sql = "TRUNCATE TABLE elevator_can_messages;";
	$mysqli->query($sql);
	
	$mysqli->close();
?>