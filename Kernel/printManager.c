void screenWriter(uint64_t buffer, uint64_t count, uint64_t upordown){
	for (int i = 0; i < count; i++){
		if(buffer[i]=='\n'){
			newLine(upordown);
		}
		if(buffer[i]=='\t'){
			print('        ');
		}
		if(buffer[i]=='\b'){
			deleteChar();
		}
		else{
			printChar(buffer[i])
		}
	}
}