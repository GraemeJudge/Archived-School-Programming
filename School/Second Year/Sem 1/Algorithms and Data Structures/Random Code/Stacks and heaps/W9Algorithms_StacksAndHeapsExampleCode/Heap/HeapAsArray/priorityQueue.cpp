/*  priorityQueue.cpp
*  Author: Michael Galle - using notes from course textbook
*  Description:  Interface for implementation of a priority queue
*/

#include "priorityQueue.h"
#include <malloc.h>

// Priority Queue variables
static Item* pq;						// pointer to a priority queue (array based) of Items
static int N;							// index variable (location of the end of the array - last element in PQ)

// Prototypes for fixUp() and fixDown() base functions
void fixUp(Item* a, int k) {
	Item temp;
	while ((k > 1) && (a[k / 2].priority < a[k].priority)) {
		// swap
		temp = a[k];
		a[k] = a[k / 2];
		a[k / 2] = temp;
		// go to next parent
		k = k / 2;
	}
}

void fixDown(Item* a, int k, int N)
{
	int j;
	Item temp;
	while (2 * k <= N) {
		j = 2 * k;												// Location of left child
		if (j < N && (a[j].priority < a[j + 1].priority)) j++;  // Advance through the array as long as parent is less than left child
		if (a[k].priority > a[j].priority) break;				// Once the parent is greater than the child - break
		// swap a[j] and a[k]									// otherwise swap parent and child
		temp = a[k];
		a[k] = a[j];
		a[j] = temp;

		k = j;													// New parent to check against child = previous child that was swapped
	}
}


void fixDown2(Item* a, int k, int N) {
	int j = 2*k; 
	Item temp;
	while (j <= N) {
		// Heap condition achieved
		if ((a[j].priority < a[k].priority) && (a[j + 1].priority < a[k].priority)) { break; }

		// Left child larger than parent
		if (a[j].priority > a[k].priority) {			// child1 > parent
			// swap a[j] and a[k]
			temp = a[k];
			a[k] = a[j];
			a[j] = temp;
		
			k = j;						// new location of parent 
		}
		// Right child 2 larger than parent 
		if (a[j + 1].priority > a[k].priority) {		// child2 > parent
			// swap a[j+1] and a[k]
			temp = a[k];
			a[k] = a[j+1];
			a[j+1] = temp;

			k = j + 1;					// new location of parent 
		}
		j = 2 * k;						// new location of child1 	
	}
}



