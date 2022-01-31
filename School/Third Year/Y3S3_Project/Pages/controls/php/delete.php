<?php
  session_start();
        if(isset($_SESSION['username']) && isset($_SESSION['password'])) {
			echo '<script src="../js/remotecontrol.js"></script>';
			readfile("../remotecontrol.html");
		
		}else{
			echo 'You need to login! Please click: <a href=\'../../accessControl/LoginPage.html\'>here</a> to log in</p> ';
		}

	$dbhost = "localhost";
	$dbusername ="root";
	$dbpassword = "";
	$dbname = "project6";


	
$mysqli = new mysqli($dbhost, $dbusername, $dbpassword, $dbname);
$id=$_REQUEST['id'];
echo $id;
$query = "DELETE FROM elevator_requests WHERE ID=$id"; 
$result = mysqli_query($mysqli,$query) or die ( mysqli_error());
header("Location: view.php");
?>