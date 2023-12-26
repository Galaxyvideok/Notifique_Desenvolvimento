/*Esse codigo deve ser a parte responsavel por criar as notificaçoes, para exemplificar as notificaçoes 
serao criadas em formas de arquivo para depois terem seus dados enviados*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INICIO "--------INICIO--------"
#define RESULTADO "-----------RESULTADO-----------"
#define CORTE "-------------------------------------"
#define MAXDESC 10000
#define TAMNOME 100
#define TAMSENHA 15

struct Localizacao{
    int latitude;
    int longetude;
};
typedef struct Localizacao Localizacao;

struct Data{
    int dia;
    int mes;
    int ano;
};
typedef struct Data Data;

struct Usuario{
    char nome[TAMNOME];
    int id;
    Data dataNascimento;
    Localizacao localAtual;
    char email[TAMNOME];
    char senha[TAMSENHA];
};
typedef struct Usuario Usuario;

struct Notificacao{
    Usuario conta;
    char descricao[MAXDESC];
    FILE * foto;
    FILE * video;
};
typedef struct Notificacao Notificacao;

int aleatorio(int n){
    return ( rand() % n) + 1;
}

FILE * abrirArquivo(char * nomeArq, char * modo) {
    FILE * arq;
    arq = fopen( nomeArq, modo );
    if ( arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        exit(-1);
    }
    return arq;
}

void gravarArquivo(FILE * arquivo, Notificacao * vetor, int qtde) {
    fwrite( &qtde, sizeof(int), 1, arquivo  );
    fwrite( vetor, sizeof(Notificacao), qtde, arquivo  );
}

void carregarArquivo(FILE * arquivo, Notificacao * vetor, int *qtde) {
    fread( qtde, sizeof(int), 1, arquivo  );
    fread( vetor, sizeof(Notificacao), *qtde, arquivo  );
}

void inserirUsuario(Usuario *user, int *indiceAtual){
    // id gerar aleatorio
    printf("digite o nome do usuario: ");
    scanf(" %99[^\n]s", user[*indiceAtual].nome);
    printf("Digite o e-mail do usuario: ");
    scanf(" %99[^\n]s", user[*indiceAtual].email);
    printf("Digite a senha do usuario: ");
    scanf(" %99[^\n]s", user[*indiceAtual].senha);
    printf("Digite a data de nascimento do usuario: ");
    scanf("%d%d%d", user[*indiceAtual].dataNascimento.dia,user[*indiceAtual].dataNascimento.mes,user[*indiceAtual].dataNascimento.ano);
    // localizaçao gerar por funcao
}

void listar(Usuario * vetor, int qtde) {
    int i;
    printf("\n%s\n", RESULTADO);
    printf("Senha|Nome                   |telefone|e-mail              |Salario   |\n");
    for( i=0; i < qtde; i++) {
        printf("%9d|%-23s|%8d|%-20s|%10.2f|\n", vetor[i].matricula, vetor[i].individuo.nome, vetor[i].individuo.telefone, vetor[i].individuo.email,vetor[i].salario  );
    }
    printf("\n%s\n", CORTE);
}

int menu(){
	int op;
	printf("\n\nSISTEMA NOTIFIQUE\n\n");
	printf("1 - Inserir usuario\n");
    printf("2 - Criar notificação\n");
	printf("0 - Sair\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
	} while(op < 0 || op > 2);
	return op;	
}

int main(){
    Usuario listaUsuario[MAXDESC];
    int indiceAtual = 0;
    int op;
    Notificacao notAtual;
    FILE * arq;
    // arq = abrirArquivo("..bancoDados/notificacaoEnv.bin", "wb");
    printf("\n%s\n", INICIO);
    do {
		op = menu();
		switch ( op ) {
			case 0:
                fclose(arq);
				break;

			case 1:
                inserirUsuario(listaUsuario,&indiceAtual);
                
                indiceAtual++;
				break;
			case 2:

				break;
			
			default:
				printf ("\n\nOpção inválida!\n\n");
		}
	} while (op != 0);
    return 0;
}
