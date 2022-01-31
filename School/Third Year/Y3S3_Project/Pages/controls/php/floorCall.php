<?php




	$dbhost = "localhost";
	$dbusername ="root";
	$dbpassword = "";
	$dbname = "project6";

	//$id = $_POST['ID'];
	$dest = $_POST['Des_Floor'];
	echo $dest;
	
	//$destintation = $_POST['Des_Floor'];
	$mysqli = new mysqli($dbhost, $dbusername, $dbpassword, $dbname);


if($mysqli->connect_error){
	echo 'Error';
	
}$sql = "INSERT INTO elevator_requests (ID, Cur_Floor, Des_Floor, Timestamp)
 VALUES (NULL, '0', $dest,CURRENT_TIMESTAMP)";
 if ($mysqli->query($sql) === TRUE) {
 // echo "New record created successfully";
} else {
  echo "Error: " . $sql . "<br>" . $mysqli->error;
}


$mysqli->close();
?>
