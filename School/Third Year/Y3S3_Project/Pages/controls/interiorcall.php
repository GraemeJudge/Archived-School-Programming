<?php




	$dbhost = "localhost";
	$dbusername ="root";
	$dbpassword = "";
	$dbname = "Project6";

		//$id = $_POST['ID'];
		//$current = $_POST['Cur_Floor'];
		$destintation = $_POST['Des_Floor'];
$mysqli = new mysqli($dbhost, $dbusername, $dbpassword, $dbname);


if($mysqli->connect_error){
	echo 'Error';
	
}$sql = "INSERT INTO elevator_requests (ID, Cur_Floor, Des_Floor)
 VALUES (NULL, '0',$destintation)";
 if ($mysqli->query($sql) === TRUE) {
 // echo "New record created successfully";
} else {
  echo "Error: " . $sql . "<br>" . $mysqli->error;
}


$mysqli->close();
?>


<!DOCTYPE HTML>

<html>
	<head>
		<title>Interior Control</title>
		<link rel="stylesheet" href="../css/navbar.css">
		<link rel="stylesheet" href="../css/button.css">

		<script src="./js/remotecontrol.js"></script>
		<meta name="author" content="Connor LaGuff, Graeme Judge, Sean Berkvens" >
	</head>

	<body>
		<div class="container">
		
			<img src="../res/elevatorin.jpg"  style="width:1200px;height:800px;">
			<button class="btnc" onclick="floor1();">1</button>
			<button class="btnb" onclick="floor2();">2</button>
			<button class="btna" onclick="floor3();">3</button>
			<button class="btne">Dest:</button>
			<button class="btnd" id="floorDisplay">1</button>

		</div>
			<form method="POST" action="interiorcall.php">
	<input type="submit" value="1"name="Des_Floor"><br><br>
	<input type="submit" value="2"name="Des_Floor"><br><br>
	<input type="submit" value="3"name="Des_Floor"><br><br>
			
	</form>
		<a href="../../index.html" id="backButton">Home</a>
	</body>

</html>




