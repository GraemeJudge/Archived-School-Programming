/* stack.h
 * Interface for the stack ADT implementation
 * Uses code from class notes
 *
 */
#pragma once

#include "Item.h"				// Node structs used in stack

void InitStack(int maxN);		// Initializes an arracy for the stack
int IsStackEmpty(void);			// checks if stack is empty
void StackPush(Item item);		// Pushes an item to the stack
Item StackPop(void);			// Returns item at head of the stack