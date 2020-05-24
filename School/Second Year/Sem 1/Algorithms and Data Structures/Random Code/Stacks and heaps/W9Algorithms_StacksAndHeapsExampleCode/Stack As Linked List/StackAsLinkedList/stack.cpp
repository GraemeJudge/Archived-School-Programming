/* stack.cpp
* Implements the stack ADT as a linked list
* Uses code from class notes
*
*/

#include <stdlib.h>
#include <malloc.h>
#include "Item.h"
#include "stack.h"

static link head;				// private pointer to head of stack

link NEW(Item item, link next) {	// Create a new node to add to the stack
	link x = (link)malloc(sizeof(STACKnode));	// Allocate space for the node variable
	x->item = item;								// Place item into new node variable x->item  
	x->next = next;								// Set the pointer to the next node in x->next as next (points to previous head pointer)
	return(x);									// Return the newly created node
}

void InitStack(int maxN) {		// Initialize the stack
	head = NULL;
}

int IsStackEmpty(void) {		// Check if head pointer is NULL (stack still empty when head is NULL
	return(head == NULL);
}

void StackPush(Item item) {		// Push to the stack
	head = NEW(item, head);		// New item pushed to head and its next pointer points to previous head 
}

Item StackPop(void) {			// Pop from the stack
	Item item = head->item;		// Store the item currently at the head in temporary variable 'item'
	link t = head->next;		// Store the link from the current head to the next node (the next head) in variable 't'
	free(head);					// Removes the node at head
	head = t;					// head now points to 't' which is the address of the next node (i.e. the new head)
	return (item);				// Return the contents of the old 'head' (stored in the temp variable item)
}
