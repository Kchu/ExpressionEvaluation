/*************************************************************************
> File Name: expressionEvaluation.c
> Description: infixexpression To postfixexpression and evaluate
> Author: Kun Chu
> Mail: chukun1997@163.com
> Created Time: July 30th, 2018
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "expressionEvaluation.h"

// Compare the priority of two operators.
int Priority(char op1, char op2) {
	if (op1 == '(') {
		return -1;
	}
	else if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/'))  {  //op1's priority < op2's priority 
		return -1;
	}
	else if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))  {  //op1's priority > op2's priority
		return 1;
	}
	//Op1 is a unary operator while op2 is a binary operator.
	else if ((op1 == '@' || op1 == '#') && (op2 == '+' || op2 == '-' || op2 == '*' || op2 == '/')) {
		return 1;
	}
	//In other cases, the two have equal priority.
	else  {      
		return 0;
	}
}

//Check whether the character is an operator or not.
int isoperator(char op) {
	if (op == '+' || op == '-' || op == '*' || op == '/')
		return 1;
	else
		return 0;
}

//Get the next effective character of the current index.
int getNext(char *infixExpression, int infixIndex){
	int temp = infixIndex + 1;
	while (infixExpression[temp] == ' ' && infixExpression[temp]!='\0') {
		temp++;
	}
	return temp;
}

//Get the previous effective character of the current index.
int getPrev(char *infixExpression, int infixIndex){
	int temp = infixIndex - 1;
	while (infixExpression[temp] == ' ') {
		temp--;
	}
	return temp;
}

//Check the character is whether a control character or not.
int iscontrol(char c) {
	if ((c>=0 && c<=9) || (c>=13 && c<=31) || c==127)  return 1;
	else  return 0;
}

//Convert a infixExpression to the postficExpression and check error.
State infixToPostfix(char *infixExpression, char postfixExpression[]) {
	int infixIndex = 0, postfixIndex = 0, tmp1, tmp2;
	char c, top, pop;
   
	SequentialStackChar *s = (SequentialStackChar *)malloc(sizeof(SequentialStackChar));
	InitStack(s);                                          //Create a char stack
	postfixExpression[postfixIndex++] = ' ';

	//Traverse the infixExpression
	while (infixExpression[infixIndex] != '\0')  {         
		c = infixExpression[infixIndex];
		tmp1 = getPrev(infixExpression, infixIndex);
		tmp2 = getNext(infixExpression, infixIndex);
		//Left brace processing
		if (c == '(') {
			//Check the situation like '()' or '(    )'.
			if (infixExpression[tmp2]==')')  {  
				printf("Error:	Position:'%d'. There is no expression between '(' and ')'!! \n", infixIndex+1);
				return FAILED;				
			}
			//After checking right, put it into the stack.
			if (!Push(s, c))  {                 
				printf("Error:	The stack is FULL!! \n");
				return FAILED;
			}
		}

		//Space processing
		else if (isspace(c));          //If c is a space, do nothing.

		//Right brace processing
		else if (c == ')')  {	
			//Put the operators in the stack to the postfixExpression until top = '('.
			if (!Pop(s, &pop)) {           //The corresponding left brace is not found
					printf("Error:	Position:'%d'. There is no matched '(' before ')'!!\n", infixIndex+1);
					return FAILED;
				}
			while (pop != '(') {            
				postfixExpression[postfixIndex++] = pop;
				if (!Pop(s, &pop)) {       //The corresponding left brace is not found
					printf("Error:	Position:'%d'. There is no matched '(' before ')'!!\n", infixIndex+1);
					return FAILED;
				}
			}//end while
			//Check the situation like ')(' or ')    ('.
			if (infixExpression[tmp2] == '(') {
				printf("Error:	Position:'%d'. There is no operator between ')' and '('!! \n", infixIndex + 1);
				return FAILED;
			}
		}//end else if (c == ')')

		//Operand processing
		else if (isdigit(c)) {
				//Check the situation like ')8' or ')      8'.
				if (infixExpression[tmp1] == ')' && tmp1>=0) {
					printf("Error:	Position:'%d'. There is no operator between the ')' and the operand !! \n", infixIndex+1);
					return FAILED;
				}
				//Check the situation where there are one more spaces between the oprends.
				else if (isdigit(infixExpression[tmp2]) && tmp2 - infixIndex >1) { 
					printf("Error:	Position:'%d'. There is no operator between two operands!! \n", infixIndex+1);
					return FAILED;
				}
				
				//Check the situation like '8(' or '8      ('.
				else if (infixExpression[tmp2] == '(') {
					printf("Error:	Position:'%d'. There is no operator between the operand and '('!! \n", infixIndex+1);
					return FAILED;
				}
			postfixExpression[postfixIndex++] = c;
		}//end else if (isdigit(c))

		//Operator processing
		else if (isoperator(c)) {
			
			//Check the operator is whether a unary operator or not.
			//Entering the unary operation.
			if (infixExpression[tmp1] == '(' || tmp1 == -1) {   
				//Check which operator is and operate.
				switch (c) {
				case '+':   if (!Push(s, '@')) {
								printf("Error:	The stack is FULL!! \n");
								return FAILED;
							}   break;
				case '-':   if (!Push(s, '#')) {
								printf("Error:	The stack is FULL!! \n");
								return FAILED;
							}   break;
				//When it comes to other operator, return 0.
				default:	if (infixExpression[tmp1] == '(')
								printf("Error:	Position:'%d'. There is no operand between '(' and '%c' !! \n", infixIndex+1, c);   
					        else
					        	printf("Error:	Position:'%d'. There is no operand before '%c' !! \n", infixIndex+1, c); 
							return FAILED;
				}
				//Check the situation where a space follows a unary operator.
				if (tmp2 - infixIndex>1) {
					printf("Error:	Position:'%d'. There is a space follows a UNARY '%c'!! \n", infixIndex+1, c);
					return FAILED;
				}
				//Check the situation where there's no number after the operator.
				if (infixExpression[tmp2] == '\0') {
					printf("Error:	Position:'%d'. There is no operand after '%c'!! \n", infixIndex+1, c);
					return FAILED;
				}
				//Check the situation like '+)'.
				else if (infixExpression[tmp2] == ')') {
					printf("Error:	Position:'%d'. There is no operand between '%c' and ')'!! \n", infixIndex + 1, c);
					return FAILED;
				}
				//Check the situation where there's no number between the operator.  '+-'
				else if (isoperator(infixExpression[tmp2])) {
						printf("Error:	Position:'%d'. The operator '%c' immediately follows another operator '%c'!! \n", tmp2 + 1, infixExpression[tmp2], c);
						return FAILED;
				}
			}

			//Entering the binary operation
			else {
				//Check the situation where there's no number after the operator.
				if (infixExpression[tmp2] == '\0') {
					printf("Error:	Position:'%d'. There is no operand after the last operator '%c'!! \n", infixIndex+1, c);
					return FAILED;								
				}	
				//Check the situation like '+)'.
				else if (infixExpression[tmp2] == ')') {
					printf("Error:	Position:'%d'. There is no operand between '%c' and ')'!! \n",infixIndex+1, c);
					return FAILED;
				}
				//Check the situation where there's no number between the operator.  '+-'
				else if (isoperator(infixExpression[tmp2])) {
					printf("Error:	Position:'%d'. The operator '%c' immediately follows another operator '%c'!! \n", tmp2 + 1, infixExpression[tmp2], c);
					return FAILED;
				}
				//After checking right, determine the priority between the current operator and the top-of-stack operator                                             
				GetTop(s, &top);
				while (StackEmpty(s) == 0 && Priority(top, c) >= 0) {
					if (!Pop(s, &pop)) {
						printf("Error:	The stack is EMPTY!! \n");
						return FAILED;
					}
					GetTop(s, &top);
					postfixExpression[postfixIndex++] = pop;
				}
				if (!Push(s, c)) {
					printf("Error:	The stack is FULL!! \n");
					return FAILED;
				}   
				postfixExpression[postfixIndex++] = ' ';       //Separate the operands.	
			}//end else
		}//end else if (isoperator(c))

		//In other cases, the character is illegal.
		else if (iscontrol(c)) {
			printf("Error:	Position:'%d'. There is a control character whose ASCII is '%d' !! \n", infixIndex+1, c);
			return FAILED;
		}
		else {
			printf("Error:	Position:'%d'. '%c' is an illegal character!! \n", infixIndex+1, c);
			return FAILED;
		}

		infixIndex++;
	}//end while

	//After the traverse is completed, pop all the operators in the stack and add them to the expression.
	while (StackEmpty(s) == 0) {
		GetTop(s, &top);
		if (top == '(') {       //If there is '(' in the stack, the brace is not matched.
		
			printf("Error:	There is no matched ')' after '('!! \n");
			return FAILED;
		}
		if (!Pop(s, &pop)) {
			printf("Error:	The stack is EMPTY!! \n");
			return FAILED;
		}
		postfixExpression[postfixIndex++] = pop;
	}

	postfixExpression[postfixIndex] = '\0';
	DestroyStack(s);                        //Free the stack
	return SUCCEEDED;
}//end function

//Compute the value from the postfixExpression.
State computeValueFromPostfix(char *postfixExpression, double *value)
{
	int postfixIndex = 0, tmp;
	char c;
	double val, op1, op2;

	SequentialStackDouble *s = (SequentialStackDouble *)malloc(sizeof(SequentialStackDouble));
	InitStackDouble(s);                               //Create a double stack

	if (1 == strlen(postfixExpression)) {        //The postfixexpression array is empty, return 0 and error message.
		printf("Error:	The input is EMPTY!! \n");
		return FAILED;
	}

	//Traverse the postfixExpression
	while (postfixExpression[postfixIndex] != '\0') {
		c = postfixExpression[postfixIndex];
		//If c is a number, judge whether the next character is also a number or not.
		if (isdigit(c)) {
			val = (c - '0');
			tmp = postfixIndex + 1;
			while (isdigit(postfixExpression[tmp]) && postfixExpression[tmp] != ' ') {
				val = val * 10.0 + (postfixExpression[tmp] - '0');
				tmp++;
			}
			postfixIndex = tmp;
			if (!PushDouble(s, val)) {
				printf("Error:	The stack is FULL!! \n");
				return FAILED;
			}
		}
		//If c is a space, skip.
		else if (isspace(postfixExpression[postfixIndex]))   postfixIndex++;  
		//If c is an operator, judge which operator is and operate.
		else if (isoperator(c)) {
			if (PopDouble(s, &op1) && PopDouble(s, &op2)) { //The situation where oprends are matched
				switch (c) {
					case '+':   val = op1 + op2;   break;
					case '-':   val = op2 - op1;   break;
					case '*':   val = op1 * op2;   break;
					case '/':   if (op1 == 0.0) {
									printf("Error:	The divisor is 0!! \n");
									return FAILED;
								}
								val = op2 / op1;   break;
				}
				if (!PushDouble(s, val)) {           //Push the result of the operation into the stack
					printf("Error:	The stack is FULL!! \n");
					return FAILED;
				}       
				postfixIndex++;
			}
			else {                              //The situation where the oprends are not matched.
				printf("Error:	There are too many operators in the expression!! \n");
				return FAILED;
			}
			
		}
		// c is a unary plus
		else if (c == '@') postfixIndex++;
		// c is a unary minus
		else if (c == '#') {
			if (!PopDouble(s, &op1)) {              
				printf("Error:	The stack is EMPTY!! \n");
				return FAILED;
			}
			val = 0 - op1;
			if (!PushDouble(s, val)) {
				printf("Error:	The stack is FULL!! \n");
				return FAILED;
			}           
			postfixIndex++;
		}
		// In other cases, the expression is illegal.
		else {
			printf("Error:	The expression is illegal!! \n");
			return FAILED;
		}    
		
	}//end while
	
	if (!PopDouble(s, value)) {           //Pop the final result out of the stack.
		printf("Error:	The stack is FULL!! \n");
		return FAILED;
	}                 
	DestroyStackDouble(s);                //Free the stack.
	return SUCCEEDED;
} //end function