//Busca binaria arquivo
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define false -1
#define true 1

//ESTRUTURA DA LISTA
typedef struct {
	char	nameUser[100+1];
	TYPEKEY	prontUser[10+1];
}REGISTRO;
typedef struct {
	REGISTRO reg[MAX];
	int numElemento;
}LISTA;

void converterString(char *str){
	int i;
	for(i=0; i<strlen(str); i++){
		str[i] = toupper(str[i]);
	}	
}
//FUNÇÕES DA LISTA
void iniciarLista(LISTA *list){
	list->numElemento = 0;
}
int tamanhoLista(LISTA *list){
	return list->numElemento;
}
void exibirLista(LISTA *list){
	int i;
	printf("\n\nLista:\n");
	for(i=0; i<tamanhoLista(list) ; i++){
		printf("\n%s - %s",
		list->reg[i].nameUser, list->reg[i].prontUser);
	}
	printf("\n");
}
//LEITOR DA LISTA
int qtdRegistrosArq(){
	int qtd_registros;
	arq_aux = fopen("USUARIO.DAT", "r");
	if(arq_aux == NULL)
		qtd_registros = 0;
	if (fseek(arq_aux, 0, SEEK_END)){
		printf("\nERRO ao calcular o tamanho de arquivo!\n");
        getch();
        qtd_registros = -1;
	} else {
		qtd_registros = ftell(arq_aux) / sizeof(REGISTRO) ;
	}
	return qtd_registros;
}
LISTA lerArquivo(){
	LISTA list_aux;
	arq = fopen("USUARIO.DAT", "rb");
	if(arq == NULL)
		printf("\nARQUIVO USUARIO.DAT NÂO EXISTE");
	else {
		list_aux.numElemento  = qtdRegistrosArq();
		fread(&list_aux, sizeof(REGISTRO)*tamanhoLista(&list_aux) , 1, arq);
	}
	fclose(arq);
	printf("\nfinalizado processo de abetura \\(*.*)/");
	return list_aux;
}
// <---------- cria busca binaria aqui
int buscaBinaria(LISTA *list, char *pesquisa){
	int init, fim, meio;
	fim=tamanhoLista(list)-1;
	init=0;
	
	while(init<=fim){
		meio=(fim+init)/2;	
		if(strcmp(list->reg[meio].nameUser, pesquisa)==0)
			return meio;
			
		if(strcmp(list->reg[meio].nameUser, pesquisa) < 0)
			init = meio+1;
		else
			fim = meio-1;
	}
	return false;
}

int main(){
	LISTA list;
	REGISTRO reg;
	
	
}


