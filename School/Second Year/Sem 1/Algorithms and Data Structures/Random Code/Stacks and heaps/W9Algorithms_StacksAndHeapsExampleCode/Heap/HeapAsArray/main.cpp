/* main.cpp
 * Author: Michael A. Galle (with code from textbook) 
 * Description: Implementation of a heap based priority queue
 */

#include <stdio.h>
#include <stdlib.h>
#include "Item.h";
#include "priorityQueue.h"


#define TOP_DOWN	 // uncomment to use TOP_DOWN heapify							// Confirm using heap on slide 53
//#define BOTTOM_UP		// uncomment to use BOTTOM_UP heapify							// Confirm using heap on slide 50

int main() {

	Item myItem;
	int numItems = 0;
	int i, k;

	printf("How many items would you like in the heap?: ");
	scanf_s("%d", &numItems);

	// Initialize the number of nodes in the heap
	Item* a = (Item*)malloc((numItems+1) * sizeof(Item));	// Don't use index 0 of array (need parent at i and children at 2i and 2i+1)

	// Add items to heap giving priority to each add to bottom of heap (will later heapify)
	for (i = 1; i <= numItems; i++) {
		// Read an item and add to end of heap
		//printf("Enter text for node: ");				// Optional: additional contents in node
		//scanf("%s", myItem.itemText);					// Optional: additional contents in node
		printf("Enter a priority from 1 to 20: ");		// Use heap on slide 50 to confirm bottom-up and heap on slide 53 to confirm top-down  
		scanf_s("%d", &myItem.priority); 
		a[i] = myItem;									// Add node to end of heap
	}

	// Show current order of heap
	printf("\n\nCurrent order of heap - BEFORE heapify operation\n");
	for (i = 1; i <= numItems; i++) {
		printf("%d\n", a[i].priority);					
	}

	// Test Bottom up heapify
	#ifdef BOTTOM_UP
	for (k = numItems; k > 1; k--) {
		fixUp(a, k);
	}
	printf("\nBOTTOM UP HEAPIFY OPERATION\n");
	printf("\n\nOrder of heap - AFTER Bottom up heapify operation\n");
	for (i = 1; i <= numItems; i++) {
		printf("%d\n", a[i].priority);
	}
	#endif

	// Test Top down heapify
	#ifdef TOP_DOWN
	printf("\nTOP DOWN HEAPIFY OPERATION\n");
	for (k = 1; k < numItems; k++) {
		fixDown(a, k, numItems);
	}
	printf("\n\nOrder of heap - AFTER Top Down heapify operation\n");
	for (i = 1; i <= numItems; i++) {
		printf("%d\n", a[i].priority);
	}
	#endif
			
	system("pause");
	return 0;
}