/*************************************************************************
> File Name: sequentialStack.c
> Description: sequential stack for the expression evaluation
> Author: Kun Chu
> Mail: chukun1997@163.com
> Created Time: July 13th, 2018
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "sequentialStack.h"

/* ********************************************************************************************** */
//The operation of the char stack

//Create a char stack
charstack *createStack_char(int maxlen)
{
	charstack *s;

	if ((s = (charstack *)malloc(sizeof(charstack))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	if ((s->data = (char *)malloc(maxlen * sizeof(char))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	s->maxlen = maxlen - 1;
	s->top = -1;
	return s;
}

//Judge whether the stack is empty or not£¨0 means not£¬1 means yes£©
int emptyStack_char(charstack *s)
{
	return (s->top == -1 ? 1 : 0);
}

//Judge whether the stack is full or not£¨0 means not£¬1 means yes£©
int fullStack_char(charstack *s)
{
	return (s->top >= (s->maxlen) ? 1 : 0);
}

//Clear the stack
void clearStack_char(charstack *s)
{
	s->top = -1;
}

//Extend the stack
void extendStack_char(charstack *s)
{
	int increase;
	printf("Please enter the length you want to extend:  \n");
	scanf("%d", &increase);
	s->data = realloc(s->data, (s->top + 1 + increase) * sizeof(char));
	s->maxlen = s->top + increase;
}

//Put into the stack
int pushStack_char(charstack *s, char value)
{
	int t;
	if (fullStack_char(s))
	{
		printf("Do you want to extend it? 1/0 \n");
		scanf("%d", &t);
		if (t == 1)
		{
			extendStack_char(s);
		}
		else
			return 0;
	}
	s->top++;
	s->data[s->top] = value;
	return 1;
}

//Put out of the stack.
void popStack_char(charstack *s)
{
	s->top--;
}

// Get the top element of the stack
char topStack_char(charstack *s)
{
	return s->data[s->top];
}

//Free the stack
void freeStack_char(charstack *s)
{
	free(s->data);
	s->data = NULL;
	free(s);
	s = NULL;
}
/* ********************************************************************************************** */

/* ********************************************************************************************** */
//The operation of the double stack

//Create the double stack
doublestack *createStack_double(int maxlen)
{
	doublestack *s;

	if ((s = (doublestack *)malloc(sizeof(doublestack))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	if ((s->data = (double *)malloc(maxlen * sizeof(double))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	s->maxlen = maxlen - 1;
	s->top = -1;
	return s;
}

//Judge whether the stack is empty or not£¨0 means not£¬1 means yes£©
int emptyStack_double(doublestack *s)
{
	return (s->top == -1 ? 1 : 0);
}

//Judge whether the stack is full or not£¨0 means not£¬1 means yes£©
int fullStack_double(doublestack *s)
{
	return (s->top >= (s->maxlen) ? 1 : 0);
}

//Clear the stack
void clearStack_double(doublestack *s)
{
	s->top = -1;
}

//Extend the stack
void extendStack_double(doublestack *s)
{
	int increase;
	printf("Please enter the length you want to extend:  \n");
	scanf("%d", &increase);
	s->data = realloc(s->data, (s->top + 1 + increase) * sizeof(double));
	s->maxlen = s->top + increase;
}

//Put into the stack
int pushStack_double(doublestack *s, double value)
{
	int t;
	if (fullStack_double(s))
	{
		printf("Do you want to extend it? 1/0 \n");
		scanf("%d", &t);
		if (t == 1)
		{
			extendStack_double(s);
		}
		else
			return 0;
	}
	s->top++;
	s->data[s->top] = value;
	return 1;
}

//Put out of the stack
void popStack_double(doublestack *s)
{
	s->top--;
}

// Get the top element of the stack
double topStack_double(doublestack *s)
{
	return s->data[s->top];
}

//Free the stack
void freeStack_double(doublestack *s)
{
	free(s->data);
	s->data = NULL;
	free(s);
	s = NULL;
}
