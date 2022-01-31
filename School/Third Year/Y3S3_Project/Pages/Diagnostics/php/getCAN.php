<?php

	$dbhost = "localhost";
	$dbusername ="root";
	$dbpassword = "";
	$dbname = "project6";

	$mysqli = new mysqli($dbhost, $dbusername, $dbpassword, $dbname);
	
	//destination floors
	$sqlget = "SELECT * FROM elevator_can_messages";
	$data = $mysqli->query($sqlget);
	
	$allMessages ="";
	$lastID = 0;
	while($row = $data->fetch_assoc()) {
		$allMessages.="Message from Node ID: 0x". dechex($row['NodeID']). " With Data: 0x".  dechex($row['Data']). ",";
		$lastID = $row['ID'];
	}
	
	echo $lastID. ",". $allMessages;
	$mysqli->close();
?>