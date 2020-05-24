

#define _CRT_SECURE_NO_WARNINGS


#include "TreeNode.h"
#include "TreeFunc.h"

int main() {
	Item* p = NULL;
	int num;
	char buffer[4];				//buffer to hod 4 nodes

	BSTInit();

	//input from user

	printf("How many nodes to put in the tree? ");
	while (scanf("%d", &num) != 1) {
		printf("\nplease enter an integer!\n");
		while (getchar() != '\n');
	}

	//fill BST - user to enter letters from a to z
	for (int i = 0; i < num; i++)
	{
		p = (Item*)malloc(sizeof(Item));
		printf("item %d ", i);
		scanf("%s", buffer);
		buffer[1] = '\0';
		strcpy(p->buff, buffer);
		insert(*p);
	}



	printf("\nPrinting BST in order\n");
	BSTPrint(getHead());

	printf("\nSearch BST for the last inserted ite,\n");
	if (Search(p->buff).buff) {
		printf("\nfound the last item in the tree \n");
	}
	else {
		printf("\ndidnt done found the las item in the tree we gots an issue\n");
	}
}