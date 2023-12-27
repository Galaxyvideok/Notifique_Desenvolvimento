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
    FILE * arq;
    arq = fopen( nomeArq, modo );
    if ( arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        exit(-1);
    }
    return arq;
}

int pesquisar(Notificacao *lista, int pesq){

}

void gravarArquivo(FILE * arquivo, Notificacao not) {
    fwrite( &not, sizeof(Notificacao), 1, arquivo);
}

void carregarArquivo(FILE * arquivo, Notificacao not) {
    fwrite( &not, sizeof(Notificacao), 1, arquivo);
}

void carregarArquivo2(FILE * arquivo, Notificacao * vetor, int *qtde) {
    fread( qtde, sizeof(int), 1, arquivo  );
    fread( vetor, sizeof(Notificacao), *qtde, arquivo  );
}

void procurarTipo(char *nome, int numeroTipo){
    if (numeroTipo == 1){
        strcat(nome,"Buraco na Rua");
    }else if (numeroTipo == 2){
        strcat(nome,"Poste de Luz Queimado");
    }else if (numeroTipo == 3){
        strcat(nome,"Lixo Urbano em Local Publico");
    }else if (numeroTipo == 3){
        strcat(nome,"Semaforo Danificado");
    }else if (numeroTipo == 4){
        strcat(nome,"Foco de Agua Parada");
    }else{
        strcat(nome,"Foco de Incendio");
    }
}

// essa funçao tambem deve ser automatizada
void buscarUsuario(Notificacao *not, Notificacao * listaUsuarios){
    int idUsuario;
    do{
        printf("Digite o id do usuario: ");
        scanf("%d", idUsuario);
    } while (pesquisar(listaUsuarios,idUsuario) == -1);
    not->quemNotifica = listaUsuarios[idUsuario].quemNotifica;
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

int main(){
    FILE * arquivoGuardaDados;
    FILE * arquivoListaUsuarios;
    Notificacao notificacaoAtual;
    Notificacao listaUsuarios[TAMNOME];
    int i;
    int op  = 99;
    arquivoGuardaDados = abrirArquivo("..bancoDados/notificacaoEnv.bin", "wb");
    for (i = 0; i < MAXDESC; i++){
        carregarArquivo2(arquivoListaUsuarios,listaUsuarios,i);
    }
    printf("\n%s\n", CORTE);
    do{
        buscarUsuario(&notificacaoAtual,listaUsuarios);
        op = notiOpcoes();
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
    } while (op != 0);
    printf("\n%s\n", CORTE);
    return 0;
}