<?php
class FloorNode
{
	public floorNum = 0;
	public nodeID;
	
	function __construct($nodeIDValue) {
		$this->nodeID = $nodeIDValue;
	}
	
	function callElevator($carNumber)
    {
		$this->ElevatorCars[$carNumber]->setDestFloor($floorNum);
    }

}
?>
