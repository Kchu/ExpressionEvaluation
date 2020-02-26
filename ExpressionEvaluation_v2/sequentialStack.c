/*************************************************************************
> File Name: sequentialStack.c
> Description: sequential stack for the expression evaluation
> Author: Kun Chu
> Mail: chukun1997@163.com
> Created Time: July 30th, 2018
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "sequentialStack.h"

/* ********************************************************************************************** */
//The operation of the char stack


/*  Initialize the sequential stack
*/
State InitStack(SequentialStackChar *s) {
	if (NULL==s) {
		printf("illegal pointer!!");
		return FAILED;
	}
	s->top = -1;
	return SUCCEEDED;
}

/*  Release the memory of the sequential stack
*/
void DestroyStack(SequentialStackChar *s) {
	if (NULL==s) {
		printf("illegal pointer!!");
		return;
	}
	free(s);
	s = NULL;
}

/*  Check if the stack is empty.
Return 1 to indicate the stack is empty.
Return 0 to indicate the stack is NOT empty.
*/
State StackEmpty(SequentialStackChar *s) {
	if (NULL==s) {
		printf("illegal pointer!!");
		return 0;
	}
	return (s->top == -1 ? SUCCEEDED : FAILED);
}

/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
If the stack is full, merely return 0 to indicate an unsuccessful push.
*/
State Push(SequentialStackChar *s, ElemType e) {
	if (NULL==s) {
		printf("illegal pointer!!");
		return FAILED;
	}
	if (s->top == MaxSize) {
	    return 0;
	}
	else {
		s->top++;
		s->data[s->top] = e;
		return SUCCEEDED;
	}
}

/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
If the stack is empty, merely return 0 to indicate an unsuccessful pop.
*/
State Pop(SequentialStackChar *s, ElemType *e) {
	if (NULL==s) {
		printf("illegal pointer!!");
		return FAILED;
	}
	if (s->top == -1) {
		return FAILED;
	}
	else {
		*e = s->data[s->top];
		s->top--;
		return SUCCEEDED;
	}
}

/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
*/
State GetTop(SequentialStackChar *s, ElemType *e) {
	if (NULL==s) {
		printf("illegal pointer!!");
		return FAILED;
	}
	if (s->top == -1) {
		return FAILED;
	}
	else {
		*e = s->data[s->top];
		return SUCCEEDED;
	}
}
/* ********************************************************************************************** */

/* ********************************************************************************************** */
//The operation of the double stack

/*  Initialize the sequential stack
*/
State InitStackDouble(SequentialStackDouble *s) {
	if (NULL==s) {
		printf("illegal pointer!!");
		return FAILED;
	}
	s->top = -1;
	return SUCCEEDED;
}

/*  Release the memory of the sequential stack
*/
void DestroyStackDouble(SequentialStackDouble *s) {
	if (NULL==s) {
		printf("illegal pointer!!");
		return;
	}
	free(s);
	s = NULL;
}

/*  Check if the stack is empty.
Return 1 to indicate the stack is empty.
Return 0 to indicate the stack is NOT empty.
*/
State StackEmpty1(SequentialStackDouble *s) {
	if (NULL==s) {
		printf("illegal pointer!!");
		return 0;
	}
	return (s->top == -1 ? SUCCEEDED : FAILED);
}

/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
If the stack is full, merely return 0 to indicate an unsuccessful push.
*/
State PushDouble(SequentialStackDouble *s, ElemTypeDouble e) {
	if (NULL==s) {
		printf("illegal pointer!!");
		return FAILED;
	}
	if (s->top == MaxSize) {
		return FAILED;
	}
	s->top++;
	s->data[s->top] = e;
	return SUCCEEDED;
}

/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
If the stack is empty, merely return 0 to indicate an unsuccessful pop.
*/
State PopDouble(SequentialStackDouble *s, ElemTypeDouble *e)
{
	if (NULL==s)
	{
		printf("illegal pointer!!");
		return FAILED;
	}
	if (s->top == -1)
	{
		return FAILED;
	}
	*e = s->data[s->top];
	s->top--;
	return SUCCEEDED;
}

/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
*/
State GetTopDouble(SequentialStackDouble *s, ElemTypeDouble *e)
{
	if (NULL==s) {
		printf("illegal pointer!!");
		return FAILED;
	}
	if (s->top == -1) {
		return FAILED;
	}
	*e = s->data[s->top];
	return SUCCEEDED;
}