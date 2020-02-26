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

// �Ƚ����������������ȼ�
int Precedence(char op1, char op2)
{
	if (op1 == '(')
	{
		return -1;
	}

	if (op1 == '+' || op1 == '-')   //op1���ȼ���op2���ȼ�
	{
		if (op2 == '*' || op2 == '/')
		{
			return -1;
		}
	}

	if (op1 == '*' || op1 == '/')   //op1���ȼ�>op2���ȼ�
	{
		if (op2 == '+' || op2 == '-')
		{
			return 1;
		}
		else                       //��������¶������ȼ����
		{
			return 0;
		}
	}
}

//�ж��ǲ��������
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

//����׺������ʽת���ɺ�׺������ʽ
int infixToPostfix(char *infixExpression, char postfixExpression[])
{
	int infixIndex = 0, postfixIndex = 0;
	char c;
	charstack *S = createStack_char(strlen(infixExpression));   //����char��ջ

	while (infixExpression[infixIndex] != '\0')                 //������׺���ʽ
	{
		c = infixExpression[infixIndex];
		if (c == '(')         //��Ϊ'('����ջ
		{
			pushStack_char(S, c);
		}
		else if (c == ')')    //���ΰ�ջ�е�����������׺���ʽ�У�ֱ������'('����ջ��ɾ��
		{
			while (topStack_char(S) != '(')
			{
				postfixExpression[postfixIndex++] = topStack_char(S);
				popStack_char(S);
			}
			popStack_char(S);  //ɾ��'(';
		}
		else if (!IsOperator(c))    //����ֱ�Ӵ�������
		{
			postfixExpression[postfixIndex++] = c;
		}
		else                   
		{
		    while (emptyStack_char(S) == 0 && Precedence(topStack_char(S), c) >= 0)   //�����
			{
				postfixExpression[postfixIndex++] = topStack_char(S);
				popStack_char(S);
			}
				pushStack_char(S, c);
				postfixExpression[postfixIndex++] = ' ';  //�����ָ���
		}//end if
		infixIndex++;
	}//end while

	 //ɨ����ϣ������������ջ������ʽ
	while (emptyStack_char(S) == 0)
	{
		postfixExpression[postfixIndex++] = topStack_char(S);
		popStack_char(S);
	}
	postfixExpression[postfixIndex] = '\0';
	freeStack_char(S);                //�ͷ�ջ
	return 1;
}//end function

int computeValueFromPostfix(char *postfixExpression, double *value)
{
	int i = 0, j;     
	char c;
	double val, op1, op2;
	doublestack *S = createStack_double(strlen(postfixExpression));  //�½�double��ջ
	while (postfixExpression[i] != '\0') 
	{
		c = postfixExpression[i];
		if (!IsOperator(c) && c!=' ')    //����������жϺ����Ƿ�Ҳ����
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
		else      //��������ж�����
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
			pushStack_double(S,val);    //��������ѹ��ջ��
			i++;
		}
	}//end while
	*value = topStack_double(S);        //�����ս��ѹ��ջ��
	freeStack_double(S);                //�ͷ�ջ
	return 1;
}
