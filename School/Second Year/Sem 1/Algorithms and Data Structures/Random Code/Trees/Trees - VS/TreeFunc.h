//header

#pragma once

#include "TreeNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//function prototypes
link NEW(Item item, link left, link right);			//creates a new BST node

void BSTInit();										//initializes BST

Item BSTSearch(link head, char* szSearchKey);		//private seacrh function requires head

Item Search(char* szSearchKey);						//public search function (main does know where the start is)

link BSTInsert(link head, Item item);				//private insert requires head

void insert(Item item);								//public insert same reason as search

void BSTPrint(link head);							//Private print function

void Print(void);									//public print function

int getHeight(link head);							//gets the height of the tree

int getCount(link head);							//gets the number of nodes in the tree	

link getHead(void);									//gets the head of the tree