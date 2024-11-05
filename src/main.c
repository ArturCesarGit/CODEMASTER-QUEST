#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para usleep (delay)
#include <time.h>    // Para srand e rand
#include <string.h>  // Para manipulação de strings

// Bibliotecas personalizadas
#include "screen.h"  // Para manipulação da tela
#include "keyboard.h" // Para manipulação do teclado
#include "timer.h"    // Para manipulação de temporizadores

// Funções de animação do foguete
void clearScreen() {
    // Limpar a tela utilizando ANSI escape codes
    printf("\033[H\033[J");
}

// Função para desenhar as estrelas no fundo
void drawStars() {
    int i, j;
    int width = 80;  // Largura do terminal
    int height = 24; // Altura do terminal

    // Preencher o fundo com estrelas
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (rand() % 50 == 0) {  // Probabilidade de uma estrela aparecer
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// Função para desenhar os planetas no fundo
void drawPlanets() {
    int planets[5][2] = {
        {15, 5}, {40, 10}, {60, 15}, {25, 18}, {70, 8}
    };

    for (int i = 0; i < 5; i++) {
        int x = planets[i][0];
        int y = planets[i][1];

        // Desenha um planeta como um círculo 'O'
        printf("\033[%d;%dH", y, x);  // Move o cursor para a posição
        printf("O");
    }
}

// Função para desenhar o foguete
void drawRocket(int y_position) {
    printf("\033[%d;10H", y_position); // Mover para a linha especificada

    // Desenhando o foguete na posição vertical
    printf("                 \n");
    printf("        |        \n");
    printf("       / \\       \n");
    printf("      /   \\      \n");
    printf("     | O O |     \n");
    printf("     |  O  |     \n");
    printf("     | O O |     \n");
    printf("     |     |     \n");
    printf("    /|-----|\\    \n");
    printf("   / |     | \\   \n");
    printf("  |  |     |  |  \n");
    printf("  |  |     |  |  \n");
    printf("  |  |     |  |  \n");
    printf("   \\|_|/   \n");
    printf("      | | |      \n");
    printf("     /  |  \\     \n");
    printf("    /   |   \\    \n");
    printf("   |    |    |   \n");
    printf("   |    |    |   \n");  // Alinha o último tracinho com o corpo do foguete
}

// Função para exibir a tela inicial
void displayStartScreen() {
    printf("\033[H\033[J");  // Limpa a tela
    printf("\n\n\n");
    printf("   CCCCC  OOO   DDDD   EEEEE   M   M   AAAAA   SSSSS  TTTTT  EEEEE  RRRRR   \n");
    printf("  C      O   O  D   D  E       MM MM  A     A  S        T    E      R    R  \n");
    printf("  C      O   O  D   D  EEEE    M M M  AAAAAAA  SSSSS    T    EEEE   RRRRR   \n");
    printf("  C      O   O  D   D  E       M   M  A     A      S    T    E      R  R    \n");
    printf("   CCCCC  OOO   DDDD   EEEEE   M   M  A     A  SSSSS    T    EEEEE  R   R   \n");

    printf("\n");
    printf("                Aperte ENTER para começar!               \n");
    printf("\n");
}

// Função para exibir a mensagem final
void displayFinalMessage() {
    printf("\033[H\033[J");  // Limpa a tela
    printf("\n");
    printf("Sua jornada espacial acaba de começar!\n");
}


// Definindo dimensões do mapa
#define MAP_WIDTH 50   // Largura do mapa
#define MAP_HEIGHT 30  // Altura do mapa

// Definindo os símbolos no mapa
#define EMPTY ' '
#define PLAYER 'P'

// Coordenadas iniciais do jogador
int x = 25, y = 15;  // O jogador começa no meio do mapa

// Mapa representado como matriz de strings
char map[MAP_HEIGHT][MAP_WIDTH] = {
    "##################################################",  // Linha 0
    "#                                                #",  // Linha 1
    "#  Qual eh a capital do Brasil?                  #",  // Linha 2 
    "#                                                #",  // Linha 3
    "#  Porta 1 = Brasilia                            #",  // Linha 4 
    "#  Porta 2 = Paris                               #",  // Linha 5 
    "#  Porta 3 = Londres                             #",  // Linha 6 
    "#                                                #",  // Linha 7
    "#                                                #",  // Linha 8
    "#     [1]              [2]              [3]      #",  // Linha 9 
    "#                                                #",  // Linha 10
    "#                                                #",  // Linha 11
    "#                                                #",  // Linha 12
    "#                                                #",  // Linha 13
    "#                                                #",  // Linha 14
    "#                                                #",  // Linha 15
    "#                                                #",  // Linha 16
    "#                                                #",  // Linha 17
    "#                                                #",  // Linha 18
    "#                                                #",  // Linha 19
    "#                                                #",  // Linha 20
    "#                                                #",  // Linha 21
    "#                                                #",  // Linha 22
    "#                                                #",  // Linha 23
    "#                                                #",  // Linha 24
    "##################################################"   // Linha 25 
};

// Função para exibir o mapa
void display_map() {
    screenClear();
    // Desenha o mapa linha por linha
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == y && j == x) {
                printf("%c", PLAYER); // Desenha o jogador
            } else {
                printf("%c", map[i][j]); // Desenha o que está no mapa
            }
        }
        printf("\n");
    }

    screenUpdate();
}

