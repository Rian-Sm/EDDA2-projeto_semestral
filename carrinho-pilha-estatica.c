//pilha estatica de carrinho
#include <stdio.h>
#include <conio.h>
#include <locale.h>

#define MAX_CARRINHO 50	

#define true 1
#define false -1

FILE *arq, *arq_aux;

typedef struct{
   char NOMEPROD[100+1];
   char DESC[100+1];
   float PESO, VALOR;
}REGISTRO;
typedef struct{
	REGISTRO reg[MAX_CARRINHO];
	int topo;
}CARRINHO;
//funcoes da struct CARRINHO
void iniciarCarrinho(CARRINHO *pilha){ 			//vale para reiniciar pilha estatica tambem
	pilha->topo = -1;
}
int tamanhoCarrinho(CARRINHO *pilha){
	return pilha->topo +1;
}
void exibirCarrinho(CARRINHO *pilha){
	int i;
	for(i=pilha->topo; i>=0;i--){
		printf("\n%s, %s - valor: %.2f - peso: %.2f kg",
		pilha->reg[i].NOMEPROD, pilha->reg[i].DESC, pilha->reg[i].VALOR, pilha->reg[i].PESO );
	}
}
int inserirElementoCarrinho(CARRINHO *pilha, REGISTRO reg){
	if(pilha->topo >= MAX_CARRINHO-1)
		return false;
	pilha->topo++;
	pilha->reg[pilha->topo] = reg;
	return true;
}
int excluirElementoCarrinho(CARRINHO *pilha, REGISTRO *reg){
	if(pilha->topo == -1)
		return false;
	*reg = pilha->reg[pilha->topo];
	pilha->topo--;
	return true;
}
int qtdRegistrosArq(){
	int qtd_registros;
	arq_aux = fopen("CARRINHO.DAT", "r");
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
void lerArquivoCarrinho(CARRINHO *pilha){
	arq = fopen("CARRINHO.DAT", "rb");
	if(arq == NULL)
		printf("\nErro na abertura do arquvo");
	else {
		pilha->topo = qtdRegistrosArq();
		fread(pilha->reg , sizeof(REGISTRO)*(tamanhoCarrinho(pilha)), 1, arq);
	}	
	fclose(arq); 
	printf("\nfinalizado processo de abetura \\(*.*)/");
}
void salvarCarrinho(CARRINHO *pilha){
	arq = fopen("CARRINHO.DAT", "wb");
	if(arq ==NULL)
		printf("\nErro ao abrir o arquivo");
	else
		if(fwrite(pilha->reg, sizeof(REGISTRO)*tamanhoCarrinho(pilha), 1, arq)==0)
			printf("\nErro ao salvar");	
	fclose(arq);
}
void menu_funcoes(){
	printf("\nfunções do carrinho:");
	printf("\n1-iniciar/reiniciar");
	printf("\n2-mostrar tamanho");
	printf("\n3-exibir carrinho");
	printf("\n4-inserir elemento");
	printf("\n5-excluir elemento");
	printf("\n6-salvar elementos	(CARRINHO.DAT)");
	printf("\n7-ler elementos		(CARRINHO.DAT)");
	printf("\n0-sair");
	printf("\nESCOLHA: ");
}
void inserirProduto(REGISTRO *produto){
	printf("\nNome do produto: "); 		fflush(stdin); gets(produto->NOMEPROD);
  	printf("Descrição do produto: ");	fflush(stdin); gets(produto->DESC);
	printf("Peso do produto: ");		fflush(stdin); scanf("%f", &produto->PESO);
	printf("Valor do produto: ");		fflush(stdin); scanf("%f", &produto->VALOR);
}
int main(){
	setlocale(LC_ALL, ""); 
	CARRINHO carrinho;
	REGISTRO produto;
	int opc, aux_while=true;
	
	iniciarCarrinho(&carrinho);
	do{
		system("cls");
    	menu_funcoes(); fflush(stdin); scanf("%d", &opc);
    	switch(opc){
    		case 1:
    			printf("\nopção 1 escolhida.");
    			iniciarCarrinho(&carrinho); 
    			getch();
				break;
			case 2:
				printf("\nopção 2 escolhida.\nCarrinho possui %d elementos.", tamanhoCarrinho(&carrinho));
				getch();
				break;
			case 3:
				printf("\nopção 3 escolhida.\nlista:\n");
				exibirCarrinho(&carrinho);
				getch();
				break;
			case 4:
				printf("\nopção 4 escolhida.");
				inserirProduto(&produto);
				inserirElementoCarrinho(&carrinho, produto); 
				getch();
				break;
			case 5:
				printf("\nopção 4 escolhida.");
				excluirElementoCarrinho(&carrinho, &produto);
				printf("\nproduto removido: %s", produto.NOMEPROD);
				getch();
				break;
			case 6:
				printf("\nlevando carrinho ao estoque: ");
				salvarCarrinho(&carrinho);
				getch();
				break;
			case 7:
				lerArquivoCarrinho(&carrinho);
				excluirElementoCarrinho(&carrinho, &produto); 
				getch();
				break;
			case 0:
				printf("\nSaindo!");
				aux_while = false;
				getch();
				break;
			default:
				printf("\nValor invalido!");
				getch();
				break;			
		}
	}while(aux_while == true);
	return 0;	
}
