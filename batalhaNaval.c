#include <stdio.h>
#include <stdlib.h>

// Função: iniciar_tabuleiro
// Objetivo: Inicializa o tabuleiro 10x10 com o valor 0 (água) em todas as posições.
void iniciar_tabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função: Verifica se o posicionamento de um navio é válido, sem ultrapassar limites ou sobrepor outros navios, de acordo com a orientação informada.
int validar_posicoes(int tabuleiro[10][10], int linha, int coluna, int tamanho_navio, char orientacao) {
    if (orientacao == 'H') { // Navio horizontal
        if (coluna + tamanho_navio > 10) {
            printf("Erro: As coordenadas do navio horizontal são inválidas. Ajuste as coordenadas e tente novamente.\n");
            return 0;
        }
        for (int i = 0; i < tamanho_navio; i++) {
            if (tabuleiro[linha][coluna + i] != 0) {
                printf("Erro: O navio horizontal está sobreposto. Ajuste as coordenadas e tente novamente.\n");
                return 0;
            }
        }
    } else if (orientacao == 'V') { // Navio vertical
        if (linha + tamanho_navio > 10) {
            printf("Erro: As coordenadas do navio vertical são inválidas. Ajuste as coordenadas e tente novamente.\n");
            return 0;
        }
        for (int i = 0; i < tamanho_navio; i++) {
            if (tabuleiro[linha + i][coluna] != 0) {
                printf("Erro: O navio vertical está sobreposto. Ajuste as coordenadas e tente novamente.\n");
                return 0;
            }
        }
    } else if (orientacao == 'D') { // Navio diagonal crescente
        if (linha + tamanho_navio > 10 || coluna + tamanho_navio > 10) {
            printf("Erro: As coordenadas do navio diagonal (D) são inválidas. Ajuste as coordenadas e tente novamente.\n");
            return 0;
        }
        for (int i = 0; i < tamanho_navio; i++) {
            if (tabuleiro[linha + i][coluna + i] != 0) {
                printf("Erro: O navio diagonal (D) está sobreposto. Ajuste as coordenadas e tente novamente.\n");
                return 0;
            }
        }
    } else if (orientacao == 'd') { // Navio diagonal decrescente
        if (linha + tamanho_navio > 10 || coluna - tamanho_navio < -1) {
            printf("Erro: As coordenadas do navio diagonal (d) são inválidas. Ajuste as coordenadas e tente novamente.\n");
            return 0;
        }
        for (int i = 0; i < tamanho_navio; i++) {
            if (tabuleiro[linha + i][coluna - i] != 0) {
                printf("Erro: O navio diagonal (d) está sobreposto. Ajuste as coordenadas e tente novamente.\n");
                return 0;
            }
        }
    }
    return 1; // Posições válidas
}

// Função: Posiciona um navio no tabuleiro alterando as posições correspondentes para o valor 3.
void posicionar_navio(int tabuleiro[10][10], int linha, int coluna, int tamanho_navio, char orientacao) {
    for (int i = 0; i < tamanho_navio; i++) {
        if (orientacao == 'H') {
            tabuleiro[linha][coluna + i] = 3;
        } else if (orientacao == 'V') {
            tabuleiro[linha + i][coluna] = 3;
        } else if (orientacao == 'D') {
            tabuleiro[linha + i][coluna + i] = 3;
        } else if (orientacao == 'd') {
            tabuleiro[linha + i][coluna - i] = 3;
        }
    }
}

// Função: Exibe o tabuleiro no console, utilizando: 0 para água, 3 para navio e 5 para áreas afetadas pela habilidade.
void exibir_tabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// ================= FUNÇÕES PARA AS HABILIDADES ================= 

// Função: Cria uma matriz 5x5 representando a área de efeito em forma de cone,  onde o ponto de origem (o topo do cone) está na parte superior central e a área se expande para baixo.
void criar_habilidade_cone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // A condição gera um cone (ponto de origem na primeira linha central)
            habilidade[i][j] = (j >= 2 - i && j <= 2 + i) ? 1 : 0;
        }
    }
}

