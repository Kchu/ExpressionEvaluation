#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressionEvaluation.h"
#include "sequentialStack.h"

/*************************************************************************
> File Name: expressionEvaluation.c
> Description: infixexpression To postfixexpression and evaluate
> Author: Kun Chu
> Mail: chukun1997@163.com
> Created Time: July 18sth, 2018
**************************************************************************/

// 比较两个操作符的优先级
int Precedence(char op1, char op2)
{
	if (op1 == '(')
	{
		return -1;
	}

	if (op1 == '+' || op1 == '-')   //op1优先级＜op2优先级
	{
		if (op2 == '*' || op2 == '/')
		{
			return -1;
		}
	}

	if (op1 == '*' || op1 == '/')   //op1优先级>op2优先级
	{
		if (op2 == '+' || op2 == '-')
		{
			return 1;
		}
		else                       //其他情况下二者优先级相等
		{
			return 0;
		}
	}
}

//判断是不是运算符
int IsOperator(char op)
{
	char ops[] = "+-*/";
	for (int i = 0; i < sizeof(ops) / sizeof(char); i++)
	{
		if (op == ops[i])
			return 1;
	}
	return 0;
}

//将中缀运算表达式转换成后缀运算表达式
int infixToPostfix(char *infixExpression, char postfixExpression[])
{
	int infixIndex = 0, postfixIndex = 0;
	char c;
	charstack *S = createStack_char(strlen(infixExpression));   //创建char型栈

	while (infixExpression[infixIndex] != '\0')                 //遍历中缀表达式
	{
		c = infixExpression[infixIndex];
		if (c == '(')         //若为'('则入栈
		{
			pushStack_char(S, c);
		}
		else if (c == ')')    //依次把栈中的运算符加入后缀表达式中，直到出现'('，从栈中删除
		{
			while (topStack_char(S) != '(')
			{
				postfixExpression[postfixIndex++] = topStack_char(S);
				popStack_char(S);
			}
			popStack_char(S);  //删除'(';
		}
		else if (!IsOperator(c))    //数字直接存入数组
		{
			postfixExpression[postfixIndex++] = c;
		}
		else                   
		{
		    while (emptyStack_char(S) == 0 && Precedence(topStack_char(S), c) >= 0)   //运算符
			{
				postfixExpression[postfixIndex++] = topStack_char(S);
				popStack_char(S);
			}
				pushStack_char(S, c);
				postfixExpression[postfixIndex++] = ' ';  //把数字隔开
		}//end if
		infixIndex++;
	}//end while

	 //扫描完毕，运算符依次退栈加入表达式
	while (emptyStack_char(S) == 0)
	{
		postfixExpression[postfixIndex++] = topStack_char(S);
		popStack_char(S);
	}
	postfixExpression[postfixIndex] = '\0';
	freeStack_char(S);                //释放栈
	return 1;
}//end function

int computeValueFromPostfix(char *postfixExpression, double *value)
{
	int i = 0, j;     
	char c;
	double val, op1, op2;
	doublestack *S = createStack_double(strlen(postfixExpression));  //新建double型栈
	while (postfixExpression[i] != '\0') 
	{
		c = postfixExpression[i];
		if (!IsOperator(c) && c!=' ')    //如果是数，判断后面是否也是数
		{
			val = (c - '0');
			j = i + 1;
			while (!IsOperator(postfixExpression[j]) && postfixExpression[j] != ' ')
			{
				val = val * 10.0 + (postfixExpression[j] - '0');
				j++;
			}
			i = j;
			pushStack_double(S, val);
		}
		else if (postfixExpression[i] == ' ')
		{
			i++;
		}
		else      //运算符就判断运算
		{
			op1 = 0.0, op2 = 0.0;
			val = 0.0;
			op1 = topStack_double(S);
			popStack_double(S);
			op2 = topStack_double(S);
			popStack_double(S);
			switch (c)
			{
			case '+':
				val = op1 + op2;
				break;
			case '-':
				val = op2 - op1;
				break;
			case '*':
				val = op1 * op2;
				break;
			case '/':
				val = op2 / op1;
				break;
			}
			pushStack_double(S,val);    //把运算结果压入栈中
			i++;
		}
	}//end while
	*value = topStack_double(S);        //把最终结果压入栈中
	freeStack_double(S);                //释放栈
	return 1;
}
