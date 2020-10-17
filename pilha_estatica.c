//pilha estatica
#include <stdio.h>
#include <locale.h>


#define MAX 10     							//quantidade de gondulas
#define MAX_ITENS 5							//quantidade de elementos na gondula
#define MAX_CARRINHO 10						//quantidade de elementos no carrinho
#define true 1
#define false -1

FILE *arq, *arq_aux;

typedef struct
{
   char NOMEPROD[100+1];
   char DESC[100+1];
   float PESO, VALOR;
}
REGISTRO;
typedef struct{
	REGISTRO reg[MAX_ITENS];
	int topo;
}PILHA;

typedef PILHA CARRINHO;

//funcao da pilha
void iniciarPilha(PILHA *pilha){ 			//vale para reiniciar pilha estatica tambem
	pilha->topo = -1;
}
int tamanhoPilha(PILHA *pilha){
	return pilha->topo +1;
}
void exibirPilha(PILHA *pilha){
	int i;
	for(i=pilha->topo; i>=0;i--){
		printf("\n%s, %s - valor: %.2f - peso: %.2f kg",
		pilha->reg[i].NOMEPROD, pilha->reg[i].DESC, pilha->reg[i].VALOR, pilha->reg[i].PESO );
	}
}
int inserirElementoPilha(PILHA *pilha, REGISTRO reg){
	if(pilha->topo >= MAX_ITENS-1)
		return false;
	pilha->topo++;
	pilha->reg[pilha->topo] = reg;
	return true;
}
int excluirElementoPilha(PILHA *pilha, REGISTRO *reg){
	if(pilha->topo == -1)
		return false;
	*reg = pilha->reg[pilha->topo];
	pilha->topo--;
	return true;
}
//funções do programa
void menuPilha(){
	system("cls");
    printf("------------SISTEMA GERENCIADOR DE GONDULAS--------------------\n");
    printf("-----------------1.ABASTECER GONDOLAS--------------------------\n");
    printf("-----------------2.LIMPAR GONDULA---(colocar no carrinho)------\n");
    printf("-----------------3.EXAMINAR GONDULAS---------------------------\n");
    printf("-----------------4.OLHAR CARRINHO------------------------------\n");
    printf("-----------------5.LIMPAR CARRINHO-----------------------------\n");
    printf("-----------------6.SALVAR CARRINHO---(CARRINHO.DAT)------------\n"); //não salva corretamente
    printf("-----------------7.PEGAR CARRINHO----(CARRINHO.DAT)------------\n");

    printf("-----------------0.SAIR----------------------------------------\n");
    printf("ESCOLHA: ");
}
void iniciarConjuntoGondulas(PILHA *pilha){
	int i=0;
	while(i<MAX){
		iniciarPilha(&pilha[i]);  
		i++;
	}
}
void abastecerGondulas(PILHA *pilha){
	REGISTRO produto;
	int scan;
	int retorno=true;
	
	printf("\nO Abastetecimento vai ser do mesmo produto: ");
	
    printf("\nNome do produto: "); 		fflush(stdin); gets(produto.NOMEPROD);
    printf("Descrição do produto: ");	fflush(stdin); gets(produto.DESC);
    printf("Peso do produto: ");		fflush(stdin); scanf("%f", &produto.PESO);
    printf("Valor do produto: ");		fflush(stdin); scanf("%f", &produto.VALOR);
    
    printf("\nDeseja inserir esse produto em toda pilha? (2-sim) (1-não)"); fflush(stdin); scanf("%d", &scan);
    	switch(scan){
    		case 1:
    			inserirElementoPilha(pilha, produto);
    			break;
    		case 2:
    			while(retorno!=false){
					retorno = inserirElementoPilha(pilha, produto);
					}
				break;
    		default:
				printf("\n erro na escolha");
				break;	
		}
	printf("\na quantidade de itens inseridos %d", tamanhoPilha(pilha));
}
void printPilha(PILHA *pilha){
	int i=0;
	while(i<MAX){
		printf("\nGondula %d", i+1);
		if(tamanhoPilha(&pilha[i])==0)
			printf("\nA gondula esta vazia");
		
		exibirPilha(&pilha[i]);
		i++;
	}
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
void lerArquivoCarrinho(PILHA *pilha){
	arq = fopen("CARRINHO.DAT", "rb");
	if(arq == NULL)
		printf("\nErro na abertura do arquvo");
	else {
		pilha->topo = qtdRegistrosArq();
		fread(pilha->reg , sizeof(REGISTRO)*(tamanhoPilha(pilha)), 1, arq);
	}	
	fclose(arq);
	printf("\nfinalizado processo de abetura \\(*.*)/");
}

void salvarCarrinho(PILHA *pilha){
	arq = fopen("CARRINHO.DAT", "wb");
	if(arq ==NULL)
		printf("\nErro ao abrir o arquivo");
	else
		if(fwrite(pilha->reg, sizeof(REGISTRO)*tamanhoPilha(pilha), 1, arq)==0)
			printf("\nErro ao salvar");
	
	fclose(arq);
}
//CODIGO MAIN
int main(){
	setlocale(LC_ALL, ""); 
	PILHA polha[MAX];
	CARRINHO carrinho;
    REGISTRO produto;
    int opc, gondula, retorno;
    int aux_while = true;
    
    iniciarConjuntoGondulas(&*polha);
    iniciarPilha(&carrinho);
    do{
    	menuPilha(); fflush(stdin); scanf("%d", &opc);
    	switch(opc){
    		case 1:
    			printf("\nAbastecer qual gondula: (0 - 9)"); fflush(stdin); scanf("%d", &gondula );
    			if ((gondula>9) || (gondula<0))
    				printf("\nEssa gondula não existe!");
				else
					abastecerGondulas(&polha[gondula]); 
				getch();
				break;
			case 2:
				printf("\nLimpar qual gondula: (0 - 9)"); fflush(stdin); scanf("%d", &gondula );
    			if ((gondula>9) || (gondula<0))
    				printf("\nEssa gondula não existe!");
				else
					excluirElementoPilha(&polha[gondula], &produto);
					inserirElementoPilha(&carrinho, produto); 
					printf("\nproduto resgatado: %s", produto.NOMEPROD);	
				getch();
				break;
			case 3:
				printPilha(&*polha);
				getch();
				break;
			case 4:
				printf("\nItens no carrinho: ");
				exibirPilha(&carrinho);
				getch();
				break;
			case 5:
				printf("\nesvaziando carrinho: ");
				iniciarPilha(&carrinho); 
				getch();
				break;
			case 6:
				printf("\nlevando carrinho ao estoque: ");
				salvarCarrinho(&carrinho);
				getch();
				break;
			case 7:
				lerArquivoCarrinho(&carrinho); 
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
