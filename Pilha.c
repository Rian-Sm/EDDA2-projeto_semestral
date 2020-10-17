#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX 1
typedef int TIPOCHAVE;

typedef struct
{
   char NOMEPROD[100+1];
   char DESC[100+1];
   float PESO, VALOR;
}
REGISTRO;
typedef struct aux
{
   REGISTRO reg;
   struct 	    aux * PROX;
}
ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct
{
   PONT topo;
}
PILHA;

void inicializarPilha (PILHA* p)
{
  p->topo = NULL;
}

int tamanho (PILHA* p)
{
   PONT end = p->topo;
   int tam = 0;
   while (end != NULL)
   {
      tam++;
      end = end->PROX;
   }
   return tam;
}

void exibirPilha (PILHA* p)
{
   PONT end = p->topo;
   //system ("cls");
   printf("Pilha: \" ");
   while (end != NULL)
   {
	printf("\n%s - %s - %.2f - %.2f kg", end->reg.NOMEPROD, end->reg.DESC, end->reg.VALOR, end->reg.PESO);
	end = end->PROX;
   }
   printf("\"\n");
}

bool estaVazia(PILHA* p)
{
   if (p->topo == NULL)
      return true;
   return false;
}

bool inserirElemPilha(PILHA* p, REGISTRO reg)
{
   PONT novo  = (PONT) malloc(sizeof(ELEMENTO));
   novo->reg  = reg;
   novo->PROX = p->topo;
   p->topo    = novo;
   return true;
}

bool excluirElemPilha(PILHA* p, REGISTRO* reg)
{
   if ( p->topo == NULL)
      return false;
   *reg        = p->topo->reg;
   PONT apagar = p->topo;
   p->topo     = apagar->PROX;
   free(apagar);
   return true;
}

void reinicializarPilha (PILHA* p)
{
   PONT apagar;
   PONT posicao = p->topo;
   while (posicao != NULL)
   {
      apagar  = posicao;
      posicao = posicao->PROX;
      free(apagar);
   }
   p->topo = NULL;
}
void abastecePilha(PILHA *p, REGISTRO reg){
    
        inserirElemPilha(p, reg);
    


}
int main(){
    int i;
    PILHA polha[];
    REGISTRO produto;
    
    printf("\nABASTECER PILHA");
    for (i = 0; i < 4;i++){
        inicializarPilha (&polha[i]);
        
        printf("insira os dados dos produtos da %d pilha:\n", i+1);
        printf("Nome do produto: "); fflush(stdin); gets(produto.NOMEPROD);
        printf("Descrição do produto: "); fflush(stdin); gets(produto.DESC);
        printf("Peso do produto: "); fflush(stdin); scanf("%f", &produto.PESO);
        printf("Valor do produto: "); fflush(stdin); scanf("%f", &produto.VALOR);
        abastecePilha(&polha[i], produto);
    }
    system ("cls");
    for (i = 0; i < 4;i++){
        exibirPilha (&polha[i]);
    }






}

