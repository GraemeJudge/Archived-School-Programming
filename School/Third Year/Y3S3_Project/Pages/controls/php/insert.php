<?php
  session_start();
        if(isset($_SESSION['username']) && isset($_SESSION['password'])) {
			echo '<script src="../js/remotecontrol.js"></script>';
			try{
			readfile("../remotecontrol.html");
			}catch 
		}else{
			echo 'You need to login! Please click: <a href=\'../../accessControl/LoginPage.html\'>here</a> to log in</p> ';
		}

	$dbhost = "localhost";
	$dbusername ="root";
	$dbpassword = "";
	$dbname = "project6";

	
$mysqli = new mysqli($dbhost, $dbusername, $dbpassword, $dbname);

$status = "";
if(isset($_POST['new']) && $_POST['new']==1){
   
   	$sqlget = "SELECT ID FROM elevator_requests WHERE ID=".$_REQUEST['ID'];
	$confirm = $mysqli->query($sqlget);
	if($confirm->num_rows == 0){
		
		$ID =$_REQUEST['ID'];
		$Cur_Floor = $_REQUEST['Cur_Floor'];
		$Des_Floor = $_REQUEST['Des_Floor'];
		$Timestamp = $_REQUEST['Timestamp'];
		$ins_query="insert into elevator_requests
		(`ID`,`Cur_Floor`,`Des_Floor`,`Timestamp`)values
		('$ID','$Cur_Floor','$Des_Floor','$Timestamp')";
		try{
			if($Cur_Floor <= 3 && $Des_Floor <= 3){
				mysqli_query($mysqli,$ins_query)
				or die(mysql_error());
				$status = "New Record Inserted Successfully.
				</br></br><a href='view.php'>View Updated Requests</a>";
			}else{
				throw new UserInputException('This ID is already in use');
			}
		} catch (Exception | UserInputException $e) {
			echo 'Caught exception: ',  $e->getMessage(), "\n";
		}
	}else{
		echo "ERROR: ID is already in use, Please try a different ID";
	}
}

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Insert New Request</title>
<link rel="stylesheet" href="css/style.css" />
</head>
<body>
<div class="form">
<p>
| <a href="view.php">View Requests</a> 
| <a href="logout.php">Logout</a></p>
<div>
<h1>Insert New Request</h1>
<form name="form" method="post" action=""> 
<input type="hidden" name="new" value="1" />
<p><input type="text" name="ID" placeholder="Enter ID" required /></p>
<p><input type="text" name="Cur_Floor" placeholder="Enter Current Floor" required /></p>
<p><input type="text" name="Des_Floor" placeholder="Enter Destination Floor" required /></p>
<p><input type="text" name="Timestamp" placeholder="Enter Timestamp" required /></p>
<p><input name="submit" type="submit" value="Submit" /></p>
</form>
<p style="color:#FF0000;"><?php echo $status; ?></p>
</div>
</div>
</body>
</html>
