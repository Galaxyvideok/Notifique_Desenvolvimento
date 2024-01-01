/*Esse codigo deve ser a parte responsavel por receber as notificaçoes e criar um arquivo que armazena os dados
, um arquvio chamado: 'notificacaoEnv.bin' alem disso nessa parte vai ser feito uma simulaçao de como os dados serao 
listados no relatorio*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    //imagem da notificaçao
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

void carregarArquivo2(FILE *arquivo, Usuario *vetor, int *qtde) {
    fread(qtde, sizeof(int), 1, arquivo);
    fread(vetor, sizeof(Usuario), *qtde, arquivo);
}

void inserirDados(Notificacao *notiAtual, int desc) {
    char tiposNotificacoes[6][TAMNOME] = {
        "Buraco na rua",
        "Poste de Luz Queimado",
        "Lixo Urbano em Local Publico",
        "Semaforo Danificado",
        "Foco de Agua Parada",
        "Foco de Incendio"
    };

    strcpy(notiAtual->tipoProblema, tiposNotificacoes[desc - 1]);

    printf("Descrição: ");
    scanf(" %[^\n]s", notiAtual->descricao);

    printf("Digite a localização:\n");
    printf("Latitude: ");
    scanf("%f", &notiAtual->quemNotifica.posicao.latitude);
    printf("Longitude: ");
    scanf("%f", &notiAtual->quemNotifica.posicao.longitude);
}

void imprimirNotificacao(Notificacao not) {
    printf("--------------------------------\n");
    printf("Tipo: %s\n", not.tipoProblema);
    printf("Usuário: %s\n", not.quemNotifica.nome);
    printf("Descrição: %s\n", not.descricao);
    printf("Localização: %.2f %.2f\n", not.quemNotifica.posicao.latitude, not.quemNotifica.posicao.longitude);
    printf("--------------------------------\n");
}

void buscarUsuarioPorNome(Usuario *usuario, char *nomeProcurado, Usuario *listaUsuarios, int qtdeUsuarios) {
    int i;
    for (i = 0; i < qtdeUsuarios; i++) {
        if (strcmp(listaUsuarios[i].nome, nomeProcurado) == 0) {
            *usuario = listaUsuarios[i];
            return;
        }
    }
    printf("Usuário com nome %s não encontrado.\n", nomeProcurado);
    exit(-1);
}

int menu(){
    
}

int main() {
    
    return 0;
}
