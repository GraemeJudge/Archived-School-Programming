<?php
require_once('User.php');
require_once('Elevator.php');
require_once('ElevatorCar.php');
require_once('FloorNode.php');

$user = new User("admin", "root");

$ele = new Elevator();

$ele->addNode(new FloorNode(0x1));
$ele->addNode(new FloorNode(0x2));
$ele->addNode(new FloorNode(0x3));

$ele->addCar(new ElevatorCar());

$ele->getCar(0)->setCurrentFloor(1);
$ele->getCar(0)->setDestFloor(1);


try{
	$user->login();
}catch (Exception $e) {
	echo 'Caught exception: ',  $e->getMessage(), "\n";
}


?>
