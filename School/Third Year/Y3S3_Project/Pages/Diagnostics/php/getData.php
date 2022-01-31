<?php

	$dbhost = "localhost";
	$dbusername ="root";
	$dbpassword = "";
	$dbname = "project6";

	$mysqli = new mysqli($dbhost, $dbusername, $dbpassword, $dbname);
	
	//destination floors
	$sqlget = "SELECT Cur_Floor FROM elevator_requests WHERE Cur_Floor=1";
	$floor1 = $mysqli->query($sqlget);
	
	$sqlget = "SELECT Cur_Floor FROM elevator_requests WHERE Cur_Floor=2";
	$floor2 = $mysqli->query($sqlget);
	
	$sqlget = "SELECT Cur_Floor FROM elevator_requests WHERE Cur_Floor=3";
	$floor3 = $mysqli->query($sqlget);
	
	//Request floor
	$sqlget = "SELECT Des_Floor FROM elevator_requests WHERE Des_Floor=1";
	$floor1req = $mysqli->query($sqlget);
	
	$sqlget = "SELECT Des_Floor FROM elevator_requests WHERE Des_Floor=2";
	$floor2req = $mysqli->query($sqlget);
	
	$sqlget = "SELECT Des_Floor FROM elevator_requests WHERE Des_Floor=3";
	$floor3req = $mysqli->query($sqlget);
	
	//last hour requests
	
	date_default_timezone_set('America/Winnipeg');
	$timestamp = date('Y-m-d h:i:s.000000', time());
	
	$sqlget = "SELECT Des_Floor, Timestamp FROM elevator_requests WHERE Timestamp>'".$timestamp. "' ORDER BY ID DESC";
	$lasthour = $mysqli->query($sqlget);
	
	$allLastHour="";
	if($lasthour->num_rows > 0){
		while($row = $lasthour->fetch_assoc()) {
			$allLastHour .= ",". $row['Des_Floor'].",".$row['Timestamp'];
		}
	}
	
	//last 10 requests
	$sqlget = "SELECT Des_Floor FROM elevator_requests WHERE NOT Des_Floor=0 ORDER BY ID DESC LIMIT 10";
	$last10 = $mysqli->query($sqlget);
	$last10 = $mysqli->query($sqlget);
	
	$recent10="";
	$i = 0;
	if ($last10->num_rows > 0) {
		while($row = $last10->fetch_assoc()) {
			$recent10 .= ",". $row['Des_Floor'];
			$i+=1;
		}
	}
	while($i<10){
		$recent10 .= ",0";	
		$i+=1;
	}
		
	echo $floor1->num_rows. ','. $floor2->num_rows. ','. $floor3->num_rows. ','. $floor1req->num_rows. ','. $floor2req->num_rows. ','. $floor3req->num_rows. $recent10. ",". $lasthour->num_rows. $allLastHour;
	
	$mysqli->close();
?>