// Função: Cria uma matriz 5x5 representando a área de efeito em forma de cruz, considerando o centro da matriz como o ponto de origem.
void criar_habilidade_cruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            habilidade[i][j] = (i == 2 || j == 2) ? 1 : 0;
        }
    }
}

// Função: Cria uma matriz 5x5 representando a área de efeito com formato de octaedro (ou vista frontal de um octaedro, similar a um losango) com o centro na posição (2,2).
void criar_habilidade_octaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            habilidade[i][j] = (abs(2 - i) + abs(2 - j) <= 2) ? 1 : 0;
        }
    }
}

// Função: Sobrepõe a matriz de habilidade ao tabuleiro, centrando a área de efeito no ponto de origem definido (origem_linha, origem_coluna). As posições com valor 1 na matriz de habilidade serão marcadas no tabuleiro com o valor 5.
void aplicar_habilidade_ao_tabuleiro(int tabuleiro[10][10], int habilidade[5][5], int origem_linha, int origem_coluna) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int lin = origem_linha - 2 + i;
            int col = origem_coluna - 2 + j;
            if (lin >= 0 && lin < 10 && col >= 0 && col < 10 && habilidade[i][j] == 1) {
                tabuleiro[lin][col] = 5;
            }
        }
    }
}

// ================= FUNÇÃO PRINCIPAL ================= 

int main() {
    int tabuleiro[10][10];
    iniciar_tabuleiro(tabuleiro);

    int tamanho_navio = 3;

    // Posicionamento dos navios utilizando as funções originais:
    if (validar_posicoes(tabuleiro, 5, 4, tamanho_navio, 'H')) {
        posicionar_navio(tabuleiro, 5, 4, tamanho_navio, 'H');
    } else {
        printf("Erro: Coordenadas inválidas. Programa encerrado.\n");
        return 1;
    }

    if (validar_posicoes(tabuleiro, 6, 8, tamanho_navio, 'V')) {
        posicionar_navio(tabuleiro, 6, 8, tamanho_navio, 'V');
    } else {
        printf("Erro: Coordenadas inválidas. Programa encerrado.\n");
        return 1;
    }

    if (validar_posicoes(tabuleiro, 1, 1, tamanho_navio, 'D')) {
        posicionar_navio(tabuleiro, 1, 1, tamanho_navio, 'D');
    } else {
        printf("Erro: Coordenadas inválidas. Programa encerrado.\n");
        return 1;
    }

    if (validar_posicoes(tabuleiro, 1, 9, tamanho_navio, 'd')) {
        posicionar_navio(tabuleiro, 1, 9, tamanho_navio, 'd');
    } else {
        printf("Erro: Coordenadas inválidas. Programa encerrado.\n");
        return 1;
    }

    // Criação e aplicação das áreas de habilidade. As matrizes de habilidade possuem dimensão 5x5.
    int habilidade_cone[5][5], habilidade_cruz[5][5], habilidade_octaedro[5][5];

    criar_habilidade_cone(habilidade_cone);
    criar_habilidade_cruz(habilidade_cruz);
    criar_habilidade_octaedro(habilidade_octaedro);

    // Definindo pontos de origem para aplicação das habilidades: O primeiro parâmetro da função aplicar_habilidade_ao_tabuleiro é o tabuleiro, o segundo é a matriz de habilidade e os últimos são as coordenadas do ponto central.
    aplicar_habilidade_ao_tabuleiro(tabuleiro, habilidade_cone, 2, 2);
    aplicar_habilidade_ao_tabuleiro(tabuleiro, habilidade_cruz, 5, 5);
    aplicar_habilidade_ao_tabuleiro(tabuleiro, habilidade_octaedro, 8, 8);

    // Exibe o tabuleiro final com navios e áreas de efeito das habilidades.
    printf("Tabuleiro:\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}
