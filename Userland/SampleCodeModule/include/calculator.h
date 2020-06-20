#ifndef _cal_culator_
#define _cal_culator_
void calculator();
double evaluate(char * string);
double evaluateOperator(double num1, double num2, char op);
int operatorPrecedence(char op);
int precedence(char op1,char op2);
void closeParenthesis();
void openParenthesis();
void operatorInExpression(char * string,int i);
int addNumber(char * string, int i,int stillInANumuber);
int isANumber(char ch);
int isOperator(char ch);
void startOver(); //int position, char * buffer
void updateStack();
void cleanEverything(); //int position, char * buffer
#endif