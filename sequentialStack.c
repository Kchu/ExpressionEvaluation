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
//double 类型栈的操作

//创建char类型栈
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

//判断栈是否为空（0表示非空，1表示空）
int emptyStack_char(charstack *s)
{
	return (s->top == -1 ? 1 : 0);
}

//判断栈是否为满（0表示非满，1表示满）
int fullStack_char(charstack *s)
{
	return (s->top >= (s->maxlen) ? 1 : 0);
}

//清空栈
void clearStack_char(charstack *s)
{
	s->top = -1;
}

//对栈进行扩容
int extendStack_char(charstack *s)
{
	int increase;
	printf("Please enter the length you want to extend:  \n");
	scanf("%d", &increase);
	s->data = realloc(s->data, (s->top + 1 + increase) * sizeof(char));
	s->maxlen = s->top + increase;
}

//入栈
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

//出栈
void popStack_char(charstack *s)
{
	//void *value;
	//value = &(s->data[s->top]);
	s->top--;
	//return value;
}

// 获取栈顶的数据
char topStack_char(charstack *s)
{
	//void *e = s->data + s->top * s->data_size;
	//return s->data + s->top * s->data_size;
	return s->data[s->top];
}

//释放栈
void freeStack_char(charstack *s)
{
	free(s->data);
	s->data = NULL;
	free(s);
	s = NULL;
}
/* ********************************************************************************************** */

/* ********************************************************************************************** */
//double 类型栈的操作

//创建栈
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

//判断栈是否为空（0表示非空，1表示空）
int emptyStack_double(doublestack *s)
{
	return (s->top == -1 ? 1 : 0);
}

//判断栈是否为满（0表示非满，1表示满）
int fullStack_double(doublestack *s)
{
	return (s->top >= (s->maxlen) ? 1 : 0);
}

//清空栈
void clearStack_double(doublestack *s)
{
	s->top = -1;
}

//对栈进行扩容
int extendStack_double(doublestack *s)
{
	int increase;
	printf("Please enter the length you want to extend:  \n");
	scanf("%d", &increase);
	s->data = realloc(s->data, (s->top + 1 + increase) * sizeof(double));
	s->maxlen = s->top + increase;
}

//入栈
int pushStack_double(doublestack *s, double value)
{
	int t;
	if (fullStack_char(s))
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

//出栈
void popStack_double(doublestack *s)
{
	//void *value;
	//value = &(s->data[s->top]);
	s->top--;
	//return value;
}

// 获取栈顶的数据
double topStack_double(doublestack *s)
{
	return s->data[s->top];
}

//释放栈
void freeStack_double(doublestack *s)
{
	free(s->data);
	s->data = NULL;
	free(s);
	s = NULL;
}
