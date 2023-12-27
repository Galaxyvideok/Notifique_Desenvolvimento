/*Essa parte do codigo servira para cadastrar outros usuarios e gerar uma lista com 
os nomes, senhas e id's de cada um deles e salvar em um arquivo binario chamado: 'listaUsuarios.bin'*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_USERS 100

struct Localizacao {
    float latitude;
    float longitude;
};

typedef struct Localizacao Localizacao;

struct Usuario {
    int id;
    char nome[100];
    char senha[100];
    Localizacao posicao;
};

typedef struct Usuario Usuario;

FILE* abrirArquivo(char* nomeArq, char* modo) {
    FILE* arq = fopen(nomeArq, modo);
    if (arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        exit(-1);
    }
    return arq;
}

void gravarArquivo2(FILE* arquivo, Usuario* vetor, int qtde) {
    fwrite(&qtde, sizeof(int), 1, arquivo);
    fwrite(vetor, sizeof(Usuario), qtde, arquivo);
}

void cadastrarUsuario(Usuario* usuarios, int* quantidadeUsuarios) {
    if (*quantidadeUsuarios < MAX_USERS) {
        Usuario novoUsuario;
        printf("Cadastro de novo usuario:\n");
        printf("Digite o nome do usuario: ");
        scanf("%s", novoUsuario.nome);
        printf("Digite a senha: ");
        scanf("%s", novoUsuario.senha);
        novoUsuario.id = rand() % 1000;
        printf("Digite a latitude: ");
        scanf("%f", &novoUsuario.posicao.latitude);
        printf("Digite a longitude: ");
        scanf("%f", &novoUsuario.posicao.longitude);

        usuarios[*quantidadeUsuarios] = novoUsuario;
        (*quantidadeUsuarios)++;
    } else {
        printf("Limite de usuarios atingido!\n");
    }
}

int main() {
    FILE* arquivoUsuarios;
    Usuario usuarios[MAX_USERS];
    int quantidadeUsuarios = 0;

    arquivoUsuarios = abrirArquivo("listaUsuarios.bin", "wb");

    int op;
    do {
        printf("\nMENU:\n");
        printf("1 - Cadastrar usuario\n");
        printf("0 - Sair\n");
        printf("Escolha sua opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                cadastrarUsuario(usuarios, &quantidadeUsuarios);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (op != 0);

    // Grava a quantidade total de usuários no início do arquivo
    fseek(arquivoUsuarios, 0, SEEK_SET);
    fwrite(&quantidadeUsuarios, sizeof(int), 1, arquivoUsuarios);

    // Grava os usuários no arquivo
    gravarArquivo2(arquivoUsuarios, usuarios, quantidadeUsuarios);

    fclose(arquivoUsuarios);

    return 0;
}

