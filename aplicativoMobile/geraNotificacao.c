/*Essa parte do codigo deve gerar a notificaçao resgatando os dados de um usuario dentro do
diretorio banco de dados e com o arquivo 'ListaUsuarios.bin' para selecionar os usuario e
pedir dele os dados da notificacao, escolhendo tambem os tipos disponiveis de notificaçao*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMNOME 100
#define MAXDESC 1000
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

struct Imagem {
    unsigned char *dados;
    int largura;
    int altura;
    int canais;
};
typedef struct Imagem Imagem;

struct Notificacao {
    Usuario quemNotifica;
    char tipoProblema[TAMNOME];
    char descricao[TAMNOME];
    Imagem imagem; // Estrutura separada para a imagem
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

    // Se houver imagem na notificação, escreve os dados da imagem no arquivo
    if (not.imagem.dados != NULL) {
        fwrite(not.imagem.dados, sizeof(unsigned char), not.imagem.largura * not.imagem.altura * not.imagem.canais, arquivo);
    }
}

void liberarMemoria(Imagem *img) {
    if (img->dados != NULL) {
        stbi_image_free(img->dados);
    }
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

    char nomeArquivoImagem[TAMNOME];
    printf("Digite o nome do arquivo da imagem: ");
    scanf(" %[^\n]s", nomeArquivoImagem);

    // Carrega a imagem usando a STB Image
    notiAtual->imagem.dados = stbi_load(nomeArquivoImagem, &notiAtual->imagem.largura, &notiAtual->imagem.altura, &notiAtual->imagem.canais, 0);

    if (notiAtual->imagem.dados == NULL) {
        printf("Erro ao carregar a imagem.\n");
        liberarMemoria(&notiAtual->imagem);
        exit(-1);
    }
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

int notiOpcoes() {
    int op;
    printf("\n\n\nNOTIFICAÇÕES\n\n\n");
    printf("1 - Buraco na rua\n");
    printf("2 - Poste de Luz Queimado\n");
    printf("3 - Lixo Urbano em Local Publico\n");
    printf("4 - Semaforo Danificado\n");
    printf("5 - Foco de Agua Parada\n");
    printf("6 - Foco de Incendio\n");
    printf("0 - Sair\n");
    do {
        printf("Escolha sua opção: ");
        scanf(" %d", &op);
    } while (op < 0 || op > 6);
    return op;
}

int main() {
    FILE *arquivoGuardaDados;
    FILE *arquivoListaUsuarios;
    Notificacao notificacaoAtual;
    Usuario listaUsuarios[MAXDESC];

    int quantidadeUsuarios = 0;

    arquivoListaUsuarios = abrirArquivo("../../bancoDados/listaUsuarios.bin", "rb");
    carregarArquivo2(arquivoListaUsuarios, listaUsuarios, &quantidadeUsuarios);
    fclose(arquivoListaUsuarios);

    char nomeProcurado[TAMNOME];
    printf("Digite o nome do usuário: ");
    scanf(" %[^\n]s", nomeProcurado);

    Usuario usuarioAtual;
    buscarUsuarioPorNome(&usuarioAtual, nomeProcurado, listaUsuarios, quantidadeUsuarios);

    strcpy(notificacaoAtual.quemNotifica.nome, usuarioAtual.nome);
    strcpy(notificacaoAtual.quemNotifica.senha, usuarioAtual.senha);

    int op;
    printf("\n\n\nNOTIFICAÇÕES\n\n\n");
    printf("1 - Buraco na rua\n");
    printf("2 - Poste de Luz Queimado\n");
    printf("3 - Lixo Urbano em Local Publico\n");
    printf("4 - Semaforo Danificado\n");
    printf("5 - Foco de Agua Parada\n");
    printf("6 - Foco de Incendio\n");
    printf("0 - Sair\n");

    printf("Escolha sua opção: ");
    scanf("%d", &op);

    switch (op) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            inserirDados(&notificacaoAtual, op);
            arquivoGuardaDados = abrirArquivo("../../bancoDados/notificacaoEnv.bin", "wb");
            gravarArquivo(arquivoGuardaDados, notificacaoAtual);
            fclose(arquivoGuardaDados);
            imprimirNotificacao(notificacaoAtual);
            break;
        case 0:
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
    

    liberarMemoria(&notificacaoAtual.imagem);

    return 0;
}
