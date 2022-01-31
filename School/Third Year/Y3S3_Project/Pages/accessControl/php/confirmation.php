<?php
    session_start();   
    // Get data submitted in the form
    $username = $_POST['user'];
    $password = $_POST['pass']; 
    $authenticated = false; 

    if(file_exists('../json/users.json')){
		$usersArray = json_decode(file_get_contents('../json/users.json'));

		foreach($usersArray->loginInfo as $data){
			if (($username == $data->Username)) {
                if($password == $data->Password) {
                    $authenticated = true;
                }
            }
		}
		
		if($authenticated) {
			$_SESSION['username'] = $username;
			$_SESSION['password'] = $password; 
			echo '<h2>Congrats ' . $username . ' you are authenticated</h2>';
			echo '<p>Please click <a href=\'../../controls/php/members.php\'>here</a> to go to the members only page</p>';
		} else {
			echo '<p>Sorry but you are not authenticated!</p><br><p>Please request access <a href="../RequestAccess.html">here</a></p> ';
		}
	}
?>

