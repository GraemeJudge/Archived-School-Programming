/* main.cpp
 * Author: Michael A. Galle (with code from textbook) 
 * Description: Implementation of a heap based priority queue
 */

#include <stdio.h>
#include <stdlib.h>
#include "Item.h";
#include "priorityQueue.h"

int main() {

	Item myItem;
	Item DequeuedItem;
	int numItems = 0;
	int i, k;

	printf("How many items would you like to add to the Priority Queue?: ");
	scanf_s("%d", &numItems);

	// Initialize the number of nodes in the Priority Queue
	PQInit(numItems); 
	
	// Add items to heap giving priority to each add to bottom of heap (will later heapify)
	for (i = 1; i <= numItems; i++) {
		//Read an item and add to end of heap
		printf("\nEnter text for node: ");											// Optional: additional contents in node
		scanf_s("%s", myItem.itemText, sizeof(myItem.itemText));					// Optional: additional contents in node
		printf("\nEnter a priority from 1 to 20: ");									  
		scanf_s("%d", &myItem.priority, sizeof(myItem.priority)); 
		PQInsert(myItem);								// Add node to end of heap
	}

	// DeQueue the Priority Queue while re-heapifying the tree
	printf("\n\nDeQueuing the tree in Priority Order (from Highest to lowest)\n");
	for (i = 1; i <= numItems; i++) {
		DequeuedItem = PQDelMax();
		printf("Priority: %d,  Message: %s\n", DequeuedItem.priority, DequeuedItem.itemText);
		//printf("Priority: %d \n", DequeuedItem.priority);
	}

	system("pause");
	return 0;
}