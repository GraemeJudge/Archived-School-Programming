/* stack.cpp
* Implements the stack ADT
* Uses code from class notes
*
*/

#include <stdlib.h>
#include <malloc.h>
#include "Item.h"
#include "stack.h"

static Item* s;					// The stack array (private)
static int iSP;					// The stack pointer (index in the stack array) (private)

void InitStack(int maxN) {		// Initialize the stack
	s = (Item*)malloc(maxN * sizeof(Item));
	iSP = 0;
}

int IsStackEmpty(void) {		// Check if the stack is empty - true when stack pointer is 0
	return(iSP == 0);
}

void StackPush(Item item) {		// Push to the stack
	s[iSP++] = item; 
}

Item StackPop(void) {			// Pop from the stack
	return (s[--iSP]);
}
