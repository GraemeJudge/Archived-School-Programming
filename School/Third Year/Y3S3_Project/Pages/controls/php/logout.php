<?php
session_start();  // Required for every page where a session is called or declared
session_destroy();  // Destroys a session

echo "You have been logged out. Click <a href='../../accessControl/LoginPage.html'>here</a> to login again";

?>