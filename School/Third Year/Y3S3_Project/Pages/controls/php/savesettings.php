<?php


	$dbhost = "localhost";
	$dbusername ="root";
	$dbpassword = "";
	$dbname = "project6";



    


$mysqli = new mysqli($dbhost, $dbusername, $dbpassword, $dbname);

$sel_query="Select Cur_Floor, Des_Floor from elevator_requests ORDER BY ID DESC ;";
$result = mysqli_query($mysqli,$sel_query);
$results = mysqli_fetch_array($result) ;
echo $results['Cur_Floor'].",".$results['Des_Floor'];
	



?>
