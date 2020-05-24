/*  priorityQueue.h
 *  Author: Michael Galle - using notes from course textbook
 *  Description:  Interface for implementation of a priority queue
 */
#pragma once

#include "Item.h"

// Prototypes for subfunctions for Priority Queues
void fixUp(Item* a, int k); 
void fixDown(Item* a, int k, int N);
void fixDown2(Item* a, int k, int N);

// Priority Queues
void PQInit(int MaxN); 
int IsPQEmpty(void); 
void PQInsert(Item v);  
Item PQDelMax(void); 