// Função para verificar se o jogador entrou em uma porta
void checkDoor() {
    if (y == 9) {  // Verifica se o jogador está na linha das portas
        if (x >= 7 && x <= 8) {  // Porta 1 
            printf("Parabéns! Você escolheu a resposta correta: Brasília.\n");
            printf("Você continua o jogo.\n");
            return;  // Continua o jogo
        } else if (x >= 15 && x <= 16) {  // Porta 2 
            printf("Você escolheu a resposta errada: Paris.\n");
            printf("Fim do jogo.\n");
            exit(0); // Encerra o programa
        } else if (x >= 23 && x <= 24) {  // Porta 3 
            printf("Você escolheu a resposta errada: Londres.\n");
            printf("Fim do jogo.\n");
            exit(0); 
        }
    }
}

// Função para mover o jogador
void move_player(int direction) {
    int new_x = x, new_y = y;

    // Determina a nova posição com base na direção
    if (direction == 65 && y > 1) {         // Seta para cima
        new_y = y - 1;
    } else if (direction == 66 && y < MAP_HEIGHT - 2) { // Seta para baixo
        new_y = y + 1;
    } else if (direction == 67 && x < MAP_WIDTH - 2) { // Seta para a direita
        new_x = x + 1;
    } else if (direction == 68 && x > 1) {  // Seta para a esquerda
        new_x = x - 1;
    }

    // Atualiza a posição do jogador
    x = new_x;
    y = new_y;
}

// Função principal
int main() {
    // Parte da animação do foguete
    displayStartScreen();
    getchar();  // Aguarda o usuário apertar ENTER

    for (int i = 20; i >= 1; i--) { // Animação do foguete subindo
        clearScreen();
        drawStars();
        drawPlanets();
        drawRocket(i);  // Passando a posição i para o foguete
        usleep(500000);  // Espera meio segundo entre os quadros
    }

    displayFinalMessage();
    usleep(2000000); // Aguarda 2 segundos antes de iniciar o jogo

    // Inicializa o jogo
    screenInit(1);  // Inicializa a tela
    keyboardInit(); // Inicializa o teclado
    timerInit(30000); // Tempo de 30 segundos para responder

    // Exibe o mapa
    display_map();

    // Controle de movimento do jogador
    int ch = 0;
    while (1) {
        if (keyhit()) { // Verifica se uma tecla foi pressionada
            ch = readch(); // Lê a tecla pressionada

            // Move o jogador com as setas
            move_player(ch);

            // Atualiza a tela
            display_map();

            // Verifica se o jogador entrou em uma porta
            checkDoor();
        }
    }

    return 0;
}