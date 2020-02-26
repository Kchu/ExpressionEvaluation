// double型
typedef struct doublestack {
	double *data;
	int maxlen;
	int top;
}doublestack;
doublestack* createStack_double(int maxlen);          //创建双精度浮点型栈
int emptyStack_double(doublestack *s);                //判断栈是否为空（0表示非空，1表示空）
void clearStack_double(doublestack *s);               //清空栈
int extendStack_double(doublestack *s);			      //扩容 
int pushStack_double(doublestack *s, double value);   //入栈
void popStack_double(doublestack *s);                 //出栈
double topStack_double(doublestack *s);				  //获取栈顶的数据
void freeStack_double(doublestack *s);			      //释放栈

// char型
typedef struct charstack {
	char *data;
	int maxlen;
	int top;
}charstack;
charstack *createStack_char(int maxlen);          //创建字符型栈
int emptyStack_char(charstack *s);                //判断栈是否为空（0表示非空，1表示空）
void clearStack_char(charstack *s);               //清空栈
int extendStack_char(charstack *s);			      //扩容 
int pushStack_char(charstack *s, char value);     //入栈
void popStack_char(charstack *s);                 //出栈
char topStack_char(charstack *s);				  //获取栈顶的数据
void freeStack_char(charstack *s);			      //释放栈