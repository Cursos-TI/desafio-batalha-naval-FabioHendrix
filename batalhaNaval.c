#include <stdio.h>

//Função para iniciar o tabuleiro
void iniciar_tabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0; //Inicializa o tabuleiro com água (valor 0)
        }
    }
}

//Funçao para verificar se os navios estão dentro dos limites do tabuleiro
int validar_posicoes(int tabuleiro[10][10], int linha, int coluna, int tamanho_navio, char orientacao) {
    if (orientacao == 'H') { //Verifica se as coordenadas do navio horizontal são validas.
        if (coluna + tamanho_navio > 10) {
            printf("Erro: As coordenadas do navio horizontal são invalidas. Ajuste as coordenadas e tente novamente.\n");
            return 0; //Coordenadas inválidas
        }
        for (int i = 0; i < tamanho_navio; i++) { //Verifica se há sobreposição
            if (tabuleiro[linha][coluna + i] != 0) {
                printf("Erro: Os navios não podem estar sobrepostos. Ajuste as coordenadas e tente novamente.\n");
                return 0; //Erro: Sobreposição (posição inválida)
            }
        }
    } else if (orientacao == 'V') { //Verifica se as coordenadas do navio vertical são validas.
        if (linha + tamanho_navio > 10) {
            printf("Erro: As coordenadas do navio vertical são invalidas. Ajuste as coordenadas e tente novamente.\n");
            return 0; //Coordenadas inválidas
        }
        for (int i = 0; i < tamanho_navio; i++) { //Verifica se há sobreposição
            if (tabuleiro[linha + i][coluna] != 0) {
                printf("Erro: Os navios não podem estar sobrepostos. Ajuste as coordenadas e tente novamente.\n");
                return 0; //Erro: Sobreposição (posição inválida)
            }
        }
    } 
    return 1; //O programa segue normalmente caso não haja erros.
}

//Função para posicionar os navios no tabuleiro
void posicionar_navio(int tabuleiro[10][10], int linha, int coluna, int navio[], int tamanho_navio, char orientacao) {
    for (int i =0; i < tamanho_navio; i++) {
        if (orientacao == 'H') { //Define a posição do navio horizontal
            tabuleiro[linha][coluna + i] = navio[i];
            
        } else if (orientacao == 'V') { //Define a posição do navio vertical
            tabuleiro[linha + i][coluna] = navio[i];
        }   
    }
}   
 
//Função para exibir o navio atualizado    
void exibir_tabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++) { //Loop externo e interno que percorre a matriz e preenche o tabuleiro
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]); //Exibe os valores do tabuleiro
        }
        printf("\n");
    }
}

//Função principal    
int main () {
    
    //Iniciando o tabuleiro
    int tabuleiro[10][10];
    iniciar_tabuleiro(tabuleiro);
    
    //Vetores representando os navios
    int navio_horizontal[3] = {3,3,3};
    int navio_vertical[3] = {3,3,3};
    
    int tamanho_navio = 3;
    
    //Definindo as coordenadas
    int linha_navio_horizontal = 2, coluna_navio_horizontal = 2;
    int linha_navio_vertical = 5, coluna_navio_vertical = 6;
    
    //Valida as coordenadas do navio horizontal
    if (validar_posicoes(tabuleiro, linha_navio_horizontal, coluna_navio_horizontal, tamanho_navio, 'H')) {
        posicionar_navio(tabuleiro, linha_navio_horizontal, coluna_navio_horizontal, navio_horizontal, tamanho_navio, 'H');
    } else {
        printf("Erro: Coordenadas invalidas. Programa encerrado.\n");
        return 1; //Coordenadas inválidas
    }
    
    //Valida as coordenadas do navio vertical
    if (validar_posicoes(tabuleiro, linha_navio_vertical, coluna_navio_vertical, tamanho_navio, 'V')) {
        posicionar_navio(tabuleiro, linha_navio_vertical, coluna_navio_vertical, navio_vertical, tamanho_navio, 'V');
    } else {
        printf("Erro: Coordenadas invalidas. Programa encerrado.\n");
        return 1; //Coordenadas inválidas
    }
    
    //Exibindo tabuleiro
    printf("Tabuleiro:\n");
    exibir_tabuleiro(tabuleiro);
    
    return 0;

    
    
}
