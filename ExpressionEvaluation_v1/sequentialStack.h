// double stack
typedef struct doublestack {
	double *data;
	int maxlen;
	int top;
}doublestack;
doublestack* createStack_double(int maxlen);          //create a double stack
int emptyStack_double(doublestack *s);                //Judge whether the stack is empty or not£¨0 means not£¬1 means yes£©
void clearStack_double(doublestack *s);               //Clear the stack
void extendStack_double(doublestack *s);			  //Extand the stack
int pushStack_double(doublestack *s, double value);   //Put into the stack 
void popStack_double(doublestack *s);                 //Put out of the stack
double topStack_double(doublestack *s);				  //Get the top element of the stack
void freeStack_double(doublestack *s);			      //Free the stack

// char stack
typedef struct charstack {
	char *data;
	int maxlen;
	int top;
}charstack;
charstack *createStack_char(int maxlen);          //create a char stack
int emptyStack_char(charstack *s);                //Judge whether the stack is empty or not£¨0 means not£¬1 means yes£©
int fullStack_char(charstack *s);                 //Judge whether the stack is full or not£¨0 means not£¬1 means yes£©
void clearStack_char(charstack *s);               //Clear the stack
void extendStack_char(charstack *s);			  //Extand the stack
int pushStack_char(charstack *s, char value);     //Put into the stack
void popStack_char(charstack *s);                 //Put out of the stack
char topStack_char(charstack *s);				  //Get the top element of the stack
void freeStack_char(charstack *s);			      //Free the stack
