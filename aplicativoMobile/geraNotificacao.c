/*Essa parte do codigo deve gerar a notificaçao resgatando os dados de um usuario dentro do
diretorio banco de dados e com o arquivo 'ListaUsuarios.bin' para selecionar os usuario e
pedir dele os dados da notificacao, escolhendo tambem os tipos disponiveis de notificaçao*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INICIO "--------INICIO--------"
#define RESULTADO "-----------RESULTADO-----------"
#define CORTE "-------------------------------------"

FILE * abrirArquivo(char * nomeArq, char * modo) {
    FILE * arq;
    arq = fopen( nomeArq, modo );
    if ( arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        exit(-1);
    }
    return arq;
}




int notiOpcoes(){
    int op;
    printf("\n\n\nNOTIFICAÇÕES\n\n\n");
    printf("1 - Buraco na rua\n");
    printf("2 - Poste de Luz queimado\n");
    printf("3 - Lixo Urbano em Local Publico\n");
    printf("4 - Semaforo Danificado\n");
    printf("5 - Foco de Agua Parada\n");
    printf("6 - Foco de Incendio\n");
	printf("0 - Sair\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
	} while(op < 0 || op > 6);
	return op;	
}

int main(){
    FILE * arquivoGuardaDados;

}