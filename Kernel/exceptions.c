
#define ZERO_EXCEPTION_ID 0

static void zero_division();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
}

void zero_division() {
	cleanScreen();
	char * string = "Trataste de dividir por cero";
	int i = 0;
	while(string[i] != 0)
		printAnyChar(string[i++],255,0,0);
	
	//printLine("Usted trato de dividir por cero!");
	// Handler para manejar excepcíon
}