//header

#pragma once


const int iLength = 140;

//Structs
typedef struct item Item;
typedef struct BSTNode* link;
typedef struct BSTNode Node;

//Item
struct item {
	char buff[iLength];		//to contain the quote (will rename)
	int senderId;
	int receiverId;
	int priority;
	int seqNum;
	char inforArray[15];	//useful in project
};

struct BSTNode {
	Item msg;			//msg.buff contains the message
	link pLeft;			//left subtree
	link pRight;		//right subtree
};
