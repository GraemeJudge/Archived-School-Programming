/* mainline for testing the stack algorithm
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

// Choose ONE of the following examples to implement a stack as an array
#define EXAMPLE_1    //uncomment to use    // Multiple items pushed to stack are output in LIFO (reverse) order
//#define EXAMPLE_2		// uncomment to use - This function evaluates Postfix expressions
//#define EXAMPLE_3		// uncomment to use - This function evaluates converts infox to postfix expressions 

int main() {


#ifdef EXAMPLE_1
	Item myItem;
	int numItems = 0, i;

	printf("How many items would you like to push to the stack?\n");
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

#endif

 
#ifdef EXAMPLE_2	
	char a[] = "1 15 20 + +";  // Can get from user if desired
	int N = strlen(a);
	int i;  
	InitStack(N);			// Make room for N items in the stack (one for each character in a[] to ensure enough room)
	Item myItem;			// Temporary Item used for addition and multiplication

	for (i = 0; i < N; ++i) {
		if (a[i] == '+') { 
			myItem.num = StackPop().num + StackPop().num;
			StackPush(myItem); 
		}
		if (a[i] == '*') {
			myItem.num = StackPop().num * StackPop().num;
			StackPush(myItem);
		}
		// Convert from asci char representation to integer (i.e. '1' -> 1 OR '15' -> 15)
		if (isdigit(a[i])) {		
			myItem.num = (a[i] - '0');
			StackPush(myItem);
			while (isdigit(a[i + 1])) {									// Take care of multidigit numbers
				myItem.num = (10 * StackPop().num) + (a[++i] - '0');    // The term (a[++i] - '0') converts and ASCII character number into an integer
				StackPush(myItem);										// The term (10*StackPop()) allows for numbers with multiple digits
			}
		}
	}

	printf("The evaluated postfix expression: '1 15 20 + +' = %d \n\n", StackPop().num);
	/*
	// Case the string is not completely evaluatable i.e. a[] = "1 15 20 +"
	printf("The numbers left on the stack are: \n");  
	while (!IsStackEmpty()) {
		printf("%d ", StackPop().num);  
	}
	*/

#endif


#ifdef EXAMPLE_3
	int i;						// for loop counter
	char a[] = "( 20 + 15 )";
	int N = strlen(a);
	InitStack(N);
	Item myItem;				// Temporary Item used for addition and multiplication
	printf("Converting infix expression ( 20 + 15 ) to postfix: ");
	for (i = 0; i < N; i++) {
		if (a[i] == ')') printf(" %c ", StackPop().operation);
		if (a[i] == '+' || a[i] == '*') {
			myItem.operation = a[i];
			StackPush(myItem);
		}
		if (isdigit(a[i])) printf("%c", a[i]);
		if (a[i] == ' ') printf(" ");				// include spaces between numbers
	} // end for all characters
	printf("\n");
#endif

	system("pause"); 
	return 0; 
}