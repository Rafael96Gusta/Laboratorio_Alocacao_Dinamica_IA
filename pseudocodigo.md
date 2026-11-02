# Etapa 1 — Pseudocódigo

## Algoritmo principal
```
INÍCIO
  inteiro n, aceitas, revisao, indiceMaior
  real limiar, media, maior
  ponteiro para real confiancas

  REPETIR
    ler n
    SE n < 1 OU n > 1000 ENTÃO escrever "Valor inválido"
  ATÉ n >= 1 E n <= 1000

  REPETIR
    ler limiar
    SE limiar < 0 OU limiar > 1 ENTÃO escrever "Valor inválido"
  ATÉ limiar >= 0 E limiar <= 1

  confiancas <- RESERVAR(n * tamanho de um real)      // exatamente n reais
  SE confiancas = NULO ENTÃO
    escrever "Erro: memória insuficiente"
    ENCERRAR com código 1                              // sem acessar o vetor
  FIM SE

  lerConfiancas(confiancas, n)
  media   <- calcularMedia(confiancas, n)
  aceitas <- contarAceitas(confiancas, n, limiar)
  revisao <- n - aceitas
  buscarMaiorConfianca(confiancas, n, ENDEREÇO de indiceMaior, ENDEREÇO de maior)

  mostrarResultados(confiancas, n, limiar)
  escrever media, aceitas, revisao, indiceMaior + 1, maior

  LIBERAR(confiancas)                                  // uma única vez
  confiancas <- NULO
FIM
```

## 1. lerConfiancas(vetor confiancas [endereço do bloco], n)
Lê: n valores. Produz: preenche o vetor.
```
PARA i DE 0 ATÉ n-1
  REPETIR
    ler confiancas[i]
    SE confiancas[i] < 0 OU confiancas[i] > 1 ENTÃO escrever "Valor inválido"
  ATÉ confiancas[i] >= 0 E confiancas[i] <= 1
FIM PARA
```

## 2. calcularMedia(confiancas, n) → real
```
soma <- 0
PARA i DE 0 ATÉ n-1: soma <- soma + confiancas[i]
RETORNAR soma / n
```

## 3. contarAceitas(confiancas, n, limiar) → inteiro
```
cont <- 0
PARA i DE 0 ATÉ n-1
  SE confiancas[i] >= limiar ENTÃO cont <- cont + 1
RETORNAR cont
```

## 4. buscarMaiorConfianca(confiancas, n, *indice, *maior)
Parâmetros por endereço (saída): indice e maior.
```
*indice <- 0
*maior  <- confiancas[0]
PARA i DE 1 ATÉ n-1
  SE confiancas[i] > *maior ENTÃO     // estrito: empate fica com a primeira
    *maior  <- confiancas[i]
    *indice <- i
```

## 5. mostrarResultados(confiancas, n, limiar)
```
PARA i DE 0 ATÉ n-1
  SE confiancas[i] >= limiar ENTÃO destino <- "ACEITAR" SENÃO destino <- "REVISAR"
  escrever i + 1, confiancas[i] (2 casas), destino
```

---

# Explicações para a apresentação
- **Memória e n:** o malloc reserva n × sizeof(float) bytes — exatamente o necessário, não 1000 posições.
- **Por que testar NULL:** malloc devolve NULL se faltar memória; acessar o vetor nesse caso seria comportamento indefinido.
- **Inicialização:** os valores são preenchidos em lerConfiancas (antes de qualquer cálculo); a soma começa em 0; o maior começa com confiancas[0], já lido.
- **Parâmetros de saída:** buscarMaiorConfianca recebe &indiceMaior e &maior; ao escrever em *indice e *maior, altera as variáveis de main.
- **free uma única vez:** liberar duas vezes é erro (double free); depois do free atribui-se NULL para não usar o bloco liberado.
