/*  priorityQueue.h
 *  Author: Michael Galle - using notes from course textbook
 *  Description:  Interface for implementation of a priority queue
 */
#pragma once

#include "Item.h"

// Prototypes
void fixUp(Item* a, int k); 
void fixDown(Item* a, int k, int N);
void fixDown2(Item* a, int k, int N);

// Priority Queues
