<?php
class ElevatorCar
{
	
	private $currentFloor; 
	private $destinationFloor;
	
	function __construct() {
		$this->currentFloor = 0;
		$this->destinationFloor = 0;
	}
	
	function getCurrentFloor()
    {
		return $currentFloor;
    }
	
	function setCurrentFloor($floor)
	{	
		$this->currentFloor = $floor;
	}
	
    function getDestFloor()
    {
		return $destinationFloor;
    }
	
	function setDestFloor($floor)
	{	
		$this->destinationFloor = $floor;
	}
}
?>
