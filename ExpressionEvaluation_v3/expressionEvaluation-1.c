/*************************************************************************
> File Name: expressionEvaluation.c
> Description: infixexpression To postfixexpression and evaluate
> Author: Kun Chu
> Mail: chukun1997@163.com
> Created Time: August 14th, 2018
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "expressionEvaluation.h"

// Compare the priority of two operators.
int Priority(char op1, char op2) {
	if (op1 == '(')
		return -1;
	else if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/'))	//op1's priority < op2's priority 
		return -1;
	else if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))	//op1's priority > op2's priority
		return 1;
	//Op1 is a unary operator while op2 is a binary operator.
	else if ((op1 == '@' || op1 == '#') && (op2 == '+' || op2 == '-' || op2 == '*' || op2 == '/'))
		return 1;
	//In other cases, the two have equal priority.
	else return 0;
}

//Check if the character is a operator or not.
int isoperator(char op) {
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '@' || op == '#') return 1;
	else return 0;
}

//Convert a infixExpression to the postficExpression and check error.
State infixToPostfix(char *infixExpression, char postfixExpression[]) {
	int infixIndex = 0, postfixIndex = 0, numbrace = 0;
	char c, prev='s', top, pop;
   
	SequentialStackChar *s = (SequentialStackChar *)malloc(sizeof(SequentialStackChar));
	InitStack(s);                                          //Create a char stack
	postfixExpression[postfixIndex++] = ' ';

	//Traverse the infixExpression
	while (infixExpression[infixIndex] != '\0')  {         
		c = infixExpression[infixIndex];	
		//Left brace processing
		switch (c) {

			case ' ': case '\t':
				// Check the situation where there is a space follows a unary operator.
				if (prev == '@' || prev == '#') {
					printf("Error: Position:'%d'. There is a space follows a UNARY '%c'!! \n", infixIndex+1, c);
					return FAILED;
				}	break;

			case '(':
				numbrace++;
				//Check the situation like ')(' or ')    ('.
				if (prev == ')') {
					printf("Error: Position:'%d'. There is no operator between ')' and '('!! \n", infixIndex+1);
					return FAILED;
				}
				//Check the situation like '8(' or '8      ('.
				else if (isdigit(prev)) {
					printf("Error: Position:'%d'. There is no operator between the operand and '('!! \n", infixIndex+1);
					return FAILED;
				}
				//After checking right, put it into the stack.
				if (Push(s, c)==FAILED) { printf("Error:  The stack is FULL!! \n"); return FAILED; }
				prev = '(';	break;

			case ')':
				numbrace--;
				// Check the situation where ')' is at the start of the expression.
				if (prev == 's') {
					printf("Error: Position:'%d'. There is no matched '(' before ')'!!\n", infixIndex+1);
					return FAILED;
				}
				//Check the situation like '+)' or '+    )'.
				else if (isoperator(prev)) {
					if (prev == '@') prev = '+'; if (prev == '#') prev = '-';
					printf("Error: Position:'%d'. There is no operand between '%c' and ')'!! \n", infixIndex+1, prev);
					return FAILED;
				}
				//Check the situation like '()' or '(    )'.
				else if (prev == '(')  {  
					printf("Error: Position:'%d'. There is no expression between '(' and ')'!! \n", infixIndex+1);
					return FAILED;				
				}
				//After checking right, put the operators in the stack to the postfixExpression until top = '('.
				Pop(s, &pop);
				while (pop != '(') {            
					postfixExpression[postfixIndex++] = pop;
					if (Pop(s, &pop) == FAILED) {       //The corresponding left brace is not found
						printf("Error: Position:'%d'. There is no matched '(' before ')'!!\n", infixIndex+1);
						return FAILED;
					}
				}
				prev = ')';	break;

			case '+': 
				//'+' is a unary operator.
				if (prev == '(' || prev == 's') {
					if (Push(s, '@')==FAILED) { printf("Error: The stack is FULL!! \n"); return FAILED; }
					prev = '@';
				}
				//'+' is a binary operator.
				else {
					//Check the situation like '+/' or '+    /'
					if (isoperator(prev)) {
						if (prev == '@') prev = '+'; if (prev == '#') prev = '-';
						printf("Error: Position:'%d'. The operator '%c' immediately follows another operator '%c'!! \n", infixIndex+1, c, prev);
						return FAILED;
					}
					//After checking right, put it into the stack according the rules.
					if (StackEmpty(s) == SUCCEEDED) Push(s, c);
					else {
						GetTop(s, &top);
						while (StackEmpty(s) == FAILED && Priority(top, c) >= 0) {
							Pop(s, &pop); GetTop(s, &top);
							postfixExpression[postfixIndex++] = pop;   
						}
						if (Push(s, c)==FAILED) { printf("Error: The stack is FULL!! \n"); return FAILED; }
					}
					//Separate the operands.
					postfixExpression[postfixIndex++] = ' '; prev = '+';	
				}	break;

			case '-':
				//'-' is a unary operator.
				if (prev == '(' || prev == 's') {
					if (Push(s, '#')==FAILED) { printf("Error: The stack is FULL!! \n"); return FAILED; }
					prev = '#';	
				}
				//'-' is a binary operator.
				else {
					//Check the situation like '-/' or '-    /'
					if (isoperator(prev)) {
						if (prev == '@') prev = '+'; if (prev == '#') prev = '-';
						printf("Error: Position:'%d'. The operator '%c' immediately follows another operator '%c'!! \n", infixIndex+1, c, prev);
						return FAILED;
					}
					//After checking right, put it into the stack according the rules.   
					if (StackEmpty(s) == SUCCEEDED) Push(s, c);
					else {
						GetTop(s, &top);
						while (StackEmpty(s) == FAILED && Priority(top, c) >= 0) {
							Pop(s, &pop); GetTop(s, &top);
							postfixExpression[postfixIndex++] = pop;
						}
						if (Push(s, c)==FAILED) { printf("Error: The stack is FULL!! \n"); return FAILED; }
					}
					//Separate the operands.
					postfixExpression[postfixIndex++] = ' '; prev = '-';	
				}	break;

			case '*': case '/':
				//Check the situation where there is no operand between '(' and '*' or '(' and '/' or before '*' or before '/'.
				if (prev == '(') {
					printf("Error: Position:'%d'. There is no operand between '(' and '%c' !! \n", infixIndex+1, c);
					return FAILED;   
				}
				else if (prev == 's') {
					printf("Error: Position:'%d'. There is no operand before '%c' !! \n", infixIndex+1, c); 
					return FAILED; 
				}
				//Check the situation like '*-' or '*    -'
				else if (isoperator(prev)) {
					if (prev == '@') prev = '+'; if (prev == '#') prev = '-';
					printf("Error: Position:'%d'. The operator '%c' immediately follows another operator '%c'!! \n", infixIndex+1, c, prev);
					return FAILED;
				}
				//After checking right, put it into the stack according the rules.                                           
				if (StackEmpty(s) == SUCCEEDED) Push(s, c);
				else {
					GetTop(s, &top);
					while (StackEmpty(s) == FAILED && Priority(top, c) >= 0) {
						Pop(s, &pop); GetTop(s, &top);
						postfixExpression[postfixIndex++] = pop;   
					}
					if (Push(s, c)==FAILED) { printf("Error:	The stack is FULL!! \n"); return FAILED; }
				} 
				postfixExpression[postfixIndex++] = ' ';       //Separate the operands.
				prev = c; break;

			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				//Check the situation like ')8' or ')      8'.
				if (prev == ')') {
					printf("Error: Position:'%d'. There is no operator between ')' and the operand!! \n", infixIndex+1);
					return FAILED;
				}
				//Check the situation like '8 2' or '8      2'.
				if (isdigit(prev)) {
					printf("Error: Position:'%d'. There is no operator between two operands!! \n", infixIndex+1);
					return FAILED;
				}
				//Store consecutive numbers.
				while (isdigit(infixExpression[infixIndex])) {
					postfixExpression[postfixIndex++] = infixExpression[infixIndex++];
				}
				infixIndex = infixIndex-1;
				prev = infixExpression[infixIndex]; break;

			default:
				printf("Error: Position:'%d'. '%c' is an illegal character!! \n", infixIndex+1, c);
				return FAILED;
		}//end switch
		infixIndex++;
	}//end while

	//Check the last character.
	if (isoperator(prev)) {
		if (prev == '@') prev = '+'; if (prev == '#') prev = '-';
		printf("Error: Position:'%d'. There is no operand after the last operator '%c'!! \n", infixIndex, prev);
		return FAILED;
	}
	//Check the matching of the braces.
	if (numbrace != 0) {
		printf("Error: There is no matched ')' after '('!! \n");
		return FAILED;
	}
	//After the traverse and the checking is completed, pop all the operators in the stack and add them to the array.
	while (StackEmpty(s) == FAILED) {
		GetTop(s, &top);Pop(s, &pop);
		postfixExpression[postfixIndex++] = pop;
	}
	postfixExpression[postfixIndex] = '\0';
	DestroyStack(s);    //Free the stack.                   
	return SUCCEEDED;
}//end function

//Compute the value from the postfixExpression.
State computeValueFromPostfix(char *postfixExpression, double *value)
{
	int postfixIndex = 0;
	char c;
	double val = 0.0, op1, op2;

	SequentialStackDouble *s = (SequentialStackDouble *)malloc(sizeof(SequentialStackDouble));
	InitStackDouble(s);                               //Create a double stack

	//The postfixexpression array is empty, return 0 and error message.
	if (strlen(postfixExpression) == 1) { printf("Error: The input is EMPTY!! \n"); return FAILED; }

	//Traverse the postfixExpression
	while (postfixExpression[postfixIndex] != '\0') {
		c = postfixExpression[postfixIndex];
		//If c is a space or a tab or a unary plus, skip.
		if (c == ' ' || c == '\t' || c == '@') {
			postfixIndex++; continue; 
		}
		switch (c) {
			//If c is a digit, look for consecutive numbers.
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				val = c - '0'; postfixIndex++;
				while (isdigit(postfixExpression[postfixIndex])) {
					val = val * 10.0 + (postfixExpression[postfixIndex++] - '0');
				}	break;
			//if c is an operator, check which operator is and operate.
			case '+':
				if ((PopDouble(s, &op1)==SUCCEEDED) && (PopDouble(s, &op2)==SUCCEEDED)) {
					val = op1 + op2; postfixIndex++;
				}
				else {                              
					printf("Error: Position:'%d'. Too many operators in the expression!! \n", postfixIndex+1); return FAILED;
				}	break;
			case '-':   
				if ((PopDouble(s, &op1)==SUCCEEDED) && (PopDouble(s, &op2)==SUCCEEDED)) {
					val = op2 - op1; postfixIndex++;
				}
				else {                              
					printf("Error: Position:'%d'. Too many operators in the expression!! \n", postfixIndex+1); return FAILED;
				}	break;
			case '*':
				if ((PopDouble(s, &op1)==SUCCEEDED) && (PopDouble(s, &op2)==SUCCEEDED)) {
					val = op1 * op2; postfixIndex++;
				}
				else {                              
					printf("Error: Position:'%d'. Too many operators in the expression!! \n", postfixIndex+1); return FAILED;
				}	break;
			case '/':   
				if ((PopDouble(s, &op1)==SUCCEEDED) && (PopDouble(s, &op2)==SUCCEEDED)) {
					if (op1 == 0.0) { printf("Error: Position:'%d'. The divisor is 0!! \n", postfixIndex+1); return FAILED; }
					val = op2 / op1; postfixIndex++;
				}
				else {                              
					printf("Error: Position:'%d'. Too many operators in the expression!! \n", postfixIndex+1); return FAILED;
				}	break;
			case '#':
				if (PopDouble(s, &op1)==FAILED) { 
					printf("Error: Position:'%d'. Too many operators in the expression!! \n", postfixIndex+1); return FAILED; 
				}
				else { 
					val = - op1; postfixIndex++; 
				}	break;
			//in other cases, c is an illegal character/
			default:
				printf("Error: Position:'%d'. '%c' is an illegal character!! \n", postfixIndex+1, c); return FAILED;    	
		}
		//Put the result of the operation into the stack.
		if (PushDouble(s, val)==FAILED) { printf("Error: The stack is FULL!! \n"); return FAILED; }   
	}//end while

	//Pop the final result out of the stack.
	if (PopDouble(s, value)==FAILED) { 
		printf("Error: No operand in the expression!! \n"); 
		return FAILED; 
	}
	//Check if the number of operators and operands are matched.
	if (StackEmptyDouble(s)==FAILED) { 
		printf("Error: Too many operands in the expression!! \n"); 
		return FAILED; 
	}  
	DestroyStackDouble(s);   //Free the stack.             
	return SUCCEEDED;
} //end function