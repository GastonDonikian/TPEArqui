
#define ZERO_EXCEPTION_ID 0

static void zero_division();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
}

static void zero_division() {
	//printLine("Usted trato de dividir por cero!");
	//printLine("Usted se tiene que arrepentir de lo que hizo");
	// Handler para manejar excepcíon
}