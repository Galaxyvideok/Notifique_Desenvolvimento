/*Esse codigo deve ser a parte responsavel por receber as notificaçoes e criar um arquivo que armazena os dados
, um arquvio chamado: 'notificacaoEnv.bin' alem disso nessa parte vai ser feito uma simulaçao de como os dados serao 
listados no relatorio. Nesse codigo primeiro sera lido do arquivo binario a notificaçao e sera exibida na tela junto
do menu, apos isso o usuario tera a opçao de emcaminhar essa notificaçao, ao fazer isso o codigo deve ler o tipo de problema
da notificaçao e baseado nesse tipo de problema encaminhar para um diretorio designado.
Os diretorios sao:
obras - para as notificaçoes de: Buraco na rua, Poste de Luz Queimado e Semaforo Danificado;
saneamento - para as notificaçoes de: Lixo Urbano em Local Publico e Foco de Agua Parada;
bombeiros - para as notificaçoes de: Foco de Incendio;
para emcaminhar corretamento o programa precisa ter uma funçao que leia dentro da struct qual e o tipoProblema dela
e encaminhe para o diretorio correspondente um novo arquivo binario chamado "notificacaoPronta.bin", lebrando que esses
diretorios estao na mesmo diretorio onde reside o arquivo .c desse codigo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Biblioteca para usar a função getcwd

#define TAMNOME 100
#define MAXDESC 1000

struct Localizacao {
    float latitude;
    float longitude;
};
typedef struct Localizacao Localizacao;

struct Usuario {
    int id;
    char nome[TAMNOME];
    char senha[TAMNOME];
    Localizacao posicao;
};
typedef struct Usuario Usuario;

struct Notificacao {
    Usuario quemNotifica;
    char tipoProblema[TAMNOME];
    char descricao[TAMNOME];
    //imagem da notificação
};
typedef struct Notificacao Notificacao;

FILE *abrirArquivo(char *nomeArq, char *modo) {
    FILE *arq = fopen(nomeArq, modo);
    if (arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        exit(-1);
    }
    return arq;
}

void gravarArquivo(FILE *arquivo, Notificacao not) {
    fwrite(&not, sizeof(Notificacao), 1, arquivo);
}

void imprimirNotificacao(Notificacao not) {
    printf("--------------------------------\n");
    printf("Tipo: %s\n", not.tipoProblema);
    printf("Usuário: %s\n", not.quemNotifica.nome);
    printf("Descrição: %s\n", not.descricao);
    printf("Localização: %.2f %.2f\n", not.quemNotifica.posicao.latitude, not.quemNotifica.posicao.longitude);
    printf("--------------------------------\n");
}

int menu(int *notSemResponsavel, Notificacao notiAtual) {
    int op;
    printf("\n------------------Notificações sem responsáveis------------------\n");
    printf("Total: %d\n", *notSemResponsavel);
    imprimirNotificacao(notiAtual); // deve ser impresso os dados da notificação
    printf("\n\nMENU\n\n");
    printf("1 - Encaminhar Notificação\n");
    printf("2 - Pedir Relatório\n");
    printf("3 - Sair\n");
    printf("Digite a opção: ");
    scanf("%d", &op);
    return op;
}

void encaminharNotificacao(Notificacao notificacao) {
    char diretorio[TAMNOME];
    getcwd(diretorio, sizeof(diretorio)); // Obtém o diretório atual

    // Determinar o subdiretório com base no tipo de problema
    if (strcmp(notificacao.tipoProblema, "Buraco na rua") == 0 ||
        strcmp(notificacao.tipoProblema, "Poste de Luz Queimado") == 0 ||
        strcmp(notificacao.tipoProblema, "Semaforo Danificado") == 0) {
        strcat(diretorio, "/obras/");
    } else if (strcmp(notificacao.tipoProblema, "Lixo Urbano em Local Publico") == 0 ||
               strcmp(notificacao.tipoProblema, "Foco de Agua Parada") == 0) {
        strcat(diretorio, "/saneamento/");
    } else if (strcmp(notificacao.tipoProblema, "Foco de Incendio") == 0) {
        strcat(diretorio, "/bombeiros/");
    } else {
        printf("Tipo de problema desconhecido.\n");
        return;
    }

    // Abrir o arquivo binário no diretório correspondente para escrita
    strcat(diretorio, "notificacaoPronta.bin");
    FILE *arquivoEncaminhado = fopen(diretorio, "ab");

    if (arquivoEncaminhado == NULL) {
        printf("ERRO ao criar o arquivo de notificação pronta.\n");
        return;
    }

    gravarArquivo(arquivoEncaminhado, notificacao); // Gravar a notificação no arquivo
    fclose(arquivoEncaminhado);
}


int main() {
    FILE *arquivo = abrirArquivo("/home/lucas/Documentos/simulaSistema/Notifique_Desenvolvimento/bancoDados/notificacaoEnv.bin", "rb"); // Abre o arquivo binário para leitura

    Notificacao notificacaoAtual;
    int notSemResponsavel = 0;

    fread(&notificacaoAtual, sizeof(Notificacao), 1, arquivo);
    while (!feof(arquivo)) {
        notSemResponsavel++;

        int op = menu(&notSemResponsavel, notificacaoAtual);

        switch (op) {
            case 1:
                encaminharNotificacao(notificacaoAtual);
                break;
            case 2:
                // Implemente a funcionalidade de pedir relatório aqui...
                break;
            case 3:
                fclose(arquivo);
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        fread(&notificacaoAtual, sizeof(Notificacao), 1, arquivo);
    }

    fclose(arquivo);
    return 0;
}