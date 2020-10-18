#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h> /* Para poder usar as funções : _strdate(data); e _strtime(hora); */

FILE *arq, *nota, *arq_aux;

char data[11];
char hora[9];

typedef struct
{
   char NOMEPROD[100+1];
   char DESC[100+1];
   float PESO, VALOR;
}REGISTRO;
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

REGISTRO reg_car;

int main(){
    int i;
    _strdate (data);
    _strtime(hora);
    arq = fopen("CARRINHO.DAT" , "r");
    if (arq == NULL){
        printf("ERRO! CARRINHO ESTA VAZIO");
        getch();
        return 0;
    }
    nota = fopen("NOTAFISCAL.txt", "w");
    int j = qtdRegistrosArq();
    REGISTRO reg_fila[j];
    int c = j-1;
    float valortotal = 0;

    if ( arq!= NULL ){
        system ("cls");
        printf("calculando valores e gerando nota fiscal.....");
        fprintf(nota,"----------------------NOTA FISCAL------------------------\n");
        fprintf (nota,"[%c%c/%c%c/%c%c][%s]\n",data[3],data[4],data[0],data[1],data[6],data[7],hora);
        fprintf(nota,"----------------------PRODUTOS---------------------------\n");
        while ( !feof(arq) ){
            fread(&reg_car, sizeof(reg_car), 1, arq);
            if(!feof(arq)){
                //fprintf(nota,"1x %s-%s-%.2fkg-R$%.2f\n", reg_car.NOMEPROD, reg_car.DESC, reg_car.PESO, reg_car.VALOR);
                reg_fila[c] = reg_car;
                c--;
                valortotal += reg_car.VALOR;
            }
    }
    for (i = 0; i < j; i++){
        fprintf(nota,"1x %s-%s-%.2fkg-R$%.2f\n", reg_fila[i].NOMEPROD, reg_fila[i].DESC, reg_fila[i].PESO, reg_fila[i].VALOR);
    }
    fprintf(nota,"---------------------------------------------------------\n");
    fprintf(nota,"valor total: %.2f",valortotal);
    }
    fclose(arq);
    fclose(nota);
    system("NOTAFISCAL.txt");
}

