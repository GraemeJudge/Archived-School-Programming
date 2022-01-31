<?php
class User
{
	private $username; 
	private $password;
	private $authenticated = false;
	
	function __construct($username, $password) {
		$this->username = $username;
		$this->password = $password;
	}
	
    function login()
    {
		//Start the session for the user
		session_start();  
		
		//This username and password is temp the project website credentials are still saved in json
		if (($this->username == 'admin')) {
			if($this->password == 'root') {
				$this->authenticated = true;
			}
		}
		//Check if the username and passwords match the login info
		if($authenticated) {
			//Save the info into the session
			$_SESSION['username'] = $this->username;			
			$_SESSION['password'] = $this->password; 
			//Congratulat the user on a job well done
			echo '<h2>Congrats ' . $this->username . ' you are authenticated</h2>';
			echo '<p>Please click <a href=\'BrokenLink/members.php\'>here</a> to go to the members only page</p>';
		} else {
			echo '<p>Sorry but you are not authenticated!</p><br><p>Please request access <a href="../RequestAccess.html">here</a></p> ';
			throw new Exception('Login failed');
		}
    }
	
	function logout()
	{	
		session_start();  				// Required for every page where a session is called or declared
		session_destroy();  			// Destroys a session

		echo "You have been logged out. Click <a href='MoreBrokenLinks.html'>here</a> to login again";
	}

	function getAuthenticated()
	{	
		return $authenticated;
	}	
}
?>
