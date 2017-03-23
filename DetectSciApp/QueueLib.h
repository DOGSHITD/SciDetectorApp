#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

/*
  Queue struct.
*/
typedef struct _QUEUE_NODE {
	char buffer[100];
	struct _QUEUE_NODE *nextPtr;
}QUEUE_NODE,* PQUEUE_NODE;

/*
  Decode from queue.
*/
CHAR* dequeue(PQUEUE_NODE *headPtr, PQUEUE_NODE *tailPtr);

/*
  Encode to queue.
*/
BOOL enqueue(PQUEUE_NODE *headPtr, PQUEUE_NODE *tailPtr, CHAR *string);

/*
  Judge if the queue is empty.
*/
BOOL isEmpty(PQUEUE_NODE headPtr);
