<?php

class Node
{

	protected $name; 
	protected $id;
	
	
	function __construct($name, $id) {
		$this->name = $name;
		$this->id = $id;
	}
	
	function getName(){
		return $this->name;
	}
	
	function getID(){
		return $this->id;
	}

	function checkValue()
	{	
		return 0;
	}	
	
	function setValue($value)
	{	
	
	}	
}


?>
