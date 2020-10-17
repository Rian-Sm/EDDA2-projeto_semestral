#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_LIST 67
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
	REGISTRO reg[MAX+1]; // modelagem com ultimo registro sentinela para busca
	int numElemento;
}LISTA;

//CONSTRUTOR
void cadastroDefault(LISTA *list);
void converterString(char *str);

//FUNÇÕES DA LISTA
void iniciarLista(LISTA *list){
	list->numElemento = 0;
}
int tamanhoLista(LISTA *list){
	return list->numElemento;
}
void exibirLista(LISTA *list){
	int i;
	printf("\nLista:\n");
	for(i=0; i<tamanhoLista(list) ; i++){
		printf("\n%s - %s",
		list->reg[i].nameUser, list->reg[i].prontUser);
	}
	printf("\n");
}
int buscaSequencial(LISTA *list, char *nome){ //// busca pelo bagulho por key
	int i;
	while(i<tamanhoLista(list)){
		if (strcmp(nome, list->reg[i].nameUser)==0) //(nome == list->reg[i].nameUser )
			return i;
		else
			i++;
	}
	return false;
}
int buscaSequencialKEY(LISTA *list, TYPEKEY *pront ){ //// busca pelo bagulho por key
	int i;
	while(i<tamanhoLista(list)){
		if(strcmp(pront, list->reg[i].prontUser)==0) //(pront == list->reg[i].prontUser)
			return i;
		else
			i++;
	}
	return false;
}
int inserirElementoLista(LISTA *list, REGISTRO reg, int posicao){
	int i;
	if (tamanhoLista(list)==MAX || (posicao<0) || posicao>tamanhoLista(list))
		return false;
	
	for (i=tamanhoLista(list); i>posicao; i--)
		list->reg[i] = list->reg[i-1];
		
	list->reg[posicao]=reg;
	list->numElemento++;
	return true;
}
int excluirElementoLista(TYPEKEY *pront, LISTA *list){
	int posicao, i;
	posicao = buscaSequencialKEY(list, pront);
	if(posicao==false)
		return false;
	for(i=posicao; i<(tamanhoLista(list)-1) ; i++)
		list->reg[i] = list->reg[i+1];
	list->numElemento--;
}
int buscaSentinela(LISTA *list, TYPEKEY *pront){
	int i=0;
	strcpy(list->reg[tamanhoLista(list)].prontUser, pront); // list->reg[tamanhoLista(list)].prontUser = pront; <-  concatenação de string
	while(strcmp(list->reg[i].prontUser, pront) != 0 ){
		printf("%d ", i);
		i += 1;
	}
	if(i==tamanhoLista(list))
		return false;
	else
		return i;
}
int inserirElementoListaOrdenada(LISTA *list, REGISTRO reg){
	int posicao = tamanhoLista(list);
	
	 if(tamanhoLista(list)==MAX)
	 	return false;
	 	
	while(posicao>0 && strcmp(list->reg[posicao-1].nameUser , reg.nameUser ) > 0) //list->reg[posicao-1].prontUser > reg.prontUser ) <- comparação de string
	{
		list->reg[posicao] = list->reg[posicao-1];
		posicao--;
	}
	list->reg[posicao]= reg;
	list->numElemento++;
	return true;
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

void salvarArquivo(LISTA *list){
	
	arq = fopen("USUARIO.DAT", "wb");
	if(arq == NULL)
		printf("\nErro na abertura do arquvo");
	else 
		if(fwrite( list->reg , sizeof(REGISTRO)*tamanhoLista(list) , 1, arq) == 0)
			printf("\nErro no salvamento no arquivo");
	fclose(arq);
	printf("\nfinalizado processo de salvamento \\(*.*)/");
}
LISTA lerArquivo(){
	LISTA list_aux;
	arq = fopen("USUARIO.DAT", "rb");
	if(arq == NULL)
		printf("\nErro na abertura do arquvo");
	else {
		list_aux.numElemento  = qtdRegistrosArq();
		fread(&list_aux, sizeof(REGISTRO)*tamanhoLista(&list_aux) , 1, arq);
	}	
	fclose(arq);
	printf("\nfinalizado processo de abetura \\(*.*)/");
	return list_aux;
	
}

//MENU INICIAL
void printMENU(){
	printf("\nESCONHA UMA DAS OPCOES:");
	printf("\n==============================================="	);
	printf("\n1 - iniciar estrutura"							);
	printf("\n2 - criar cadastro default"						);
	printf("\n3 - retornar quantidade de elementos"				);
	printf("\n4 - mostrar elementos da estrutura"				);
	printf("\n5 - pesquisar elemento da estrutura"				);
	printf("\n6 - incluir novo elemento na estrutura"			);
	printf("\n7 - excluir elemento da estrutura"				);
	printf("\n8 - reiniciar estrutura"							);
	printf("\n9 - salvar lista em arquivo	(USUARIO.DAT)"		);
	printf("\n10 - ler lista em arquivo	(USUARIO.DAT)"			);
	printf("\n11 - quntidade lista em arquivo	(USUARIO.DAT)"	);
	printf("\n0 - sair do programa"								);
	printf("\n===============================================\n");
}
//TIPO DE BUSCA
int tipoBusca(LISTA *list){
	int opc, busca_aux, aux_while=true;
	REGISTRO reg;
	do{
	printf("\nTIPOS DE BUSCA:"						);
	printf("\n1 - Busca sequencial (prontuario)"	);
	printf("\n2 - Busca sentinela  (prontuario)"	);
	printf("\n3 - Busca binaria    (nome)"			);
	
	printf("\nQual tipo de busca?"); fflush(stdin); scanf("%d", &opc);
		
	switch(opc){
		case 1:
			printf("\n\nQual o PRONTUARIO do elemento? "); fflush(stdin); gets(reg.prontUser);
			converterString(reg.prontUser);
			busca_aux = buscaSequencialKEY(list, reg.prontUser);
			aux_while = false;
			break;
		case 2:
			printf("\n\nQual o PRONTUARIO do elemento? "); fflush(stdin); gets(reg.prontUser);
			converterString(reg.prontUser);
			busca_aux = buscaSentinela(list, reg.prontUser);
			aux_while = false;
			break;
		case 3: 
			printf("\n\nQual o NOME do elemento? "); fflush(stdin); gets(reg.nameUser);
			converterString(reg.nameUser);
			busca_aux = buscaBinaria(list, reg.nameUser);
			aux_while = false;
			break;
		default:
			printf("\n\nERRO na escolha de busca!");
			getch();
			system("cls");
	}
	}while(aux_while == true);
	return busca_aux;
}

//MAIN DO CODIGO
int main(){
	REGISTRO reg;
	LISTA list;
	TYPEKEY chave;
	int opcao, aux_posicao ,aux_busca, aux_while=true;
	
	do{
		system("cls");
		printMENU();
		fflush(stdin);  scanf("%d", &opcao);
		switch(opcao){
			case 1:
				iniciarLista(&list);
				printf("\nLista iniciada com %d posicoes", MAX);
				
				getch();
				break;
			case 2:
				printf("\nCriando cadastro default!");
				cadastroDefault(&list);
				getch();
				break;
			case 3:
				printf("\nA quantidade de elementos na lista atual: %d", tamanhoLista(&list));
				getch();
				break;
			case 4:
				printf("\nQuantidade os itens da lista:\n");
				exibirLista(&list);
				getch();
				break;
			case 5: // ======================= Alterar aqui para receber nome como busca
				aux_busca = tipoBusca(&list); 
				if (aux_busca == false)
					printf("\nERRO na busca desse elemento!");
				else {
					printf("\nElemento que contem esse nome");
					printf("\n%s - %s",
					list.reg[aux_busca].nameUser, list.reg[aux_busca].prontUser);
				}
				getch();
				break;
			case 6:
				printf("\nInserir elementos de forma ordenada: ");
				printf("\n\nQual nome da pessoa: "); fflush(stdin); gets(reg.nameUser);
				printf("\n\nQual prontuario da pessoa: "); fflush(stdin); gets(reg.prontUser);
				aux_busca = inserirElementoListaOrdenada(&list, reg);
				if(aux_busca == false)
					printf("\nErro na criacao do elemento");
				printf("\nElemento criado com sucesso");
				getch();
				break;
			case 7:
				printf("\nExcluir elemento: qual a chave do elemento? "); scanf("%s", &chave);
				aux_busca = excluirElementoLista(&chave, &list);
				if(aux_busca==false)
					printf("\nErro na exclusao do elemento");
				printf("\nElemento excluido com sucesso");
				getch();
				break;
			case 8:
				printf("\nReiniciada estrutura");
				iniciarLista(&list);
				getch();
				break;
			case 9:
				printf("\niniciado SALVAMENTO em arquivo externo...");
				salvarArquivo(&list);
				getch();
				break;
			case 10:
				printf("\niniciado LEITURA em arquivo externo...");
				list = lerArquivo(); 
				getch();
				break;
			case 11:
				printf("\nA quantidade de elementos no arquivo atual: %d", qtdRegistrosArq());
				getch();
				break;	
			case 0:
				printf("\nSaindo do programa...");
				aux_while = false;
				break;
			default:
				printf("Escolha uma opcao valida");
				getch();
				break;
		}
	}while(aux_while==true);
	getch();
	return 0;
}
void cadastroDefault(LISTA *list){
	int i=0;
		if(tamanhoLista(list)==0){
		REGISTRO reg[DEFAULT_LIST] = {
						{"Domingos Lucas Latorre de Oliveira"				, "CJ146456"	},
						{"Leandro Pinto Santana"							, "CP220383"	},
						{"Rodrigo Ribeiro de Oliveira"						, "RG134168"	},
						{"Andre Luiz da Silva"								, "SP030028"	},
						{"Claudia Miyuki Werhmuller"						, "SP030041"	},
						{"Claudete de Oliveira Alves"						, "SP03020X"	},
						{"Francisco Verissimo Luciano"						, "SP030247"	},
						{"Luk Cho Man"										, "SP060380"	},
						{"Ivan Francolin Martinez"							, "SP060835"	},
						{"Joao Vianei Tamanini"								, "SP060914"	},
						{"Jose Oscar Machado Alexandre"						, "SP070038"	},
						{"Jose Braz de Araujo"								, "SP070385"	},
						{"Paulo Roberto de Abreu"							, "SP070816"	},
						{"Jose Braz de Araujo"								, "SP070385"	},
						{"Eurides Balbino da Silva"							, "SP07102X"	},
						{"Domingos Bernardo Gomes Santos"					, "SP090888"	},
						{"Andre Evandro Lourenco"							, "SP100092"	},
						{"Miguel Angelo Tancredi Molina"					, "SP102763"	},
						{"Antonio Airton Palladino"							, "SP112197"	},
						{"Luis Fernando Aires Branco Menegueti"				, "SP145385"	},
						{"Antonio Ferreira Viana"							, "SP200827"	},
						{"Leonardo Bertholdo"								, "SP204973"	},
						{"Marcelo Tavares de Santana"						, "SP20500X"	},
						{"Wagner de Paula Gomes"							, "SP215016"	},
						{"Daniel Marques Gomes de Morais"					, "SP220097"	},
						{"Alexandre Beletti Ferreira"						, "SP226117"	},
						{"Vladimir Camelo Pinto"							, "SP240291"	},
						{"Leonardo Andrade Motta de Lima"					, "SP24031X"	},
						{"Davi Henrique Silva de Oliveira"					, "SP3013081"	},
						{"Guilherme Santana Reis de Souza"					, "SP3013278"	},
						{"Lorena Moreira Bezerra"							, "SP3013316"	},
						{"Arisvitor Alves da Silva Barros"					, "SP3013391"	},
						{"Adriana Machado Martins"							, "SP3015572"	},
						{"Breno Dias Oliveira"								, "SP3015645"	},
						{"Karina Mitie Fujihara"							, "SP3015734"	},
						{"Caio Gerstmann"									, "SP3015777"	},
						{"Mikael Ducatti Walczak"							, "SP3023168"	},
						{"Rafael Ribeiro Santos de Carvalho"				, "SP3024008"	},
						{"Rubens Henrique do Nascimento Lotufo"				, "SP3024121"	},
						{"Luis Vitor Santos de Sousa"						, "SP3026922"	},						
						{"Luiz Eduardo Barbosa Silveira"					, "SP3026922"	},						
						{"Gabriela Dias Dutra"								, "SP3030041"	},						
						{"Isabela Souza Duarte"								, "SP3030083"	},						
						{"Stefany Rodrigues dos Santos"						, "SP303027X"	},						
						{"Diego Marques da Costa"							, "SP3032175"	},						
						{"Tiago Henrique Cardoso"							, "SP3035646"	},						
						{"Elker Rodrigues Baroni Báo"						, "SP3037045"	},						
						{"Daniel Teixeira Paulino"							, "SP3037886"	},						
						{"Lucas Henrique Lima Soares"						, "SP3038912"	},						
						{"Brian Windson Oliveira Siqueira"					, "SP3038963"	},						
						{"Victor Hugo Sampa Hamaguti"						, "SP3038998"	},						
						{"Edilene Shizue Onizuka Reges"						, "SP3039005"	},						
						{"Jesiel Silva Gomes"								, "SP3039081"	},						
						{"Mauricio Guery Moreira Leite Saldanha"			, "SP3039102"	},						
						{"Ingra Viana Cabral"								, "SP3039366"	},						
						{"Isabella Salles Lourenço"							, "SP3039391"	},						
						{"Henrique Hiromi Shimada"							, "SP3039421"	},						
						{"Guilherme de Paula Vitorino"						, "SP3039439"	},						
						{"Rian Santos Macedo"								, "SP3039498"	},						
						{"Vinicius Gomes Moreira"							, "SP3039587"	},						
						{"Guilherme Fernandes Lima"							, "SP3040674"	},						
						{"João Pedro Gomes Figueiredo"						, "SP3040682"	},						
						{"Cezar Godoy Nascimento"							, "SP3040755"	},						
						{"Amanda Queiroz Carreiro"							, "SP3040836"	},						
						{"Marco Antonio de Souza Reis Junior"				, "SP3041671"	},						
						{"Cesar Lopes Fernandes"							, "SP890534"	},						
						{"Josceli Maria Tenorio"							, "SZ124382"	},						
					};
		while(i<DEFAULT_LIST){
			converterString(reg[i].nameUser);
			converterString(reg[i].prontUser);
			inserirElementoListaOrdenada(list, reg[i]);
			i++;
		}	
	} else
		printf("\n\nja existem dados cadastrados :/");	
}
void converterString(char *str){
	int i;
	for(i=0; i<strlen(str); i++){
		str[i] = toupper(str[i]);
	}	
}
