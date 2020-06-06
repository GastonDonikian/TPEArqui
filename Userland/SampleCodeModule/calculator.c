#include "lib.h"
#include "calculator.h"

#define MAX_OPERATIONS 20
#define MAX_OPERANDS 20
	
double operandStack[MAX_OPERANDS];
char operationStack[MAX_OPERATIONS];
	
int currentOperandPosition = 0;
int currentOperationPosition = 0;

int thereWasAnError = 0;
//ERROR 0 = TODO BIEN
//ERROR 1 = MAL DADO UN NUMERO
//ERROR 2 = MAL CANTIDAD DE OPERANDOS
//ERROR 3 = MAL CANTIDAD DE NUMEROS
void calculator() {
	char c;
	char buffer[MAX_OPERATIONS + MAX_OPERANDS + 20] = {0};
	int position = 0;
	while((c = getChar()) != 'a') {
		if(c == '\b') {
			if(position != 0) {
				buffer[--position] = 0;
				putChar('\b');
			}
		}
		else if(c == '\n') {
			startOver(position,buffer);
			position = 0;
		}
		else if(c == ' ')
			putChar(' ');
		else if(isANumber(c) || isOperator(c) || c== '.' || c=='(' || c==')'){
			putChar(c);
			buffer[position++] = c;
		}
		if(position >= (MAX_OPERATIONS + MAX_OPERANDS + 20)) {
			startOver(position,buffer);
			position = 0;
		}
	}	
	putChar('=');
	char string[30];
	doubleToString(evaluate(buffer),string);
	if(thereWasAnError) {
		printf("Error: ");
		char * stringArray[4] = {"Todo bien...","Me pasaste mal un numero","Mal cantidad de operandores","Mal cantidad de numeros","Dividiste por cero"};
		printf(stringArray[thereWasAnError]);
	}
	else
		printf(string);
	printf("\tTermine\n");
	cleanEverything(position,buffer);
	calculator();
	return;
}

void cleanEverything(int position, char * buffer) {
	for(int i = 0; i < currentOperationPosition;i++)
		operationStack[i] = 0;
	for(int i = 0; i < currentOperandPosition;i++)
		operandStack[i] = 0;
	currentOperandPosition = 0;
	currentOperationPosition = 0;
	for(int i = 0; i < position;i++)
		buffer[i] = 0;
	position = 0;
	return;
}
void startOver(int position,char * buffer) { 
	for(int  i = 0; i < position; i++) {
		buffer[i] = 0;
		putChar('\b');
	}
	calculator();
}


double evaluate(char * string) {
	for(int i = 0; string[i] != 0;i++) {
		int stillInANumber = 0;
		if(isANumber(string[i])) { //ESTOY PARADO EN UN NUMERO, AVANZO HASTA QUE EL NUMER TERMINE
			operandStack[currentOperandPosition++] = stringToDouble(string + i); //AGREGO EL NUMERO A MI STACK
			while(isANumber(string[i + 1]) || string[i + 1] == '.') {
				if(string[i + 1] == '.'){
					if(stillInANumber) {
						thereWasAnError = 1;
						return;
					}
					stillInANumber = 1;
				}
				i++;
			}

		}
		else if(string[i] == '(') {
			operationStack[currentOperationPosition++] = '(';
		}
		else if(string[i] == ')') {
			while(operationStack[currentOperationPosition - 1] != '(') {
				updateStack();
			}
			operationStack[currentOperationPosition - 1] = 0;
			currentOperationPosition--;

		}
		else if(isOperator(string[i])) {
			while((currentOperationPosition != 0) && precedence(operationStack[currentOperationPosition - 1],string[i])) {
				updateStack();
			}
			operationStack[currentOperationPosition++] = string[i];
		}
		else {
			thereWasAnError = 2;
			return;
		}
	}
	while(currentOperationPosition != 0) {
		updateStack();
	}
	if(currentOperandPosition != 1){
		thereWasAnError = 3;
		return;
	}

	return operandStack[0];
}

void updateStack() {
	if(currentOperandPosition < 2) {
		thereWasAnError = 2;
		return;
	}
	double num1 = operandStack[currentOperandPosition - 2]; //AGARRO EL PRIMER NUMERO
	double num2 = operandStack[currentOperandPosition - 1]; //AGARRO EL SEGUNDO NUMERO
	char op = operationStack[currentOperationPosition-1];
	if((op == '%' || op == '/') && num2 == 0) {
		thereWasAnError = 4;
		return;
	}
	operandStack[currentOperandPosition - 2] = evaluateOperator(num1,num2,op);
	currentOperandPosition--;
	currentOperationPosition--;
}

double evaluateOperator(double num1, double num2, char op) { 
	switch(op) {
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1*num2;
		case '%':
		case '/':
			return num1/num2;
		default:
			thereWasAnError = 1;
			return;
		}
}

int operatorPrecedence(char op) { 
	if(op == '+' || op == '-')
		return 0;
	if(op == '%' || op == '*' || op == '/')
		return 1;
	if(op == '(')
		return -1;
}

int precedence(char op1,char op2) { 
	return (operatorPrecedence(op1) >= operatorPrecedence(op2));
}

int isANumber(char ch) { 
	return (ch >= '0' && ch <= '9');
}
int isOperator(char ch) { 
	return (ch == '+' || ch == '-' || ch=='*' ||ch=='/'||ch=='%') ;
 }