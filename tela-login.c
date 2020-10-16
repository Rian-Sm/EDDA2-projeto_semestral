#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_LIST 67
#define MAX 100
#define false -1
#define true 1

typedef int TYPEKEY;

FILE * arq;
//ESTRUTURA DA LISTA
typedef struct {
	TYPEKEY	chave;
	char	nameUser[100+1];
	char	prontUser[10+1];
}REGISTRO;

typedef struct {
	REGISTRO reg[MAX+1]; // modelagem com ultimo registro sentinela para busca
	int numElemento;
}LISTA;

void iniciarLista(LISTA *list){
	list->numElemento = 0;
}

int tamanhoLista(LISTA *list){
	return list->numElemento;
}

int buscaSequencial(LISTA *list, TYPEKEY chave){
	int i;
	while(i<tamanhoLista(list)){
		if(chave==list->reg[i].chave)
			return i;
		else
			i++;
	}
	return false;
}
void exibirLista(LISTA *list){
	int i;
	
	printf("\nLista:\n");
	for(i=0; i<tamanhoLista(list) ; i++){
		printf("\n%d - %s - %s",
		list->reg[i].chave, list->reg[i].nameUser, list->reg[i].prontUser);
	}
	printf("\n");
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
int excluirElementoLista(TYPEKEY chave, LISTA *list){
	int posicao, i;
	
	posicao = buscaSequencial(list, chave);
	
	if(posicao==false)
		return false;
	
	for(i=posicao; i<(tamanhoLista(list)-1) ; i++)
		list->reg[i] = list->reg[i+1];
		
	list->numElemento--;
}
int inserirElementoListaOrdenada(LISTA *list, REGISTRO reg){
	int posicao = tamanhoLista(list);
	
	 if(tamanhoLista(list)==MAX)
	 	return false;
	 	
	while(posicao>0 && list->reg[posicao-1].nameUser > reg.nameUser );
	{
		list->reg[posicao] = list->reg[posicao-1];
		posicao--;
	}
	list->reg[posicao]= reg;
	list->numElemento++;
	return true;
}
int buscaBinaria(LISTA *list, TYPEKEY chave){
	int esq, dir, meio;
	esq = 0;
	dir = (tamanhoLista(list)-1);
	
	while(esq<=dir){
		meio = (esq+dir)/2;
		if(list->reg[meio].chave = chave)
			return meio;
		else
			if(list->reg[meio].chave<chave)
				esq=meio+1;
			else
				dir=meio-1;	
	}
	return false;
}
//CADASTRO DEFAULT
void cadastroDefault(LISTA *list);

void criarArquivoDeUsuarios(LISTA *list){
	cadastroDefault(list);
	exibirLista(list); 
	
	arq = fopen("USUARIO.DAT", "w");
	if(arq==NULL){
		printf("\nErro de Criacao de arquivo");
		exit(EXIT_FAILURE );
	} else{
		fwrite(list, sizeof(LISTA), 1, arq);
	}
	
	fclose(arq);
}
void lerArquivoDeUsuarios(LISTA * list){
	

}

//MAIN DO CODIGO
int main(){
	LISTA list;
	REGISTRO reg;
	int opcao;
	
	printf("\nCriar novo cadastro default? (1-sim, 2-nao): "); scanf("%d", &opcao);
	if(opcao==1){
		printf("\nesta na primeira opc");
		criarArquivoDeUsuarios(&list);
		lerArquivoDeUsuarios(&list);
		printf("\ntamanho da lista %d"), tamanhoLista(&list);
		
	} else {
		printf("\nesta na segunda opc");
		lerArquivoDeUsuarios(&list);
		exibirLista(&list);
		printf("\ntamanho da lista %d"), tamanhoLista(&list);

	}
	
	printf("\nDigite seu nome completo(iniciais maiusculas): "); fflush(stdin); gets(reg.nameUser);
	printf("\nDigite seu prontuario(com as letras maiuscula): "); fflush(stdin); scanf("%s", &reg.prontUser);
	
	return 0;
}

//LISTA DEFAULT
void cadastroDefault(LISTA *list){
	int i=0;
		if(tamanhoLista(list)==0){
		REGISTRO reg[DEFAULT_LIST] = {
						{1, "Domingos Lucas Latorre de Oliveira"				, "CJ146456"	},
						{2, "Leandro Pinto Santana"								, "CP220383"	},
						{3, "Rodrigo Ribeiro de Oliveira"						, "RG134168"	},
						{4, "Andre Luiz da Silva"								, "SP030028"	},
						{5, "Claudia Miyuki Werhmuller"							, "SP030041"	},
						{6,	"Claudete de Oliveira Alves"						, "SP03020X"	},
						{7, "Francisco Verissimo Luciano"						, "SP030247"	},
						{8, "Luk Cho Man"										, "SP060380"	},
						{9, "Ivan Francolin Martinez"							, "SP060835"	},
						{10, "Joao Vianei Tamanini"								, "SP060914"	},
						{11, "Jose Oscar Machado Alexandre"						, "SP070038"	},
						{12, "Jose Braz de Araujo"								, "SP070385"	},
						{13, "Paulo Roberto de Abreu"							, "SP070816"	},
						{14, "Jose Braz de Araujo"								, "SP070385"	},
						{15, "Eurides Balbino da Silva "						, "SP07102X"	},
						{16, "Domingos Bernardo Gomes Santos"					, "SP090888"	},
						{17, "Andre Evandro Lourenco"							, "SP100092"	},
						{18, "Miguel Angelo Tancredi Molina"					, "SP102763"	},
						{19, "Antonio Airton Palladino"							, "SP112197"	},
						{20, "Luis Fernando Aires Branco Menegueti"				, "SP145385"	},
						{21, "Antonio Ferreira Viana"							, "SP200827"	},
						{22, "Leonardo Bertholdo "								, "SP204973"	},
						{23, "Marcelo Tavares de Santana"						, "SP20500X"	},
						{24, "Wagner de Paula Gomes"							, "SP215016"	},
						{25, "Daniel Marques Gomes de Morais"					, "SP220097"	},
						{26, "Alexandre Beletti Ferreira"						, "SP226117"	},
						{27, "Vladimir Camelo Pinto"							, "SP240291"	},
						{28, "Leonardo Andrade Motta de Lima"					, "SP24031X"	},
						{29, "Davi Henrique Silva de Oliveira"					, "SP3013081"	},
						{30, "Guilherme Santana Reis de Souza"					, "SP3013278"	},
						{31, "Lorena Moreira Bezerra "							, "SP3013316"	},
						{32, "Arisvitor Alves da Silva Barros"					, "SP3013391"	},
						{33, "Adriana Machado Martins"							, "SP3015572"	},
						{34, "Breno Dias Oliveira"								, "SP3015645"	},
						{35, "Karina Mitie Fujihara"							, "SP3015734"	},
						{36, "Caio Gerstmann"									, "SP3015777"	},
						{37, "Mikael Ducatti Walczak"							, "SP3023168"	},
						{38, "Rafael Ribeiro Santos de Carvalho "				, "SP3024008"	},
						{39, "Rubens Henrique do Nascimento Lotufo"				, "SP3024121"	},
						{40, "Luis Vitor Santos de Sousa"						, "SP3026922"	},						
						{41, "Luiz Eduardo Barbosa Silveira"					, "SP3026922"	},						
						{42, "Gabriela Dias Dutra"								, "SP3030041"	},						
						{43, "Isabela Souza Duarte"								, "SP3030083"	},						
						{44, "Stefany Rodrigues dos Santos"						, "SP303027X"	},						
						{45, "Diego Marques da Costa "							, "SP3032175"	},						
						{46, "Tiago Henrique Cardoso"							, "SP3035646"	},						
						{47, "Elker Rodrigues Baroni Báo"						, "SP3037045"	},						
						{48, "Daniel Teixeira Paulino"							, "SP3037886"	},						
						{49, "Lucas Henrique Lima Soares"						, "SP3038912"	},						
						{50, "Brian Windson Oliveira Siqueira"					, "SP3038963"	},						
						{51, "Victor Hugo Sampa Hamaguti"						, "SP3038998"	},						
						{52, "Edilene Shizue Onizuka Reges "					, "SP3039005"	},						
						{53, "Jesiel Silva Gomes"								, "SP3039081"	},						
						{54, "Mauricio Guery Moreira Leite Saldanha "			, "SP3039102"	},						
						{55, "Ingra Viana Cabral"								, "SP3039366"	},						
						{56, "Isabella Salles Lourenço"							, "SP3039391"	},						
						{57, "Henrique Hiromi Shimada"							, "SP3039421"	},						
						{58, "Guilherme de Paula Vitorino"						, "SP3039439"	},						
						{59, "Rian Santos Macedo"								, "SP3039498"	},						
						{60, "Vinicius Gomes Moreira"							, "SP3039587"	},						
						{61, "Guilherme Fernandes Lima "						, "SP3040674"	},						
						{62, "João Pedro Gomes Figueiredo"						, "SP3040682"	},						
						{63, "Cezar Godoy Nascimento"							, "SP3040755"	},						
						{64, "Amanda Queiroz Carreiro"							, "SP3040836"	},						
						{65, "Marco Antonio de Souza Reis Junior"				, "SP3041671"	},						
						{66, "Cesar Lopes Fernandes"							, "SP890534"	},						
						{67, "Josceli Maria Tenorio"							, "SZ124382"	},						
					
					};
		while(i<DEFAULT_LIST){
			inserirElementoListaOrdenada(list, reg[i]);
			i++;
		}	
	} else
		printf("\n\nja existem dados cadastrados :/");	
}
