#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define false -1
#define true 1

typedef char TYPEKEY;
FILE *arq, *arq_aux;

//ESTRUTURA DA LISTA
typedef struct {
	char	nameUser[100+1];
	TYPEKEY	prontUser[10+1];
}REGISTRO;
typedef struct {
	REGISTRO reg[MAX];
	int numElemento;
}LISTA;

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
int buscaBinaria(LISTA *list, char *nome){
	int esq, dir, meio;
	esq = 0;
	dir = (tamanhoLista(list)-1);
	
	while(esq<=dir){
		meio = (esq+dir)/2;
		if(strcmp(list->reg[meio].nameUser, nome)==0)  
			return meio;
		else
			if(strcmp(list->reg[meio].nameUser, nome) < 0 ) 
				esq=meio+1;
			else
				dir=meio-1;	
	}
	return false;
}
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
//CONVERSOR STRINGS
void converterString(char *str){
	int i;
	for(i=0; i<strlen(str); i++){
		str[i] = toupper(str[i]);
	}	
}

//LOGIN
int loginUser(REGISTRO *reg, LISTA *list){
	int resultado;
	printf("\n\nNome de usuário: "); 		fflush(stdin); gets(reg->nameUser);
	printf("\nProntuário do usuário: "); 	fflush(stdin); gets(reg->prontUser);
	
	printf("\n- %-30s, %-10s", reg->nameUser , reg->prontUser );
	converterString(reg->nameUser);
	converterString(reg->prontUser);
	printf("\n- %-30s, %-10s", reg->nameUser , reg->prontUser);
	resultado = buscaBinaria(list, reg->nameUser);
	return resultado;
}
//CODIGO MAIN
int main(){
	LISTA list;
	REGISTRO registro;
	int aux_busca;
	
	iniciarLista(&list);
	list = lerArquivo();
	exibirLista(&list);
	
	aux_busca = loginUser(&registro, &list);
	
	
	if(aux_busca!=false){
		printf("\n%d - %-30s, %-10s",aux_busca, list.reg[aux_busca].nameUser, list.reg[aux_busca].prontUser);
	}
	else {
		printf("\n\nUSUARIO E/OU PRONTUARIO INVALIDOS");
	}	
	getch();
	return 0;
}
