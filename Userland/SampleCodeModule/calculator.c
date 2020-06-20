#include <stdint.h>
#include "lib.h"
#include "calculator.h"

#define MAX_OPERATIONS 20
#define MAX_OPERANDS 20
	
double operandStack[MAX_OPERANDS];
char operationStack[MAX_OPERATIONS];
char buffer[MAX_OPERATIONS + MAX_OPERANDS + 100] = {0};
int position = 0;
int currentOperandPosition = 0;
int currentOperationPosition = 0; //VARIABLES GLOBALES PARA MANEJAR LOS STACKS
int welcomeMessage = 1;
int thereWasAnError = 0; // HABLA ENTRE LA CALCULADORA Y EL ANALIZADOR PARA SABER SI HUBO ALGUN ERROR CON LA EXPRESION
//ERROR 0 = TODO BIEN
//ERROR 1 = MAL DADO UN NUMERO
//ERROR 2 = MAL CANTIDAD DE OPERANDOS
//ERROR 3 = MAL CANTIDAD DE NUMEROS
//ERROR 4 = DIVIDISTE POR CERO 
//ERROR 5 = NOT AN OPERATOR

void calculator() { //FUENTE DE "FRONT-END" DE LA CALCULADORA
	setUpDown(0);
	if(welcomeMessage) {
		welcomeMessage = 0;
		printf("En esta calculadora solo se \npueden usar los simbolos:\n");
		printf("+ - * / % = 1 2 3 4 5 6 7 8 9 0\n");
		printf("Ademas de parentesis ( )\n");
		printf("Para indicar precedencia\n");
		printf("No es necesario utilizar espacio\n\n");	
		//printf("Utilizando el backspace\nse borra un caracter\n");
		//printf("Utilizando el enter borra\nuna linea entera\n");
		welcomeMessage = 0;
	}	
	thereWasAnError = 0;

	while(1) {
		char c;
		while((c = getChar()) != '=') { 
			if(c == '\b') {
				if(position != 0) {
					buffer[--position] = 0;
					putChar('\b');
				}
			}
			else if(c == '\n') {
				startOver(); 
				position = 0;
			}
			else if(isANumber(c) || isOperator(c) || c== '.' || c=='(' || c==')'){
				putChar(c);
				buffer[position++] = c;
			}
			if(position >= (MAX_OPERATIONS + MAX_OPERANDS + 20)) 
				startOver(); 
		}	
		putChar('=');

		char string[30];
		doubleToString(evaluate(buffer),string);
		if(thereWasAnError) {
			printf("Error: ");
			char * stringArray[5] = {"Todo bien...","Me pasaste mal un numero","Mal cantidad de operadores","Mal cantidad de numeros","Dividiste por cero"};
			printf(stringArray[thereWasAnError]);
			thereWasAnError = 0;
		}

		else
			printf(string);

		putChar('\n');
		cleanEverything(); 
	}
}

void cleanEverything() { 
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


void startOver() { 
	for(int  i = 0; i < position; i++) {
		buffer[i] = 0;
		putChar('\b');
	}
}


double evaluate(char * string) {
	thereWasAnError = 0; 
	for(int i = 0; string[i] != 0;i++) { 
		if(thereWasAnError)
			return 0;
		int stillInANumber = 0;
		if((string[i] == '-' && isANumber(string[i+1])) ||isANumber(string[i])) {

			if(string[i] == '-') {
				operandStack[currentOperandPosition++] = ((double)-1)*stringToDouble(string + ++i); 
				operationStack[currentOperationPosition++] = '+';
			}
			else
				operandStack[currentOperandPosition++] = stringToDouble(string + i);
			while(isANumber(string[i + 1]) || string[i + 1] == '.') {
				if(string[i + 1] == '.'){
					if(stillInANumber) {
						thereWasAnError = 1;
						return 0;
					}
					stillInANumber = 1;
				}
				i++;
			}

		} 

		else if(string[i] == '(') 
			openParenthesis(); //hice esta funcion para mantener simetria
		else if(string[i] == ')') {
			closeParenthesis();
			if(thereWasAnError)
				return 0;
		}
		else if(isOperator(string[i])) { 
			operatorInExpression(string,i);
			if(thereWasAnError)
				return 0;
		}
		else {
			thereWasAnError = 2;
			return 0;
		}
	}
	while(currentOperationPosition != 0) { 
		if(thereWasAnError)
			return 0;
		updateStack();
	}
	if(currentOperandPosition != 1){ 
		thereWasAnError = 3;
		return 0;
	}

	return operandStack[0]; 
}

void operatorInExpression(char * string, int i) {
	while((currentOperationPosition != 0) && precedence(operationStack[currentOperationPosition - 1],string[i])) {
		updateStack();
		if(thereWasAnError)
			return;
	}
	operationStack[currentOperationPosition++] = string[i];	
}
void openParenthesis(){
	operationStack[currentOperationPosition++] = '(';
}

void closeParenthesis() {
		while(operationStack[currentOperationPosition - 1] != '(') {
			if(currentOperationPosition == 0) {
				thereWasAnError = 2;
				return;
			}
		if(thereWasAnError)
			return;
		updateStack();
	}
	operationStack[currentOperationPosition - 1] = 0; 
	currentOperationPosition--;
}

void updateStack() { //OPERA CON EL ULTIMO VALOR DEL STACK Y LOS ULTIMOS DOS DEL STACK DE NUMEROS
	if(currentOperandPosition < 2) {
		thereWasAnError = 2;
		return;
	}
	double num1 = operandStack[currentOperandPosition - 2]; //AGARRO EL PRIMER NUMERO
	double num2 = operandStack[currentOperandPosition - 1]; //AGARRO EL SEGUNDO NUMERO
	char op = operationStack[currentOperationPosition-1];
	if((op == '%' || op == '/') && (num2 == 0)) {
		thereWasAnError = 4;
		return;
	}
	operandStack[currentOperandPosition - 2] = evaluateOperator(num1,num2,op);
	currentOperandPosition--;
	currentOperationPosition--;
}

double evaluateOperator(double num1, double num2, char op) { //EVALUA LA OPERACION
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
			return 0;
		}
}

int operatorPrecedence(char op) { //PRECEDENCIA DE OPERADOR
	if(op == '+' || op == '-')
		return 0;
	if(op == '%' || op == '*' || op == '/')
		return 1;
	else
		return 0;
}

int precedence(char op1,char op2) { //ME DICE QUE OPERADOR TIENE PRECEDENCIA
	return (operatorPrecedence(op1) > operatorPrecedence(op2));
}

int isANumber(char ch) { //DICE SI ES UN NUMERO
	return (ch >= '0' && ch <= '9');
}
int isOperator(char ch) { //DICE SI ES OPERADOR
	return (ch == '+' || ch == '-' || ch=='*' ||ch=='/'||ch=='%') ;
}