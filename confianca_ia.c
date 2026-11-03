#include <stdio.h>
#include <stdlib.h>

void lerConfiancas(float confiancas[], int n);
float calcularMedia(float confiancas[], int n);
int contarAceitas(float confiancas[], int n, float limiar);
void buscarMaiorConfianca(float confiancas[], int n, int *indice, float *maior);
void mostrarResultados(float confiancas[], int n, float limiar);

void alterarConfianca(float *valor, float nova);

int main(void) {
    int n, aceitas, revisao, indiceMaior;
    float limiar, media, maior;
    float *confiancas;
    int posição;  //Questão extra 
    float nova;

    // Leitura e validacao de n 
    do {
        printf("Quantidade de previsoes (1 a 1000): ");
        scanf("%d", &n);
        if (n < 1 || n > 1000) {
            printf("Valor invalido!\n");
        }
    } while (n < 1 || n > 1000);

    // Leitura e validacao do limiar 
    do {
        printf("Limiar (0 a 1): ");
        scanf("%f", &limiar);
        if (limiar < 0.0f || limiar > 1.0f) {
            printf("Valor invalido!\n");
        }
    } while (limiar < 0.0f || limiar > 1.0f);

    do {
        printf("Posicao a alterar (1 a %d): ", n); //alterar confianca
        scanf("%d", &posição);
        if (posição < 1 || posição > n) {
            printf("Valor invalido!\n");
        }
    } while (posição < 1 || posição > n);

    do {
        printf("Nova confianca (0 a 1): ");
        scanf("%f", &nova);
        if (nova < 0.0f || nova > 1.0f) {
            printf("Valor invalido!\n");
        }
    } while (nova < 0.0f || nova > 1.0f);
    
     alterarConfianca(&confiancas[posição - 1], nova); //alterar confianca
    // alterarConfianca(confiancas + (posição - 1), nova); 

    confiancas = malloc(n * sizeof *confiancas);
    if (confiancas == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return 1;
    }

    lerConfiancas(confiancas, n);

    media = calcularMedia(confiancas, n);
    aceitas = contarAceitas(confiancas, n, limiar);
    revisao = n - aceitas;
    buscarMaiorConfianca(confiancas, n, &indiceMaior, &maior);
   
    mostrarResultados(confiancas, n, limiar);

    printf("\n--- Resumo ---\n");
    printf("Media das confiancas: %.2f\n", media);
    printf("Previsoes aceitas: %d\n", aceitas);
    printf("Previsoes em revisao: %d\n", revisao);
    printf("Maior confianca: %.2f (previsao %d)\n", maior, indiceMaior + 1);

    free(confiancas);
    confiancas = NULL;

    return 0;
}

void alterarConfianca(float *valor, float nova) {  // fun. alterarConfianca
    *valor = nova;
}  

void lerConfiancas(float confiancas[], int n) {    //fun. lerConfianca
    int i;
    for (i = 0; i < n; i++) {
        do {
            printf("Confianca da previsao %d (0 a 1): ", i + 1);
            scanf("%f", &confiancas[i]);
            if (confiancas[i] < 0.0f || confiancas[i] > 1.0f) {
                printf("Valor invalido!\n");
            }
        } while (confiancas[i] < 0.0f || confiancas[i] > 1.0f);
    }
}

float calcularMedia(float confiancas[], int n) {  //fun. calcularMedia
    int i;
    float soma = 0.0f;
    for (i = 0; i < n; i++) {
        soma += confiancas[i];
    }
    return soma / n;
}

int contarAceitas(float confiancas[], int n, float limiar) {  //fun. contarAceitas
    int i, cont = 0;
    for (i = 0; i < n; i++) {
        if (confiancas[i] >= limiar) {
            cont++;
        }
    }
    return cont;
}

void buscarMaiorConfianca(float confiancas[], int n, int *indice, float *maior) {  //fun. buscarMaiorConfiaça
    int i;
    *indice = 0;
    *maior = confiancas[0];
    for (i = 1; i < n; i++) {
        if (confiancas[i] > *maior) { /* > estrito: mantem a primeira em empate */
            *maior = confiancas[i];
            *indice = i;
        }
    }
}

void mostrarResultados(float confiancas[], int n, float limiar) {  // fun. mostrarResultado
    int i;
    printf("\nPrevisao | Confianca | Encaminhamento\n");
    for (i = 0; i < n; i++) {
        printf("%8d | %9.2f | %s\n", i + 1, confiancas[i],
               confiancas[i] >= limiar ? "ACEITAR" : "REVISAR");
    }
}

/*
alterarConfianca (confiancas + (posição - 1), nova);  // alterar confiança

float *p;
for (p = confiancas; p < confiancas + n; p++) {
    printf("Confianca: %.2f\n", *p);
}

*/
