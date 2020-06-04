#include "lib.h"
#include "calculator.h"
void calculator() {

}

double analyzeExpression(char * string) {
	
}

double stringToDouble(char * string) {
	double rta = 0;
	int pointPosition = 0;
	int length = 0;
	double pow = 0.1;
	while(*string == '0')
		string = string+1;
	while((string[length] >= '0' && string[length] <= '9') || string[length] == '.') { //CAMBIAR != 0 POR PARENTESIS O OPERANDO Y VALIDAR!
		if(string[length] == '.') {
			if(pointPosition)
				return; //HUBO UN ERROR!
			pointPosition = length;
		}
		if(!pointPosition)
			pow = pow*10;
		length++;
	}
	for(int i = 0; i < length;i++) {
		if(i != pointPosition){
			rta = rta +  (string[i] - '0') * pow;
			pow = pow/10;
		}
		else;
	}
	return rta;
}