<?php
class Elevator
{
	
	protected $ElevatorNodes = []; 
	protected $ElevatorCars = [];
	
	function addNode($nodeToAdd){
		$this->ElevatorNodes[sizeof(ElevatorNodes)] = $nodeToAdd;
	}
	
	function getNode($nodeNumber)
    {
		return $this->ElevatorNodes[$nodeNumber];
    }
	
	function removeNode($nodeNumber)
	{
		unset($this->ElevatorNodes[$nodeNumber]);
	}
	
	function addCar($nodeToAdd)
	{
		$this->ElevatorCars[sizeof(ElevatorCars)] = $nodeToAdd;
	}
	
	function getCar($carNumber)
    {
		return $this->ElevatorCars[$carNumber];
    }
	
	function removeCar($carNumber)
	{
		unset($this->ElevatorCars[$carNumber]);
	}	
	
}
?>
