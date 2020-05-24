/* name.Extension -	Description
*
*  		Copyright 2019 Graeme Judge
*		Change Log:
*  			October 10, 1999: Source file created
*/


#pragma once

#include "TreeNode.h"
#include "TreeFunc.h"


//private variables

static link root;
static Item nullItem{ "NOT FOUND - NULL LEAF REACHED" };

//global variables



//functions

//creates a new BST node
link NEW(Item item, link left, link right) {
	link pNew = (link)malloc(sizeof(Node));
	pNew->msg = item;
	pNew->pLeft = left;
	pNew->pRight = right;
	return pNew;
}

//initializes BST
void BSTInit() {
	root = NEW(nullItem, NULL, NULL);					//initalizes with no item, no left and no right
}

//private seacrh function requires head
Item BSTSearch(link head, char* szSearchKey) {
	int rc;
	if (head == NULL) {
		return(nullItem);								//reached leaft node and didnt find what we were looking for
	}
	rc = strcmp(szSearchKey, head->msg.buff);			//comapres the string

	if (rc == 0) {
		return (head->msg);								//if they match return it
	}

	if (rc < 0) {
		return(BSTSearch(head->pLeft, szSearchKey));
	}
	else {
		return(BSTSearch(head->pRight, szSearchKey));
	}

}

//public search function (main does know where the start is)
Item Search(char* szSearchKey) {
	return BSTSearch(root, szSearchKey);
}

//private insert requires head
link BSTInsert(link head, Item item) {
	int rc;
	if (head == NULL) {
		return(NEW(item, NULL, NULL));								//reached leaft node and didnt find what we were looking for
	}
	rc = strcmp(item.buff, head->msg.buff);			//comapres the string

	if (rc < 0) { //go right
		head->pLeft = BSTInsert(head->pLeft, item);
	}
	else {
		head->pRight = BSTInsert(head->pRight, item);
	}

	return (head);
}	
 
//public insert same reason as search
void insert(Item item) {
	BSTInsert(root, item);
}

//Private print function
void BSTPrint(link head) {
	if (head == NULL) {
		return;
	}
	BSTPrint(head->pLeft);						//left
	printf("\nKey: %s\n", head->msg.buff);		//center
	BSTPrint(head->pRight);						//right
}

//public print function
void Print(void) {

}

//gets the height of the tree
int getHeight(link head) {
	int iLeftHeight, iRightHeight;

	if (head == NULL) {
		return - 1;
	}

	iLeftHeight = getHeight(head->pLeft);

	iRightHeight = getHeight(head->pLeft);
	
	if (iLeftHeight > iRightHeight) {
		return iLeftHeight + 1;
	}
	else {
		return iRightHeight + 1;
	}
}

//gets the number of nodes in the tree	
int getCount(link head) {

	if (head == NULL) {
		return 0;
	}

	return(getCount(head->pLeft) + getCount(head->pRight) + 1);

}

//gets the head of the tree
link getHead(void) {
	if (root != NULL) {
		return root;
	}
	else {
		return NULL;
	}
}

