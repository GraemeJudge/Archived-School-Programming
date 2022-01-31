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
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Request Log</title>
<link rel="stylesheet" href="css/style.css" />
</head>
<body>
<div class="form">
<p>
| <a href="insert.php">Insert New Request</a> 
| <a href="logout.php">Logout</a></p>
<h2>Request Log</h2>
<table width="100%" border="1" style="border-collapse:collapse;">
<thead>
<tr>
<th><strong>ID</strong></th>
<th><strong>Current Floor</strong></th>
<th><strong>Destination Floor</strong></th>
<th><strong>Timestamp</strong></th>
<th><strong>Edit</strong></th>
<th><strong>Delete</strong></th>
</tr>
</thead>
<tbody>
<?php

$sel_query="Select * from elevator_requests;";
$result = mysqli_query($mysqli,$sel_query);
while($data = mysqli_fetch_array($result)) { ?>
  <tr>
    <td><?php echo $data['ID']; ?></td>
    <td><?php echo $data['Cur_Floor']; ?></td>
    <td><?php echo $data['Des_Floor']; ?></td> 
	<td><?php echo $data['Timestamp']; ?></td>   	
    <td><a href="edit.php?id=<?php echo $data['ID']; ?>">Edit</a></td>
    <td><a href="delete.php?id=<?php echo $data['ID']; ?>">Delete</a></td>
  </tr>	
<?php } ?>
</tbody>
</table>
</div>
<button onclick="topFunction()" id="topBtn" title="Go to top">Back to Top</button>
</body>
</html>