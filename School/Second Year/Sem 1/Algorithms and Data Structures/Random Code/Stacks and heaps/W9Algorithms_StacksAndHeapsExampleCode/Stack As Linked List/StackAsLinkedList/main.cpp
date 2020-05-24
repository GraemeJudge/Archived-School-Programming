/* mainline for testing the stack algorithm based on linked lists
 * Uses code from the Stacks and Heaps lecture
 *
 */

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Item.h"
#include "stack.h"


int main() {

	Item myItem;
	int numItems = 0, i;

	printf("How many items would you like to push to the linked list based stack?\n");
	scanf("%d", &numItems);

	InitStack(numItems);									// Initialize stack to hold numItems

	for (i = 0; i < numItems; i++) {
		// Read an item 
		printf("Enter some text: \n");
		scanf("%s", myItem.itemText);			            // Scanf requires the address (pointer)

		// Push to stack
		StackPush(myItem);
	}

	printf("The text you entered in LIFO (reverse) order is: \n");

	while (!IsStackEmpty()) {
		printf("You entered: %s\n", StackPop().itemText);  // %s uses pointer
	}
	system("pause");
	return(0);
}