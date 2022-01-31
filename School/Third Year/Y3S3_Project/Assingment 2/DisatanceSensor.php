<?php

class DistanceSensor Extends Node
{

	protected $distance = 0;

	function checkValue()
	{	
		return $distance;
	}	
	
	function setValue($value)
	{	
		$this->distance = $value;
	}	
}


?>
