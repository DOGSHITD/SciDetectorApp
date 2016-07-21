#include "QueueLib.h"

BOOL isEmpty(PQUEUE_NODE headPtr)
{
	return (NULL == headPtr);
}

BOOL enqueue(PQUEUE_NODE *headPtr, PQUEUE_NODE *tailPtr, CHAR *string)
{
	PQUEUE_NODE newPtr;

	newPtr =(PQUEUE_NODE) malloc(sizeof(QUEUE_NODE));

	if (NULL != newPtr) {
		memset(newPtr->buffer, 0, 100);
		strcpy_s(newPtr->buffer, string);
		newPtr->nextPtr = NULL;

		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else {
			(*tailPtr)->nextPtr = newPtr;
		}
		(*tailPtr) = newPtr;
	}
	else {
		/* error: No memory available */
		return -1;
	}

	return 0;
}

CHAR* dequeue(PQUEUE_NODE *headPtr, PQUEUE_NODE *tailPtr)
{
	CHAR *string;
	PQUEUE_NODE tempPtr;

	/* Make sure to free pointer after invoke dequeue. */
	string = (CHAR *)malloc(strlen((*headPtr)->buffer) + 1);
	memset(string, 0, strlen((*headPtr)->buffer) + 1);
	memcpy(string, (*headPtr)->buffer, strlen((*headPtr)->buffer) + 1);

	tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (NULL == *headPtr) {
		*tailPtr = NULL;
	}

	free(tempPtr);

	return string;
}