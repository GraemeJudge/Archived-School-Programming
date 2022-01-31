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
$query = "SELECT * from elevator_requests where ID='".$id."'"; 
$result = mysqli_query($mysqli, $query) or die ( mysqli_error());
$row = mysqli_fetch_assoc($result);
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Update Request</title>
<link rel="stylesheet" href="css/style.css" />
</head>
<body>
<div class="form">
<p><a href="view.php">View Requests</a>
| <a href="insert.php">Insert New Request</a> 
| <a href="logout.php">Logout</a></p>
<h1>Update Request</h1>
<?php
$status = "";
if(isset($_POST['new']) && $_POST['new']==1)
{

	$id=$_REQUEST['id'];

    $Cur_Floor = $_REQUEST['Cur_Floor'];
	$Des_Floor = $_REQUEST['Des_Floor'];
    $Timestamp = $_REQUEST['Timestamp'];
$update="update elevator_requests set ID='".$id."',
Cur_Floor='".$Cur_Floor."', Des_Floor='".$Des_Floor."',
Timestamp='".$Timestamp."' where ID='".$id."'";



try{
mysqli_query($mysqli, $update) or die(mysqli_error());}catch(Exception $e){  
        echo 'Caught exception: ',  $e->getMessage(), "\n";
    }

if($Cur_Floor <= 3 && $Des_Floor <= 3){
$status = "Request Updated Successfully. </br></br>
<a href='view.php'>View Updated Requests</a>";
echo '<p style="color:#FF0000;">'.$status.'</p>';
}else{
	$status = "Request Updated Unsuccessfully. </br></br>
ERROR: There is only 3 Floors, Please select to Insert New Request and Enter a Valid Value";
	
	
	echo '<p style="color:#FF0000;">'.$status.'</p>';
	
}}else {
?>
<div>
<form name="form" method="post" action=""> 
<input type="hidden" name="new" value="1" />


<p><input type="text" name="Cur_Floor" placeholder="Enter Current Floor" 
required value="<?php echo $row['Cur_Floor'];?>" /></p>
<p><input type="text" name="Des_Floor" placeholder="Enter Destination Floor" 
required value="<?php echo $row['Des_Floor'];?>" /></p>
<p><input type="text" name="Timestamp" placeholder="Enter Timestamp" 
required value="<?php echo $row['Timestamp'];?>" /></p>
<p><input name="submit" type="submit" value="Update" /></p>
</form>
<?php } ?>
</div>
</div>
</body>
</html>
