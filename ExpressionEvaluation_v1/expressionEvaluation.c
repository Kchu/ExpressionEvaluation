#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "expressionEvaluation.h"
#include "sequentialStack.h"

/*************************************************************************
> File Name: expressionEvaluation.c
> Description: infixexpression To postfixexpression and evaluate
> Author: Kun Chu
> Mail: chukun1997@163.com
> Created Time: July 18sth, 2018
**************************************************************************/

// Compare the precedence of two operators
int Precedence(char op1, char op2)
{
	if (op1 == '(')
	{
		return -1;
	}

	if (op1 == '+' || op1 == '-')   //op1's priority < op2's priority
	{
		if (op2 == '*' || op2 == '/')
		{
			return -1;
		}
	}

	if (op1 == '*' || op1 == '/')   //op1's priority > op2's priority
	{
		if (op2 == '+' || op2 == '-')
		{
			return 1;
		}
		else                       //In other cases, the two have equal priority
		{
			return 0;
		}
	}
    return 0;
}

//Check if it is an operator
int isoperator(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/')
		return 1;
	else
		return 0;
}

//Convert the infixexpression to a postfixexpression
int infixToPostfix(char *infixExpression, char postfixExpression[])
{
	int infixIndex = 0, postfixIndex = 0, maxlen = strlen(infixExpression);
	int tmp, flag;
	char c;
	if (maxlen == 0)     //If the suffix expression array is empty,return 0 and error message.
	{
		printf("Empty!! \n");
		return 0;
	}

	charstack *S = createStack_char(maxlen);              //Create a char stack

	while (infixExpression[infixIndex] != '\0')           //Traverse the infix expression
	{
		c = infixExpression[infixIndex];
		if (c == '(')         //If it is '(' then push it into the stack
		{
			pushStack_char(S, c);
		}
		else if (c == ')')    // Add the operators in the stack to the suffix expression 
			                  // until c=='(', remove '(' from the stack
		{
			while (topStack_char(S) != '(')
			{
				if (emptyStack_char(S))    //The corresponding left parenthesis was not found, 
					                       //returning 0 and outputting an error message
				{
					printf("Improper braces!! \n");
					return 0;
				}
				postfixExpression[postfixIndex++] = topStack_char(S);
				popStack_char(S);
			}
			popStack_char(S);   //delete '(';
		}
		else if (isdigit(c))    //If it is a number, check if there is a space and a number after it.
		{
			tmp = infixIndex + 1;
			flag = 0;
			while (!isoperator(infixExpression[tmp]))          //Stop if operator is found
			{
				if (isdigit(infixExpression[tmp]) && flag==1)  //There is a space between the number and the number
				{
					printf("Spaces!! \n");
					return 0;
				}
				else if (infixExpression[tmp] == ' ')   //If there is a space, assign 1 to flag
				{
					tmp++;
					flag = 1;
				}
				else break;
			}
			postfixExpression[postfixIndex++] = c;
		}
		else if (c == ' ')                               //If c is a space, then skip.
		{
			infixIndex++;
			continue;
		}
		else if(isoperator(c))                          //Operator processing
		{
			if (strlen(postfixExpression) == 0)         //Only operator
			{
				printf("Insufficient operands!! \n");
				return 0;
			}
			tmp = infixIndex + 1;
			while (!isdigit(infixExpression[tmp]))      //There's no number between the operator.
			{
				if (isoperator(infixExpression[tmp]) || infixExpression[tmp]=='\0')
				{
					printf("Insufficient operands!! \n");
					return 0;
				}
				else if (infixExpression[tmp] == ' ')
					 tmp++;
				else
					 break;
			}
		    while (emptyStack_char(S) == 0 && Precedence(topStack_char(S), c) >= 0) //Determine the priority between 
				                                                                    //the current operator and the top-of-stack operator

			{
				postfixExpression[postfixIndex++] = topStack_char(S);
				popStack_char(S);
			}
				pushStack_char(S, c);
				postfixExpression[postfixIndex++] = ' ';       //Separate the numbers.
		}
        else
        {
             printf("illegal character!! \n");
             return 0;
        }
		infixIndex++;
     }	        //end while

	 //After the scan is completed, the operators are sequentially unstacked and added to the expression.
	while (emptyStack_char(S) == 0)
	{
		if (topStack_char(S) == '(')   //If there is '(' in the stack, the braces do not match.
		{
			printf("Improper braces!! \n");
			return 0;
		}
		postfixExpression[postfixIndex++] = topStack_char(S);
		popStack_char(S);
	}
	postfixExpression[postfixIndex] = '\0';
	freeStack_char(S);                      //Free the stack
	if (strlen(postfixExpression) == 0)     //If the suffix expression array is empty, 
											//return 0 and error message.
	{
		printf("Empty!! \n");
		return 0;
	}
	return 1;
}//end function

int computeValueFromPostfix(char *postfixExpression, double *value)
{
	int postfixIndex = 0, tmp;
	char c;
	double val, op1, op2;
	doublestack *S = createStack_double(strlen(postfixExpression));  //create a double stack
	while (postfixExpression[postfixIndex] != '\0')
	{
		c = postfixExpression[postfixIndex];
		if (isdigit(c))                     //If c is a number, judge whether it is also a number
		{
			val = (c - '0');
			tmp = postfixIndex + 1;
			while (isdigit(postfixExpression[tmp]) && postfixExpression[tmp] != ' ')
			{
				val = val * 10.0 + (postfixExpression[tmp] - '0');
				tmp++;
			}
			postfixIndex = tmp;
			pushStack_double(S, val);
		}
		else if (postfixExpression[postfixIndex] == ' ')   //If c is a space, then skip.
		{
			postfixIndex++;
		}
		else                                   //If c is an operator,judge which operator is and then operate.
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
			pushStack_double(S,val);    //Push the result of the operation into the stack
			postfixIndex++;
		}
	}//end while
	*value = topStack_double(S);        //Push the final result onto the stack
	freeStack_double(S);                //Free the stack
	return 1;
} //end function
