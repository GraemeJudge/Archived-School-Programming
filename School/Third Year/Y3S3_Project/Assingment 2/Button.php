<?php

class Button extends Node
{	

	protected $buttonState = 0;

	function checkValue()
	{	
		return $buttonState;
	}	
	
	function setValue($value)
	{	
		$this->buttonState = $value;
	}	
}


?>
