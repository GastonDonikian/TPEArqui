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
}

double evaluate(char * string) {
	int stillInANumber = 0;

	for(int i = 0; string[i] != 0;i++) {
		if(isANumber(string[i])) { //ESTOY PARADO EN UN NUMERO, AVANZO HASTA QUE EL NUMER TERMINE
			operandStack[currentOperandPosition++] = stringToDouble(string[i]); //AGREGO EL NUMERO A MI STACK
			while(isANumber(string[i]) || string[i] == '.') {
				if(string[i] == '.')
					if(stillInANumber) {
						thereWasAnError = 1;
						return;
					}
				i++;
			}
		}
		else if(string[i] == '(') {
			operationStack[currentOperationPosition++] = '(';
		}
		else if(string[i] == ')') {
			while(operationStack[currentOperationPosition] != '(') {
				updateStack();
			}
		}
		else if(isOperator(string[i])) {
			while(operationStack != 0 && precedence(string[i],operationStack[currentOperandPosition - 1])) {
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
	if(currentOperandPosition != 0){
		thereWasAnError = 3;
		return;
	}

	return operandStack[currentOperandPosition];
}

void updateStack() {
		if(currentOperandPosition < 2) {
			thereWasAnError = 3;
			return;
		}
		double num1 = operandStack[currentOperandPosition - 2]; //AGARRO EL PRIMER NUMERO
		double num2 = operandStack[currentOperandPosition - 1]; //AGARRO EL SEGUNDO NUMERO
		operandStack[currentOperandPosition - 2] = evaluateOperator(num1,num2,operationStack[currentOperationPosition-1]);
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
}

int precedence(char op1,char op2) { //ME DICE SI OP1 TIENE MAYOR PRECEDENCIA QUE OP2
	return (op1 >= op2);
}

int isANumber(char ch) {
	return (ch >= '0' && ch <= '9');
}
int isOperator(char ch) {
	return (ch == '+' || ch == '-' || ch=='*' ||ch=='/'||ch=='%') ;
 }