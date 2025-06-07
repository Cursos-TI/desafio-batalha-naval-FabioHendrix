#include <stdio.h>


void iniciar_tabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0; 
        }
    }
}

//Verifica se o posicionamento de um navio é válido dentro do tabuleiro (sem exceder os limites ou sobrepor outros navios)
int validar_posicoes(int tabuleiro[10][10], int linha, int coluna, int tamanho_navio, char orientacao) { 
    if (orientacao == 'H') { // Verifica se as coordenadas do navio horizontal são válidas.
        if (coluna + tamanho_navio > 10) {
            printf("Erro: As coordenadas do navio horizontal são inválidas. Ajuste as coordenadas e tente novamente.\n");
            return 0; // Coordenadas inválidas
        }
        for (int i = 0; i < tamanho_navio; i++) { // Verifica se há sobreposição
            if (tabuleiro[linha][coluna + i] != 0) {
                printf("Erro: O navio horizontal está sobreposto. Ajuste as coordenadas e tente novamente.\n");
                return 0;
            }
        }
    } else if (orientacao == 'V') { // Verifica se as coordenadas do navio vertical são válidas.
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
    } else if (orientacao == 'D') { // Valida navio na diagonal crescente
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
    } else if (orientacao == 'd') { // Valida navio na diagonal decrescente
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


//Posiciona um navio no tabuleiro, alterando os valores nas posições ocupadas para 3.
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

//Exibe o tabuleiro no console, mostrando os valores de cada posição.
void exibir_tabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]); 
        }
        printf("\n");
    }
}


int main() {
    
    
    int tabuleiro[10][10];
    iniciar_tabuleiro(tabuleiro);

    int tamanho_navio = 3;

    
    // Verifica a validade das coordenadas e posiciona os navios.
    
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

    
    printf("Tabuleiro:\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}
