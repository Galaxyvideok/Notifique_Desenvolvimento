#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define inicio "--------INICIO--------"
#define resultado "-----------RESULTADO-----------"
#define corte "-------------------------------------"


int pedirTamanho(char conjunto) {
    int num;
    do {
        printf("Digite o tamanho do conjunto %c: ", conjunto);
        scanf("%d", &num);
    } while (num <= 0);
    return num;
}

int pesquisar(int vetor[],int quanti,int pesq){
    int i;
    for(i = 0; i < quanti; i++){ 
        if(vetor[i] == pesq){
            return i;
        }
    }
    return -1;
}

void inserirConjunto(int conjunto[], int tamanho){
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("Digite o %dº número: ", i + 1);
        scanf("%d", &conjunto[i]);
    }
}

int uniao(int conjuntoA[], int conjuntoB[], int tamanho1, int tamanho2, int conjuntoUniao[]){
    int i, tamanhoUniao = 0;
    
    for (i = 0; i < tamanho1; i++) {
        conjuntoUniao[tamanhoUniao] = conjuntoA[i];
        tamanhoUniao++;
    }
    
    for (i = 0; i < tamanho2; i++) {
        if (pesquisar(conjuntoUniao, tamanhoUniao, conjuntoB[i]) == -1) {
            conjuntoUniao[tamanhoUniao] = conjuntoB[i];
            tamanhoUniao++;
        }
    }
    
    return tamanhoUniao; 
}

int intersessao(int conjuntoA[], int conjuntoB[], int tamanho1, int tamanho2, int conjuntoInter[]) {
    int i, j, tamanhoInter = 0;
    
    for (i = 0; i < tamanho1; i++) {
        for (j = 0; j < tamanho2; j++) {
            if (conjuntoA[i] == conjuntoB[j]) {
                if (pesquisar(conjuntoInter, tamanhoInter, conjuntoA[i]) == -1) {
                    conjuntoInter[tamanhoInter] = conjuntoA[i];
                    tamanhoInter++;
                }
            }
        }
    }
    
    return tamanhoInter; 
}

int subtracao(int conjuntoA[], int conjuntoB[], int tamanho1, int tamanho2, int conjuntoSubtracao[]) {
    int i, tamanhoSubtracao = 0;
    
    for (i = 0; i < tamanho1; i++) {
        if (pesquisar(conjuntoB, tamanho2, conjuntoA[i]) == -1) {
            conjuntoSubtracao[tamanhoSubtracao] = conjuntoA[i];
            tamanhoSubtracao++;
        }
    }
    
    return tamanhoSubtracao; 
}

int diferencaSimetrica(int conjuntoA[], int conjuntoB[], int tamanho1, int tamanho2, int conjuntoDiferencaSimetrica[]) {
    int i, tamanhoDiferencaSimetrica = 0;

    for (i = 0; i < tamanho1; i++) {
        if (pesquisar(conjuntoB, tamanho2, conjuntoA[i]) == -1) {
            conjuntoDiferencaSimetrica[tamanhoDiferencaSimetrica] = conjuntoA[i];
            tamanhoDiferencaSimetrica++;
        }
    }

    for (i = 0; i < tamanho2; i++) {
        if (pesquisar(conjuntoA, tamanho1, conjuntoB[i]) == -1) {
            conjuntoDiferencaSimetrica[tamanhoDiferencaSimetrica] = conjuntoB[i];
            tamanhoDiferencaSimetrica++;
        }
    }

    return tamanhoDiferencaSimetrica;
}

void produtoCartesiano(int conjuntoA[], int conjuntoB[], int tamanho1, int tamanho2) {
    printf("\nProduto Cartesiano (A x B):\n");
    int i, j;
    for (i = 0; i < tamanho1; i++) {
        for (j = 0; j < tamanho2; j++) {
            if (pesquisar(conjuntoA, tamanho1, conjuntoA[i]) != -1 && pesquisar(conjuntoB, tamanho2, conjuntoB[j]) != -1) {
                printf("(%d, %d)\n", conjuntoA[i], conjuntoB[j]);
            }
        }
    }
}

