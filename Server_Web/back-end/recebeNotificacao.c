/*Esse codigo deve ser a parte responsavel por receber as notificaçoes e criar um arquivo que armazena os dados
alem disso nessa parte vai ser feito uma simulaçao de como os dados serao listados no relatorio*/

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



int main(){
    FILE * arquivoGuardaDados;

}
