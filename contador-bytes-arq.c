/* ==============Bibliotecas=========== */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

/* =======Tipos de dados pr?-definidos======= */
/* 
   Neste programa, a estrutura necess?ria para se saber 
   quantos registros estar?o gravados em PRODUTOS.DAT 
*/
typedef   struct 
{   /* campos da estrutura */
    int    	Codprod;
    char   	Nomeprod[20+1]; /* 20 ?teis mais o \0 = NULL TERMINATOR */
    float	Custoprod;
}  
registro; 

/* ========Vari?veis globais========= */
FILE * Arq;
int   numero_registros;

/* ========Corpo do programa========= */
int main()
{
	Arq = fopen ("PRODUTOS.DAT", "r");
	if ( Arq == NULL) /* O arquivo n?o existe */
	   numero_registros = 0;
	else
	{   /* Calcula o tamanho do arquivo */
		if ( fseek (Arq, 0, SEEK_END) ) /* Aqui fseek tenta se posicionar no final do arquivo...*/
		{
           printf("\nERRO ao calcular o tamanho de arquivo!\n");
           getch();
           numero_registros = -1;
        }
        else
		{   /*...para que ftell 'conte' quantos bytes o arquivo tem */
		    /* Dividindo-se o total de bytes do arquivo pelo tamanho de cada registro */
		    /* tem-se o n?mero de registros do arquivo. */
		    numero_registros =  ftell(Arq) / sizeof (registro); 
  	    }
  	    /* Fecha o arquivo */
  	    fclose (Arq);
	}
    /* Para teste: avisa quantos bytes o arquivo tem */
    /* printf ("\nO arquivo PRODUTOS.DAT tem [%i] registros.", numero_registros);*/

    /* 'devolve' a quantidade de registros para o programa 'chamador'*/
	return (numero_registros); 
}
