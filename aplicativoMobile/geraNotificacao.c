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
#define TAMNOME 100
#define MAXDESC 1000

struct Localizacao {
    float latitude;
    float longetude;
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
    // file do video
    // file da foto
};
typedef struct Notificacao Notificacao;

FILE * abrirArquivo(char * nomeArq, char * modo) {
    FILE * arq = fopen(nomeArq, modo);
    if (arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        exit(-1);
    }
    return arq;
}

void gravarArquivo(FILE * arquivo, Notificacao not) {
    fwrite(&not, sizeof(Notificacao), 1, arquivo);
}

void carregarArquivo2(FILE * arquivo, Notificacao * vetor, int *qtde) {
    fread(qtde, sizeof(int), 1, arquivo);
    fread(vetor, sizeof(Notificacao), *qtde, arquivo);
}

void inserirDados(Notificacao *notiAtual, int desci){
    char tipoNoti[TAMNOME] = { };
    procurarTipo(tipoNoti,desci);
    strcpy(tipoNoti,notiAtual->tipoProblema);
    printf("Descriçao: ");
    scanf(" 999[^\n]s", notiAtual->descricao);

    // esse passo pode ser automatizado por funcao
    printf("Digite a localização: \n");
    printf("Latitude: ");
    scanf("%f", notiAtual->quemNotifica.posicao.latitude);
    printf("Longetude: ");
    scanf("%f", notiAtual->quemNotifica.posicao.longetude);
}

int notiOpcoes(){
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
	} while(op < 0 || op > 6);
	return op;	
}

void imprimirNotificacao(Notificacao not){
    printf("--------------------------------\n");
    printf("Tipo: %s\n", not.tipoProblema);
    printf("Usuario: %s\n", not.quemNotifica.nome);
    printf("Senha do Usuario: %s\n", not.quemNotifica.senha);
    printf("Descriçao: %s\n", not.descricao);
    printf("Localizaçao: %.2f %.2f\n", not.quemNotifica.posicao.latitude,not.quemNotifica.posicao.longetude);
    printf("--------------------------------\n");
}

int main(){
    FILE * arquivoGuardaDados;
    FILE * arquivoListaUsuarios;
    Notificacao notificacaoAtual;
    Notificacao listaUsuarios[MAXDESC]; // Alteração para listaUsuarios

    int quantidadeUsuarios = 0; // Nova variável para armazenar a quantidade de usuários

    arquivoListaUsuarios = abrirArquivo("..bancoDados/listaUsuarios.bin", "rb");
    carregarArquivo2(arquivoListaUsuarios, listaUsuarios, &quantidadeUsuarios);
    fclose(arquivoListaUsuarios);

    int op = 99;
    do{
        buscarUsuario(&notificacaoAtual,listaUsuarios);
        arquivoListaUsuarios = abrirArquivo("..bancoDados/listaUsuarios.bin", "rb");
        carregarArquivo2(arquivoListaUsuarios,listaUsuarios,TAMNOME);
        fclose(arquivoListaUsuarios);
        op = notiOpcoes();
        arquivoGuardaDados = abrirArquivo("..bancoDados/notificacaoEnv.bin", "wb");
        switch (op){
        case 1:
            inserirDados(&notificacaoAtual,op);
            gravarArquivo(arquivoGuardaDados,notificacaoAtual);
            break;

        case 2:
            inserirDados(&notificacaoAtual,op);
            gravarArquivo(arquivoGuardaDados,notificacaoAtual);
            break;
        
        case 3:
            inserirDados(&notificacaoAtual,op);
            gravarArquivo(arquivoGuardaDados,notificacaoAtual);
            break;
        
        case 4:
            inserirDados(&notificacaoAtual,op);
            gravarArquivo(arquivoGuardaDados,notificacaoAtual);
            break;
        
        case 5:
            inserirDados(&notificacaoAtual,op);
            gravarArquivo(arquivoGuardaDados,notificacaoAtual);
            break;
        
        case 6:
            inserirDados(&notificacaoAtual,op);
            gravarArquivo(arquivoGuardaDados,notificacaoAtual);
            break;
        
        case 0:
            fclose(arquivoGuardaDados);
            break;

        default:
            break;
        }
        imprimirNotificacao(notificacaoAtual);
    } while (op != 0);
    printf("\n%s\n", CORTE);
    return 0;
}
