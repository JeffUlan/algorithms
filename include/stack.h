/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * STACK
 *
 * Features:
 * 1. Stack with capcity 
 * 
 * http://en.wikipedia.org/wiki/Stack_(abstract_data_type)
 *
 ******************************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** 
 * Stack has three properties. capacity stands for the maximum number of
 * elements stack can hold. Size stands for the current size of the stack and elements 
 * is the array of elements 
 */
typedef struct Stack
{
	int capacity;
	int size;
	void ** elements;
} Stack;

/*
 * createStack function takes argument the maximum number of elements the stack 
 * can hold, creates a stack according to it and returns a pointer to 
 * the stack. 
 */
inline Stack * createStack(int maxElements)
{
	/* Create a Stack */
	Stack *S;
	S = (Stack *)malloc(sizeof(Stack));
	/* Initialise its properties */
	S->elements = (void **)malloc(sizeof(void *)*maxElements);
	S->size = 0;
	S->capacity = maxElements;
	/* Return the pointer */
	return S;
}

inline void destroyStack(Stack * S)
{
	free(S->elements);
	free(S);
}

/**
 * pop an element and store in *rval
 */
inline void pop(Stack *S)
{
	/* If stack size is zero then it is empty. So we cannot pop */
	if(S->size==0)
	{
			return;
	}
	/* Removing an element is equivalent to reducing its size by one */
	else
	{
			S->size--;
	}
	return;
}

/**
 * get top element into *rval
 * returns false when the stack is empty.
 */
inline void * top(Stack *S)
{
	if(S->size==0)
	{
		return NULL;
	}
	/* Return the topmost element */
	return S->elements[S->size-1];
}

/**
 * push an element into the stack
 * returns false when stack is full.
 */
inline bool push(Stack *S, void * element)
{
	/* If the stack is full, we cannot push an element into it as there is no space for it.*/
	if(S->size == S->capacity)
	{
		return false;
	}
	else
	{
		/* Push an element on the top of it and increase its size by one*/ 
		S->elements[S->size++] = element;
		return true;
	}
}

#endif //
