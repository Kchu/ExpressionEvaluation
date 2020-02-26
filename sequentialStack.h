// double��
typedef struct doublestack {
	double *data;
	int maxlen;
	int top;
}doublestack;
doublestack* createStack_double(int maxlen);          //����˫���ȸ�����ջ
int emptyStack_double(doublestack *s);                //�ж�ջ�Ƿ�Ϊ�գ�0��ʾ�ǿգ�1��ʾ�գ�
void clearStack_double(doublestack *s);               //���ջ
int extendStack_double(doublestack *s);			      //���� 
int pushStack_double(doublestack *s, double value);   //��ջ
void popStack_double(doublestack *s);                 //��ջ
double topStack_double(doublestack *s);				  //��ȡջ��������
void freeStack_double(doublestack *s);			      //�ͷ�ջ

// char��
typedef struct charstack {
	char *data;
	int maxlen;
	int top;
}charstack;
charstack *createStack_char(int maxlen);          //�����ַ���ջ
int emptyStack_char(charstack *s);                //�ж�ջ�Ƿ�Ϊ�գ�0��ʾ�ǿգ�1��ʾ�գ�
void clearStack_char(charstack *s);               //���ջ
int extendStack_char(charstack *s);			      //���� 
int pushStack_char(charstack *s, char value);     //��ջ
void popStack_char(charstack *s);                 //��ջ
char topStack_char(charstack *s);				  //��ȡջ��������
void freeStack_char(charstack *s);			      //�ͷ�ջ