void menu(){
    printf("\n1 - INSERIR OS CONJUNTOS A E B\n");
    printf("\n2 - A U B\n");
    printf("\n3 - A ∩ B\n");
    printf("\n4 - A - B\n");
    printf("\n5 - B - A\n");
    printf("\n6 - A ∆ B\n");
    printf("\n7 - A x B\n");
    printf("\n8 - SAIR\n");
}

int main() {
    SetConsoleOutputCP(65001);
    printf("\n%s\n", inicio);
    int opcao = 0;
    int tamanho1, tamanho2;
    int conjtA[100], conjtB[100], conjtUniao[200], conjtIntersecao[100], conjtSubtracaoA_B[100]; 
    int tamanhoUniao = 0;
    int tamanhoIntersecao = 0;
    int tamanhoSubtracaoA_B = 0;
    int conjtSubtracaoB_A[100], conjtDiferencaSimetrica[200]; 
    int tamanhoSubtracaoB_A = 0;
    int tamanhoDiferencaSimetrica = 0;
    int i;
    do {
        menu();
        printf("\nDigite a opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                tamanho1 = pedirTamanho('A');
                tamanho2 = pedirTamanho('B');
                inserirConjunto(conjtA, tamanho1);
                inserirConjunto(conjtB, tamanho2);
                printf("\n%s\n", corte);
                break;

            case 2:
                tamanhoUniao = uniao(conjtA, conjtB, tamanho1, tamanho2, conjtUniao);
                printf("\n%s\n", resultado);
                printf("Conjunto de União: ");
                for (i = 0; i < tamanhoUniao; i++) {
                    printf("%d ", conjtUniao[i]);
                }
                printf("\n%s\n", corte);
                break;

            case 3:
                tamanhoIntersecao = intersessao(conjtA, conjtB, tamanho1, tamanho2, conjtIntersecao);
                printf("\n%s\n", resultado);
                printf("Conjunto de Interseção: ");
                for (i = 0; i < tamanhoIntersecao; i++) {
                    printf("%d ", conjtIntersecao[i]);
                }
                printf("\n%s\n", corte);
                break;

            case 4:
                tamanhoSubtracaoA_B = subtracao(conjtA, conjtB, tamanho1, tamanho2, conjtSubtracaoA_B);
                printf("\n%s\n", resultado);
                printf("Resultado da subtração (A - B): ");
                for (i = 0; i < tamanhoSubtracaoA_B; i++) {
                    printf("%d ", conjtSubtracaoA_B[i]);
                }
                printf("\n%s\n", corte);
                break;

            case 5:
                tamanhoSubtracaoB_A = subtracao(conjtB, conjtA, tamanho2, tamanho1, conjtSubtracaoB_A);
                printf("\n%s\n", resultado);
                printf("Resultado da subtração (B - A): ");
                for (i = 0; i < tamanhoSubtracaoB_A; i++) {
                    printf("%d ", conjtSubtracaoB_A[i]);
                }
                printf("\n%s\n", corte);
                break;

            case 6:
                tamanhoDiferencaSimetrica = diferencaSimetrica(conjtA, conjtB, tamanho1, tamanho2, conjtDiferencaSimetrica);
                printf("\n%s\n", resultado);
                printf("Resultado da diferença simétrica (A ∆ B): ");
                for (i = 0; i < tamanhoDiferencaSimetrica; i++) {
                    printf("%d ", conjtDiferencaSimetrica[i]);
                }
                printf("\n%s\n", corte);
                break;

            case 7:
                printf("\n%s\n", resultado);
                produtoCartesiano(conjtA, conjtB, tamanho1, tamanho2);
                printf("\n%s\n", corte);
                break;

            case 8:
                break;

            }
    } while (opcao != 8);
    return 0;
}