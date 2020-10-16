#include <stdio.h>
#include <string.h>
#include <ctype.h>

void converterString(char *str){
	int i;
	for(i=0; i<strlen(str); i++){
		str[i] = toupper(str[i]);
	}	
}
int main(){
	char str[] = "batata doce";
	int i;

	printf("\n%s", str);
	converterString(str);
		
	printf("\n%s", str);
	
	return 0;
}
