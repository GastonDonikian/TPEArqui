#include <stdint.h>
#include "lib.h"
#include "calculator.h"

#define MAX_OPERATIONS 20
#define MAX_OPERANDS 20
	
double operandStack[MAX_OPERANDS];
char operationStack[MAX_OPERATIONS];
	
int currentOperandPosition = 0;
int currentOperationPosition = 0; //VARIABLES GLOBALES PARA MANEJAR LOS STACKS
 
int thereWasAnError = 0; // HABLA ENTRE LA CALCULADORA Y EL ANALIZADOR PARA SABER SI HUBO ALGUN ERROR CON LA EXPRESION
//ERROR 0 = TODO BIEN
//ERROR 1 = MAL DADO UN NUMERO
//ERROR 2 = MAL CANTIDAD DE OPERANDOS
//ERROR 3 = MAL CANTIDAD DE NUMEROS
//ERROR 4 = DIVIDISTE POR CERO 
//ERROR 5 = NOT AN OPERATOR
void calculator() { //FUENTE DE "FRONT-END" DE LA CALCULADORA
	putChar('h');
	while(1) {
		char c;
		char buffer[MAX_OPERATIONS + MAX_OPERANDS + 20] = {0}; //MAXIMA POSICION DE IMPRESION
		int position = 0;
		while((c = getChar()) != 'a') { //SOLO ACEPTAMOS DIGITOS O CARACTERES ESPECIALES
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
		if(thereWasAnError) { //SI HUBO ALGUN ERROR IMPRIMIMOS EL ERROR Y NO MOSTRAMOS EL VALOR
			printf("Error: ");
			char * stringArray[5] = {"Todo bien...","Me pasaste mal un numero","Mal cantidad de operadores","Mal cantidad de numeros","Dividiste por cero"};
			printf(stringArray[thereWasAnError]);
			thereWasAnError = 0;
		}
		else
			printf(string);
		putChar('\n');
		cleanEverything(position,buffer);
	}
}

void cleanEverything(int position, char * buffer) { //RESETEA LAS VARIABLES GLOBALES PARA VOLVER A EMPEZAR
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

void startOver(int position,char * buffer) { //NO RESETEA TODO, PERO BORRAR EL INPUT
	for(int  i = 0; i < position; i++) {
		buffer[i] = 0;
		putChar('\b');
	}
}


double evaluate(char * string) { //EVALUA LA EXPRESION 
	for(int i = 0; string[i] != 0;i++) { //PARA CADA CARACTER DE LA STRING
		int stillInANumber = 0;
		if(thereWasAnError)
			return 0;
		if(isANumber(string[i])) { //ESTOY PARADO EN UN NUMERO, AVANZO HASTA QUE EL NUMER TERMINE
			operandStack[currentOperandPosition++] = stringToDouble(string + i); //AGREGO EL NUMERO A MI STACK
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

		} //YA TENEMOS EL NUMERO GUARDADO EN EL STACK
		else if(string[i] == '(') { //SI ES UN PARENTESIS LO APPENDEA PUES SIEMPRE QUIERO EJECUTAR LO QUE HAY ADENTRO DEL PARENTESIS
			operationStack[currentOperationPosition++] = '(';
		}
		else if(string[i] == ')') { //HASTA QUE NO HAYA UN CIERRE SIGO CORRIENDO
			while(operationStack[currentOperationPosition - 1] != '(') {
				if(currentOperationPosition == 0) {
					thereWasAnError = 2;
					 return 0;
				}
				if(thereWasAnError)
					 return 0;
				updateStack();
			}
			operationStack[currentOperationPosition - 1] = 0; //BORRO EL PARENTESIS, PUES NO ME INTERESA
			currentOperationPosition--;

		}
		else if(isOperator(string[i])) { //SI ES UN OPERADOR ME FIJO PRECEDENCIA Y VEO QUE HAGO
			while((currentOperationPosition != 0) && precedence(operationStack[currentOperationPosition - 1],string[i])) {
				updateStack();
				if(thereWasAnError)
					return 0;
			}
			operationStack[currentOperationPosition++] = string[i];
		}
		else {
			thereWasAnError = 2;
			return 0;
		}
	}
	while(currentOperationPosition != 0) { //TERMINE CON EL STRING PERO TODAVIA ME FALTA OPERAR
		if(thereWasAnError)
			return 0;
		updateStack();
	}
	if(currentOperandPosition != 1){ //SI NO ME QUEDA SOLO UN NUMERO HUBO UN PROBLEMA CON LA EXPRESION
		thereWasAnError = 3;
		return 0;
	}

	return operandStack[0]; //DEVUELVE EL ULTIMO VALOR
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