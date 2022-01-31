<?php
        session_start();
        if(isset($_SESSION['username']) && isset($_SESSION['password'])) {
			echo '<script src="../js/floorControl.js" defer></script>';
			readfile("../remotecontrol.html");
		
		}else{
			echo 'You need to login! Please click: <a href=\'../../accessControl/LoginPage.html\'>here</a> to log in</p> ';
		}

?>