#pragma once

typedef struct item Item; 
struct item {
	char itemText[30]; 
	int num; 
};

typedef struct STACKnode* link;
struct STACKnode {
	Item item;
	link next;
};
