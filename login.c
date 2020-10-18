#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

#define DEFAULT_LIST 67 // analizar se é necessario
#define MAX 100
#define false -1
#define true 1

typedef char TYPEKEY;
FILE *arq, *arq_aux;
int aux_menu = 0;

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
int buscaBinaria(LISTA *list, char *nome){
	int esq, dir, meio;
	esq = 0;
	dir = (tamanhoLista(list)-1);

	while(esq<=dir){
		meio = (esq+dir)/2;
		if(strcmp(list->reg[meio].nameUser, nome)==0)  //(list->reg[meio].nameUser == nome)
			return meio;
		else
			if(strcmp(list->reg[meio].nameUser, nome) < 0 ) //(list->reg[meio].nameUser  < name) <- comparação de string
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
REGISTRO loginUser(){
	REGISTRO reg;

	printf("\n\nNome de usuário: "); 		fflush(stdin); gets(reg.nameUser);
	printf("\nProntuário do usuário: "); 	fflush(stdin); gets(reg.prontUser);
	converterString(reg.nameUser);
	converterString(reg.prontUser);
	return reg;
}
//OPCAO DO MENU
void optMenu(char c){
    system("cls");
    switch(c){
        default:
            printf("SELECIONE UMA OPCAO VALIDA");
            getch();
            break;
        case '1':
            system("pilha_estatica.exe");		//abastece gondola
            break;
        case '2':
            system("fila.exe");					//caixa/pdv
            break;
        case '3':
            system("salvar-lista.exe");			//gerenciar usuarios
            break;
        case '0':
            aux_menu = 1;
            break;
    }
}
//MENU
void inicializaMenu(){
    char a;
    system("cls");
    printf("------------SISTEMA GERENCIADOR DE SUPERMERCADOS---------------\n");
    printf("-----------------1.ABASTECER GONDOLAS--------------------------\n");
    printf("-----------------2.CAIXA/PDV-----------------------------------\n");
    printf("-----------------3.GERENCIAR USUARIOS--------------------------\n");
    printf("-----------------0.SAIR----------------------------------------\n");
    printf("\nEscolha uma opcao: ");
    a = getch();
    optMenu(a);

}
//CODIGO MAIN
int main(){
	setlocale(LC_ALL, ""); 
	LISTA list;
	REGISTRO registro;
	int aux_busca;

	registro = loginUser();

	iniciarLista(&list);
	list = lerArquivo();
	aux_busca = buscaBinaria(&list, registro.nameUser);
	
	if(aux_busca!=false){
		if(strcmp(list.reg[aux_busca].prontUser, registro.prontUser )==0){
			while(aux_menu == 0){
            inicializaMenu();
			}
		} else 
			printf("\n\nUSUARIO E/OU PRONTUARIO INVALIDOS");
	}
	else
		printf("\n\nUSUARIO E/OU PRONTUARIO INVALIDOS");
	getch();
	return 0;
}
