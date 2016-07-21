#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

typedef struct _QUEUE_NODE {
	char buffer[100];
	struct _QUEUE_NODE *nextPtr;
}QUEUE_NODE,* PQUEUE_NODE;

CHAR* dequeue(PQUEUE_NODE *headPtr, PQUEUE_NODE *tailPtr);
BOOL enqueue(PQUEUE_NODE *headPtr, PQUEUE_NODE *tailPtr, CHAR *string);
BOOL isEmpty(PQUEUE_NODE headPtr);